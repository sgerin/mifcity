#include "Floor.h"

Floor::Floor(const Vector* a, const Vector* b, const Vector* c, const Vector* d)
{
    ul = *a;
    ur = *b;
    dr = *c;
    tgl = (d == 0);
    if (!tgl)
        dl = *d;
}

Mesh* Floor::elevate()
{
    Mesh* components;
    if (tgl)
        components = polygon(ul, ur, dr, 0.01f);//new Mesh();
    else
        components =polygon(ul, ur, dr, dl, 0.01f);
    switch(rand() % 4)
    {
    case 0:
        components->setColor(0.2,0.2,0.2);
        break;
    case 1:
        components->setColor(0.8,0.8,0.8);
        break;
    case 2:
        components->setColor(0.7,0.7,0.7);
        break;
    case 3:
        components->setColor(0.5,0.5,0.5);
        break;
    }
    return components;
}

Mesh* Floor::toMesh()
{
    Mesh* m = new Mesh;
    *m += *elevate();
    return m;
}

float Floor::surface() { return 0; }
