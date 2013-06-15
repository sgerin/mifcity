#include "QBlock.h"

#include <iostream>

#define OFFSET 0.1
#define PI M_PI
//#define DEBUG

//       v2
//
//
// v1
QBlock::QBlock(const Vector& v1, const Vector& v2)
{
    ur = v2;
    dl = v1;
    dr = Vector(v2[0], 0, v1[2]);
    ul = Vector(v1[0], 0, v2[2]);
}

// v2    v3
//
//
// v1    v4
QBlock::QBlock(const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4)
{
    ur = v3;
    dl = v1;
    dr = v4;
    ul = v2;
}

float QBlock::surface()
{
    TBlock t(dl, ur, ul);
    TBlock t2(dl, ur, dr);

    return (t.surface() + t2.surface())/2;
}

void QBlock::empty(BlockList& bl)
{
    bl.addBlock(this);
}

void QBlock::loadRound(BlockList& bl)
{
    Vector origin(0,0,0);
    int size_x = Norm(ul - ur);
    int size_y = Norm(ul - dl);
    int sc_x = size_x/10;
    int sc_y = size_y/10;

    //middle
    TBlock* t = new TBlock(Vector(-1*sc_x,0,sc_y*2), origin, Vector(-2*sc_x,0,sc_y*1));
    t->subdivide(bl);
    t = new TBlock(Vector(-1*sc_x,0,sc_y*2), Vector(1*sc_x,0,sc_y*2), origin);
    t->subdivide(bl);
    t = new TBlock(Vector(1*sc_x,0,sc_y*2), Vector(2*sc_x,0,sc_y*1), origin);
    t->subdivide(bl);
    t = new TBlock(Vector(2*sc_x,0,sc_y*1), Vector(2*sc_x,0,sc_y*-1), origin);
    t->subdivide(bl);

    t = new TBlock(Vector(2*sc_x,0,sc_y*-1), Vector(1*sc_x,0,sc_y*-2), origin);
    t->subdivide(bl);
    t = new TBlock(Vector(1*sc_x,0,sc_y*-2), Vector(-1*sc_x,0,sc_y*-2), origin);
    t->subdivide(bl);
    t = new TBlock(Vector(-1*sc_x,0,sc_y*-2), Vector(-2*sc_x,0,sc_y*-1), origin);
    t->subdivide(bl);
    t = new TBlock(Vector(-2*sc_x,0,sc_y*-1), Vector(-2*sc_x,0,sc_y*1), origin);
    t->subdivide(bl);

    //sides
    QBlock* q = new QBlock(Vector(1*sc_x,0,sc_y*2), Vector(2*sc_x,0,sc_y*5), Vector(5*sc_x,0,sc_y*2), Vector(2*sc_x,0,sc_y*1));
    q->subdivide(bl);
    q = new QBlock(Vector(2*sc_x,0,sc_y*-1), Vector(2*sc_x,0,sc_y*1), Vector(5*sc_x,0,sc_y*2), Vector(5*sc_x,0,sc_y*-2));
    q->subdivide(bl);
    q = new QBlock(Vector(2*sc_x,0,sc_y*-5), Vector(1*sc_x,0,sc_y*-2), Vector(2*sc_x,0,sc_y*-1), Vector(5*sc_x,0,sc_y*-2));
    q->subdivide(bl);
    q = new QBlock(Vector(-2*sc_x,0,sc_y*-5), Vector(-1*sc_x,0,sc_y*-2), Vector(1*sc_x,0,sc_y*-2), Vector(2*sc_x,0,sc_y*-5));
    q->subdivide(bl);

    q = new QBlock(Vector(-1*sc_x,0,sc_y*-2), Vector(-2*sc_x,0,sc_y*-5), Vector(-5*sc_x,0,sc_y*-2), Vector(-2*sc_x,0,sc_y*-1));
    q->subdivide(bl);
    q = new QBlock(Vector(-2*sc_x,0,sc_y*1), Vector(-2*sc_x,0,sc_y*-1), Vector(-5*sc_x,0,sc_y*-2), Vector(-5*sc_x,0,sc_y*2));
    q->subdivide(bl);
    q = new QBlock(Vector(-2*sc_x,0,sc_y*5), Vector(-1*sc_x,0,sc_y*2), Vector(-2*sc_x,0,sc_y*1), Vector(-5*sc_x,0,sc_y*2));
    q->subdivide(bl);
    q = new QBlock(Vector(2*sc_x,0,sc_y*5), Vector(1*sc_x,0,sc_y*2), Vector(-1*sc_x,0,sc_y*2), Vector(-2*sc_x,0,sc_y*5));
    q->subdivide(bl);

    //corners
    t = new TBlock(Vector(-5*sc_x,0,sc_y*2), Vector(-5*sc_x,0,sc_y*5), Vector(-2*sc_x,0,sc_y*5));
    t->subdivide(bl);
    t = new TBlock(Vector(2*sc_x,0,sc_y*5), Vector(5*sc_x,0,sc_y*5), Vector(5*sc_x,0,sc_y*2));
    t->subdivide(bl);
    t = new TBlock(Vector(5*sc_x,0,sc_y*-2), Vector(5*sc_x,0,sc_y*-5), Vector(2*sc_x,0,sc_y*-5));
    t->subdivide(bl);
    t = new TBlock(Vector(-2*sc_x,0,sc_y*-5), Vector(-5*sc_x,0,sc_y*-5), Vector(-5*sc_x,0,sc_y*-2));
    t->subdivide(bl);

}

