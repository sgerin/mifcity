#include "HBlock.h"

HBlock::HBlock(const Vector& c1, const Vector& c2, const Vector& c3, const Vector& c4)
{
	dl = c1;
	ul = c2;
	ur = c3;
	dr = c4;
}

void HBlock::subdivide(BlockList& bl)
{
	bl.addBlock(this);
}

void HBlock::erode(float f)
{
    erode(f, &ul, &ur, &dr, &dl);
}

void HBlock::erode(float f, Vector* n_ul, Vector* n_ur, Vector* n_dr, Vector* n_dl)
{
    erodeSquare(f, ul, ur, dr, dl, n_ul, n_ur, n_dr, n_dl);
}

void HBlock::generateLots(LotList& ll)
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

    Floor* h_floor = new Floor(&inside_ul, &inside_ur, &inside_dr, &inside_dl);
    ll.addLot(h_floor);

    HLot* hl = new HLot(&inside_ul, &inside_ur, &inside_dr, &inside_dl);
    ll.addLot(hl);
}

float HBlock::surface()
{
    TBlock t(dl, ur, ul);
    TBlock t2(dl, ur, dr);

    return t.surface()*2 + t2.surface();
}

Mesh* HBlock::toMesh()
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