#include "TBlock.h"

#include <iostream>

#define OFFSET 0.1
//#define DEBUG


// a
//
// c           b


TBlock::TBlock(const Vector& a, const Vector& b, const Vector& c)
{
    TBlock::a = a;
    TBlock::b = b;
    TBlock::c = c;
}

float TBlock::surface()
{
    float area2 = a[0] * (b[2] - c[2]);
    area2 += b[0] * (c[2] - a[2]);
    area2 += c[0] * (a[2] - b[2]);
    area2 /= 2.0;
    if(area2 < 0)
        area2 *= -1.0;
    return area2;
}

void TBlock::subdivide(BlockList& bl)
{
    if (surface() > MIN_SURFACE)
    {
        int a = rand()%100;
        if (a < 50)
        T_QTT(bl);
        else
        	T_QQT(bl);
    }
    else
        bl.addBlock(this);
}

void TBlock::T_QQT(BlockList& bl)
{
    Vector tier_ab = (2*a + b)/3;
    Vector tier_ab2 = (a + 2*b)/3;
    Vector tier_cb = (2*c + b)/3;
    Vector tier_cb2 = (c + 2*b)/3;

    QBlock* q = new QBlock(a, tier_ab, tier_cb, c);
    q->subdivide(bl);
    q = new QBlock(tier_ab, tier_ab2, tier_cb2, tier_cb);
    q->subdivide(bl);
    TBlock* t = new TBlock(tier_ab2, b, tier_cb2);
    t->subdivide(bl);
}

/*void TBlock::T_TTT(BlockList& bl)
{
    std::cout << "T -> T T T" << std::endl;
    Vector tier_ab = (2*a + b)/3;
    Vector tier_ab2 = (a + 2*b)/3;

    TBlock* t = new TBlock(a, c, tier_ab);
    t->subdivide(bl);

    t = new TBlock(tier_ab, c, tier_ab2);
    t->subdivide(bl);

    t = new TBlock(tier_ab2, c, b);
    t->subdivide(bl);
}*/

void TBlock::T_QTT(BlockList& bl)
{
#ifdef DEBUG
    std::cout << "T -> Q T T" << std::endl;
#endif
    Vector mid_ab = (a + b)/2;
    Vector mid_bc = (b + c)/2;
    Vector mid_ca = (c + a)/2;

    QBlock* q = new QBlock(mid_ca, mid_ab, mid_bc, c);
    q->subdivide(bl);

    TBlock* t = new TBlock(a, mid_ab, mid_ca);
    t->subdivide(bl);

    t = new TBlock(mid_ab, b, mid_bc);
    t->subdivide(bl);
}

void TBlock::erode(float f, Vector* n_a, Vector* n_b, Vector* n_c)
{
    erodeTriangle(f, a, b, c, n_a, n_b, n_c);
}

void TBlock::erode(float f)
{
    erode(f, &a, &b, &c);
}

void TBlock::generateLots(LotList& ll)
{
    Vector inside_a;
    Vector inside_b;
    Vector inside_c;

    Vector center = ((a+b)/2 + c)/2;
    double dist_to_downtown = Norm(center-Vector(0.0, 0.0,0.0));
    dist_to_downtown = abs(dist_to_downtown);

    float var_size = 0.0;
    if(dist_to_downtown < 3)
        var_size = STREET_SIZE;
    else if(dist_to_downtown < 5)
        var_size = STREET_SIZE/2;

    erode(STREET_SIZE + var_size, &inside_a, &inside_b, &inside_c);

    Street* t = new Street(a, b, inside_b, inside_a);
    ll.addLot(t);

    t = new Street(inside_c, inside_b, b, c);
    ll.addLot(t);

    t = new Street(a, inside_a, inside_c, c);
    ll.addLot(t);

    int a = rand()%100;

    if(dist_to_downtown < CITY_SIZE/6)
    {
        if (a < 20)
            generateBuilding(ll, inside_a, inside_b, inside_c);
        else
            generateRoundTower(ll, inside_a, inside_b, inside_c);
    }
    else if(dist_to_downtown < CITY_SIZE/4)
    {
        if (a < 30)
            generateResidential(ll, inside_a, inside_b, inside_c);
        else if (a < 70)
            generateBuilding(ll, inside_a, inside_b, inside_c);
        else
            generateRoundTower(ll, inside_a, inside_b, inside_c);
    }
    else
    {
        if (a < 90)
            generateResidential(ll, inside_a, inside_b, inside_c);
        else
            generateBuilding(ll, inside_a, inside_b, inside_c);
    }

    Floor* h_floor = new Floor(&inside_a, &inside_b, &inside_c);
    ll.addLot(h_floor);
}