void QBlock::loadHisto(BlockList& bl)
{
    Vector mu = (ur+ul)/2;
    Vector md = (dr+dl)/2;
    Vector ml = (ul+dl)/2;
    Vector mr = (ur+dr)/2;

    Vector middle = (mu+md)/2;

    Vector ul_h = (ml+mu)/2;
    Vector ur_h = (mu+middle)/2;
    Vector dl_h = (middle+ml)/2;

    TBlock* t = new TBlock(mu, ul, ml);
    t->subdivide(bl);
    t = new TBlock(ur_h, mu, ul_h);
    t->subdivide(bl);
    t = new TBlock(dl_h, ul_h, ml);
    t->subdivide(bl);

    QBlock* q = new QBlock(dl, ml, middle, md);
    q->subdivide(bl);

    q = new QBlock(md, middle, mr, dr);
    q->subdivide(bl);

    q = new QBlock(middle, mu, ur, mr);
    q->subdivide(bl);

    HBlock* h = new HBlock(dl_h, ul_h, ur_h, middle);
    h->subdivide(bl);
}

void QBlock::subdivide(BlockList& bl)
{
    if (surface() > MIN_SURFACE)
    {
        //if too thin
        /*if (size_u > 2*size_l && size_u > 2*size_r  ||
            size_d > 2*size_l && size_d > 2*size_r  ||
            size_l > 2*size_u && size_l > 2*size_d  ||
            size_r > 2*size_u && size_r > 2*size_d)
            Q_QQ(bl);
        if (abs(size_u - size_d) < MIN_SURFACE && abs(size_l-size_r) < MIN_SURFACE)
        {*/
        int a = rand()%100;
        if (a < 50)
            Q_TTTT(bl);
        else //if (a < 70)
            Q_QQQQ(bl);
        /*else
                Q_QQ(bl);*/
        /*}
        else
            */
    }
    else
        bl.addBlock(this);
}

//void QBlock::Q_QQT(BlockList& bll)
//{
//    int size_r = Norm(ur-dr);
//    int size_u = Norm(ur-ul);
//    int size_l = Norm(ul-dl);
//    int size_d = Norm(dr-dl);

//    Vector sl, sr;
//    Vector bl, br;

//    if (size_u > size_d)
//    {
//        if (size_l>size_r)
//        {
//            bl = ur;
//            br = ul;
//            sl = dr;
//            sr = dl;
//        }
//        else
//        {
//            bl = ul;
//            br = ur;
//            sl = dl;
//            sr = dr;
//        }
//    }
//    else
//    {
//        if (size_l > size_r)
//        {
//            bl = dr;
//            br = dl;
//            sl = ur;
//            sr = ul;
//        }
//        else
//        {
//            bl = dl;
//            br = dr;
//            sl = ul;
//            sr = ur;
//        }
//    }

//    Vector middle_big = (br+bl)/2;
//    TBlock* t = new TBlock(sr, br, middle_big);
//    t->subdivide(bll);

//    QBlock* q = new QBlock(sl, (sl+bl)/2, (middle_big + sr)/2, sr);
//    q->subdivide(bll);
//    q = new QBlock((sl+bl)/2, bl, middle_big, (middle_big + sr)/2);
//    q->subdivide(bll);
//}

void QBlock::Q_TTTT(BlockList& bl)
{
    Vector mu = (ur+ul)/2;
    Vector md = (dr+dl)/2;
    Vector center = (mu + md)/2;

    TBlock* t = new TBlock(ul, ur, center);
    t->subdivide(bl);
    t = new TBlock(ul, center, dl);
    t->subdivide(bl);
    t = new TBlock(dl, center, dr);
    t->subdivide(bl);
    t = new TBlock(center, ur, dr);
    t->subdivide(bl);
}

void QBlock::Q_QQ(BlockList& bl)
{
    //#ifdef DEBUG
    std::cout << "Q -> Q Q" << std::endl;
    //#endif
    int sizer = Norm(ur-dr);
    int sizeu = Norm(ur-ul);
    int sizel = Norm(ul-dl);
    int sized = Norm(dl-dr);

    if (sizeu > sizer || sizeu > sizel || sized > sizer || sized > sizel)
    {
        Vector middle_right = (ur + dr)/2;
        Vector middle_left = (ul + dl)/2;

        QBlock* q = new QBlock(middle_left, middle_right, dr, dl);
        q->subdivide(bl);

        q = new QBlock(ul, ur, middle_right, middle_left);
        q->subdivide(bl);
    }
    else
    {
        Vector middle_up = (ur + ul)/2;
        Vector middle_bot = (dr + dl)/2;

        QBlock* q = new QBlock(ul, middle_up, middle_bot, dl);
        q->subdivide(bl);

        q = new QBlock(middle_up, ur, dr, middle_bot);
        q->subdivide(bl);
    }
}

void QBlock::Q_QQQQ(BlockList& bl)
{
#ifdef DEBUG
    std::cout << "Q -> Q Q Q Q" << std::endl;
#endif
    Vector middle_up = (ur + ul)/2;
    Vector middle_bot = (dr + dl)/2;
    Vector middle_left = (ul + dl)/2;
    Vector middle_right = (ur + dr)/2;

    Vector middle = (middle_up + middle_bot)/2;

    QBlock* q = new QBlock(middle_left, middle, middle_bot, dl);
    q->subdivide(bl);

    q = new QBlock(ul, middle_up, middle, middle_left);
    q->subdivide(bl);

    q = new QBlock(middle_up, ur, middle_right, middle);
    q->subdivide(bl);

    q = new QBlock(middle, middle_right, dr, middle_bot);
    q->subdivide(bl);
}

/*void QBlock::Q_QTT(BlockList& bl)
{
#ifdef DEBUG
    std::cout << "Q -> Q T T" << std::endl;
#endif
    Vector middle_up = (ur + ul)/2;
    Vector middle_bot = (dr + dl)/2;

    QBlock* q = new QBlock(dl, middle_up);
    q->subdivide(bl);

    TBlock* t = new TBlock(ur, middle_bot, dr);
    t->subdivide(bl);

    t = new TBlock(ur, middle_bot, middle_up);
    t->subdivide(bl);
}*/