void TBlock::generateResidential(LotList& ll, const Vector& a, const Vector& b, const Vector& c)
{
    Vector i_a, i_b, i_c;
    erodeTriangle(0.2, a, b, c, &i_a, &i_b, &i_c);

    Park* h_park = new Park(i_a, i_b, i_c);
    ll.addLot(h_park);

    //side ab
    {
        Vector m_a = a;
        Vector m_ia = i_a;

        float scale = Norm(i_a - i_b) / Norm(a - b);

        while(Norm(m_a - b) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_a = Normalized(b - a)*HEIGHT + m_a;
            Vector tmp_ia = Normalized(i_b - i_a)*HEIGHT*scale + m_ia;

            House* h = new House(m_a, tmp_a, tmp_ia, m_ia);
            ll.addLot(h);

            m_a += Normalized(b - a)*HEIGHT + Normalized(b - a)*HEIGHT/4;
            m_ia += Normalized(i_b - i_a)*HEIGHT*scale + Normalized(i_b - i_a)*scale*HEIGHT/4;
        }
    }

    //side ac
    {
        Vector m_a = a;
        Vector m_ia = i_a;

        float scale = Norm(i_a - i_c) / Norm(a - c);

        while(Norm(m_a - c) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_a = Normalized(c - a) * HEIGHT + m_a;
            Vector tmp_ia = Normalized(i_c - i_a)*HEIGHT*scale + m_ia;

            House* h = new House(m_ia, tmp_ia, tmp_a, m_a);
            ll.addLot(h);

            m_a += Normalized(c - a)*HEIGHT + Normalized(c - a)*HEIGHT/4;
            m_ia += Normalized(i_c - i_a)*HEIGHT*scale + Normalized(i_c - i_a)*scale*HEIGHT/4;
        }
    }

    //side bc
    {
        Vector m_b = b;
        Vector m_ib = i_b;

        float scale = Norm(i_b - i_c) / Norm(b - c);

        while(Norm(m_b - c) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_b = Normalized(c - b)*HEIGHT + m_b;
            Vector tmp_ib = Normalized(i_c - i_b)*HEIGHT*scale + m_ib;

            House* h = new House(m_b, tmp_b, tmp_ib, m_ib);
            ll.addLot(h);

            m_b += Normalized(c - b)*HEIGHT + Normalized(c - b)*HEIGHT/4;
            m_ib += Normalized(i_c - i_b)*HEIGHT*scale + Normalized(i_c - i_b)*scale*HEIGHT/4;
        }
    }

}

void TBlock::generateBuilding(LotList& ll, const Vector& inside_a, const Vector& inside_b, const Vector& inside_c)
{
    TBuilding* tb = new TBuilding(inside_a, inside_b, inside_c);
    ll.addLot(tb);
}

void TBlock::generateRoundTower(LotList& ll, const Vector& inside_a, const Vector& inside_b, const Vector& inside_c)
{
    double a_dist = Norm(inside_c-inside_b);
    double b_dist = Norm(inside_b-inside_a);
    double c_dist = Norm(inside_b-inside_a);

    double x = (a_dist*inside_a[0]+b_dist*inside_b[0]+c_dist*inside_c[0])/(a_dist+b_dist+c_dist);
    double z = (a_dist*inside_a[2]+b_dist*inside_b[2]+c_dist*inside_c[2])/(a_dist+b_dist+c_dist);

    Vector center = Vector(x, 0, z);
    float radius = sqrt(((b_dist + c_dist - a_dist)*(c_dist + a_dist - b_dist)*(a_dist + b_dist - c_dist))/(a_dist+b_dist+c_dist))/2;
    //radius /= 2;
    if(radius != radius)
    {
        radius = std::min(std::min(a_dist, b_dist), c_dist);
    }

    RoundTower* rt = new RoundTower(center, radius);
    ll.addLot(rt);
}


void TBlock::generateHousewithGarden(LotList& ll, const Vector& inside_a, const Vector& inside_b, const Vector& inside_c)
{
    Vector tier_ab = (2*inside_a + inside_b)/3;
    Vector tier2_ab = (inside_a + 2*inside_b)/3;

    //Vector ab = b - a;
    Vector ab = inside_b - inside_a;
    Vector ca = inside_a - inside_c;
    Vector ab_normal = Vector(ab[2], ab[1], -ab[0]);
    double dota = ab_normal*ca;

    if(dota > 0)
    {
        //CCW
        ab_normal[0] = -ab_normal[0];
        ab_normal[2] = -ab_normal[2];
    }

    // if(dota > 0)
    // 	ca_normal = Vector(-ca[2], ca[1], ca[0]);

    ab_normal = Normalized(ab_normal);

    float f;
    Vector p1;
    Vector p2;

    do
    {
        f = (float)rand()/(float)RAND_MAX;
        p1 = tier_ab + f*ab_normal;
        p2 = tier2_ab + f*ab_normal;
    }while(inTriangle(p1, inside_a, inside_b, inside_c) && inTriangle(p2, inside_a, inside_b, inside_c));

    p1 = Intersect(inside_a, inside_c, tier_ab, p1);
    p2 = Intersect(inside_b, inside_c, tier2_ab, p2);

    // std::cout << "DISPLAY  " << std::endl;
    // std::cout << "A, B, C  " << std::endl;
    // inside_a.display();
    // inside_b.display();
    // inside_c.display();
    // std::cout << "P1, P2  " << std::endl;
    // p1.display();
    // p2.display();
    // std::cout << std::endl << std::endl;

    House* h = new House(p1, p2, tier2_ab, tier_ab);
    ll.addLot(h);
    Park* p = new Park(inside_a, tier_ab, p1);
    ll.addLot(p);
    p = new Park(inside_b, tier2_ab, p2);
    ll.addLot(p);
    p = new Park(p1, p2, inside_c);
    ll.addLot(p);
}


Mesh* TBlock::toMesh()
{
    Mesh* m = new Mesh;
    m->addVertex(a);
    m->addVertex(b);
    m->addVertex(c);
    m->addFace(0, 1, 2);
    return m;
}

Vector& TBlock::getCoord_A(){ return a; }

Vector& TBlock::getCoord_B(){ return b; }

Vector& TBlock::getCoord_C(){ return c; }