/*void QBlock::erode(float f, LotList& ll)
{
    Vector u = ul - ur;
    Vector l = dl - ul;
    Vector u_normal = Vector(u[2], u[1], -u[0]);
    double dota = u_normal*l;

    Vector d = dr - dl;
    Vector r = ur - dr;

    Vector l_normal;
    Vector d_normal;
    Vector r_normal;

    if(dota > 0)
    {
        //CW
        l_normal = Vector(l[2], l[1], -l[0]);
        d_normal = Vector(d[2], d[1], -d[0]);
        r_normal = Vector(r[2], r[1], -r[0]);
    }
    else if(dota < 0)
    {
        //CCW
        u_normal[0] = -u_normal[0];
        u_normal[2] = -u_normal[2];
        l_normal = Vector(-l[2], l[1], l[0]);
        d_normal = Vector(-d[2], d[1], d[0]);
        r_normal = Vector(-r[2], r[1], r[0]);
    }

    u_normal = Normalized(u_normal);
    l_normal = Normalized(l_normal);
    d_normal = Normalized(d_normal);
    r_normal = Normalized(r_normal);

    Vector ur1 = ur + f*u_normal;
    Vector ur2 = ur + f*r_normal;

    Vector ul1 = ul + f*u_normal;
    Vector ul2 = ul + f*l_normal;

    Vector dl1 = dl + f*d_normal;
    Vector dl2 = dl + f*l_normal;

    Vector dr1 = dr + f*d_normal;
    Vector dr2 = dr + f*r_normal;

    inside_ur = Intersect(ul1, ur1, dr2, ur2);
    inside_ul = Intersect(ur1, ul1, dl2, ul2);
    inside_dr = Intersect(ur2, dr2, dl1, dr1);
    inside_dl = Intersect(ul2, dl2, dr1, dl1);

    Street* t = new Street(ul, ur, inside_ur, inside_ul);
    ll.addLot(t);

    t = new Street(inside_ur, ur, dr, inside_dr);
    ll.addLot(t);

    t = new Street(inside_dl, inside_dr, dr, dl);
    ll.addLot(t);

    t = new Street(ul, inside_ul, inside_dl, dl);
    ll.addLot(t);

}*/

//DEBUG
void QBlock::erode(float f)
{
    erode(f, &ul, &ur, &dr, &dl);
}
void QBlock::erode(float f, Vector* n_ul, Vector* n_ur, Vector* n_dr, Vector* n_dl)
{
    erodeSquare(f, ul, ur, dr, dl, n_ul, n_ur, n_dr, n_dl);
}

void QBlock::generateLots(LotList& ll)
{
    Vector inside_ul;
    Vector inside_ur;
    Vector inside_dl;
    Vector inside_dr;

    Vector center = ((ul+ur)/2 + (dl+dr)/2)/2;
    double dist_to_downtown = Norm(center-Vector(0.0, 0.0,0.0));
    dist_to_downtown = abs(dist_to_downtown);

    float var_size = 0.0;
    if(dist_to_downtown < 3)
        var_size = STREET_SIZE;
    else if(dist_to_downtown < 5)
        var_size = STREET_SIZE/2;

    erode(STREET_SIZE+var_size, &inside_ul, &inside_ur, &inside_dr, &inside_dl);

    Street* t = new Street(ul, ur, inside_ur, inside_ul);
    ll.addLot(t);

    t = new Street(inside_ur, ur, dr, inside_dr);
    ll.addLot(t);

    t = new Street(inside_dl, inside_dr, dr, dl);
    ll.addLot(t);

    t = new Street(ul, inside_ul, inside_dl, dl);
    ll.addLot(t);

    int a = rand()%100;

    if(dist_to_downtown < CITY_SIZE/6)
    {
        if (a < 30)
            generateBuilding(ll, inside_ul, inside_ur, inside_dr, inside_dl);
        else
            generateSquareTower(ll, inside_ul, inside_ur, inside_dr, inside_dl);
    }
    else if(dist_to_downtown < CITY_SIZE/4)
    {
        if (a < 30)
            generateResidential(ll, inside_ul, inside_ur, inside_dr, inside_dl);
        else if (a < 70)
            generateBuilding(ll, inside_ul, inside_ur, inside_dr, inside_dl);
        else
            generateSquareTower(ll, inside_ul, inside_ur, inside_dr, inside_dl);
    }
    else
    {
        if (a < 70)
            generateResidential(ll, inside_ul, inside_ur, inside_dr, inside_dl);
        else
            generateBuilding(ll, inside_ul, inside_ur, inside_dr, inside_dl);
    }

    Floor* h_floor = new Floor(&inside_ul, &inside_ur, &inside_dr, &inside_dl);
    ll.addLot(h_floor);
}

float getAngle(const Vector& v1, const Vector& v2)
{
    float a = acos((v1[0]*v2[0] + v1[2]*v2[2]) / Norm(v1)*Norm(v2));
    return (a*180)/PI;
}

void QBlock::generateResidential(LotList& ll, const Vector& ul, const Vector& ur, const Vector& dr, const Vector& dl)
{
    Vector i_ul, i_ur, i_dl, i_dr;
    erodeSquare(0.2, ul, ur, dr, dl, &i_ul, &i_ur, &i_dr, &i_dl);

    Park* h_park = new Park(i_ul, i_ur, i_dr, i_dl);
    ll.addLot(h_park);

    //side left
    {
        Vector m_dl = dl;
        Vector m_idl = i_dl;

        float scale = Norm(i_ul - i_dl) / Norm(ul - dl);

        while(Norm(m_dl - ul) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_dl = Normalized(ul - dl)*HEIGHT + m_dl;
            Vector tmp_idl = Normalized(i_ul - i_dl)*HEIGHT*scale + m_idl;

            House* h = new House(m_dl, tmp_dl, tmp_idl, m_idl);
            ll.addLot(h);

            m_dl += Normalized(ul - dl)*HEIGHT + Normalized(ul - dl)*HEIGHT/4;
            m_idl += Normalized(i_ul - i_dl)*HEIGHT*scale + Normalized(i_ul - i_dl)*scale*HEIGHT/4;
        }
    }

    //side up
    {
        Vector m_ul = ul;
        Vector m_iul = i_ul;

        float scale = Norm(i_ul - i_ur) / Norm(ul - ur);

        while(Norm(m_ul - ur) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_ul = Normalized(ur - ul)*HEIGHT + m_ul;
            Vector tmp_iul = Normalized(i_ur - i_ul)*HEIGHT*scale + m_iul;

            House* h = new House(m_ul, tmp_ul, tmp_iul, m_iul);
            ll.addLot(h);

            m_ul += Normalized(ur - ul)*HEIGHT + Normalized(ur - ul)*HEIGHT/4;
            m_iul += Normalized(i_ur - i_ul)*HEIGHT*scale + Normalized(i_ur - i_ul)*scale*HEIGHT/4;
        }
    }

    //side right
    {
        Vector m_ur = ur;
        Vector m_iur = i_ur;

        float scale = Norm(i_ur - i_dr) / Norm(ur - dr);

        while(Norm(m_ur - dr) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_ur = Normalized(dr - ur)*HEIGHT + m_ur;
            Vector tmp_iur = Normalized(i_dr - i_ur)*HEIGHT*scale + m_iur;

            House* h = new House(m_ur, tmp_ur, tmp_iur, m_iur);
            ll.addLot(h);

            m_ur += Normalized(dr - ur)*HEIGHT + Normalized(dr - ur)*HEIGHT/4;
            m_iur += Normalized(i_dr - i_ur)*HEIGHT*scale + Normalized(i_dr - i_ur)*scale*HEIGHT/4;
        }
    }

    //side down
    {
        Vector m_dr = dr;
        Vector m_idr = i_dr;

        float scale = Norm(i_dr - i_dl) / Norm(dr - dl);

        while(Norm(m_dr - dl) > HEIGHT+HEIGHT/4)
        {
            Vector tmp_dr = Normalized(dl - dr)*HEIGHT + m_dr;
            Vector tmp_idr = Normalized(i_dl - i_dr)*HEIGHT*scale + m_idr;

            House* h = new House(m_dr, tmp_dr, tmp_idr, m_idr);
            ll.addLot(h);

            m_dr += Normalized(dl - dr)*HEIGHT + Normalized(dl - dr)*HEIGHT/4;
            m_idr += Normalized(i_dl - i_dr)*HEIGHT*scale + Normalized(i_dl - i_dr)*scale*HEIGHT/4;
        }
    }
}

void QBlock::generateBuilding(LotList& ll, const Vector& inside_ul, const Vector& inside_ur, const Vector& inside_dr, const Vector& inside_dl)
{
    Building* b = new Building(inside_ul, inside_ur, inside_dr, inside_dl);
    ll.addLot(b);
}

void QBlock::generateSquareTower(LotList& ll, const Vector& inside_ul, const Vector& inside_ur, const Vector& inside_dr, const Vector& inside_dl)
{

    SquareTower* st = new SquareTower(inside_ul, inside_ur, inside_dr, inside_dl);
    ll.addLot(st);
}


void QBlock::generateRoundTower(LotList& ll, const Vector& inside_ul, const Vector& inside_ur, const Vector& inside_dr, const Vector& inside_dl)
{
    Vector middle_up = (inside_ul + inside_ur)/2;
    Vector middle_down = (inside_dl + inside_dr)/2;
    Vector center = (middle_up + middle_down)/2;
    float dist_middle_up = Norm(center - middle_up);
    float dist_middle_down = Norm(center - middle_down);
    float radius = (dist_middle_up > dist_middle_down) ?  dist_middle_down : dist_middle_up;
    radius -= radius/5;
    RoundTower* rt = new RoundTower(center, radius);
    ll.addLot(rt);
}

void QBlock::generateHousewithGarden(LotList& ll, const Vector& inside_ul, const Vector& inside_ur, const Vector& inside_dr, const Vector& inside_dl)
{
    Vector tier_up = (2*inside_ul + inside_ur)/3;
    Vector tier2_up = (inside_ul + 2*inside_ur)/3;
    Vector tier_down = (2*inside_dl + inside_dr)/3;
    Vector tier2_down = (inside_dl + 2*inside_dr)/3;
    Vector tier_left = (2*inside_ul + inside_dl)/3;
    Vector tier2_left = (inside_ul + 2*inside_dl)/3;
    Vector tier_right = (2*inside_ur + inside_dr)/3;
    Vector tier2_right = (inside_ur + 2*inside_dr)/3;

    Vector new_ul = Intersect(tier_up, tier_down, tier_left, tier_right);
    Vector new_ur = Intersect(tier2_up, tier2_down, tier_left, tier_right);
    Vector new_dl = Intersect(tier_up, tier_down, tier2_left, tier2_right);
    Vector new_dr = Intersect(tier2_up, tier2_down, tier2_left, tier2_right);

    House* h = new House(new_ul, new_ur, new_dr, new_dl);
    ll.addLot(h);
    Park* p = new Park(inside_ul, inside_ur, tier_right, tier_left);
    ll.addLot(p);
    p = new Park(tier2_left, tier2_right, inside_dr, inside_dl);
    ll.addLot(p);
    p = new Park(tier_left, new_ul, new_dl, tier2_left);
    ll.addLot(p);
    p = new Park(new_ur, tier_right, tier2_right, new_dr);
    ll.addLot(p);
}

Mesh* QBlock::toMesh()
{
    Mesh* m = new Mesh;
    m->addVertex(ul);
    m->addVertex(ur);
    m->addVertex(dr);
    m->addVertex(dl);
    m->addFace(0, 1, 2);
    m->addFace(2, 3, 0);
    return m;
}

Vector& QBlock::getCoord_UpLeft() { return ul; }

Vector& QBlock::getCoord_UpRight() { return ur; }

Vector& QBlock::getCoord_DownLeft() { return dl; }

Vector& QBlock::getCoord_DownRight() { return dr; }


