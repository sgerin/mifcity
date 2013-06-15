#include "SquareTower.h"
#include "FacadeBuildingA.h"

SquareTower::SquareTower(const Vector& ul, const Vector& ur, const Vector& dr, const Vector& dl) : ul(ul), ur(ur), dr(dr), dl(dl)
{
}

Mesh* SquareTower::elevate()
{
    Mesh* m = new Mesh();
    simpleSquareTower(m);
    return m;
}


void SquareTower::test(Mesh *m)
{
    //Mesh* components = NULL;
    int nb_storey = FLOORS +(rand() % FLOORS);
    int type = 0;
    *m += *FacadeBuildingA(dl, dr, nb_storey, type).toMesh();
    *m += *FacadeBuildingA(dr, ur, nb_storey, type).toMesh();
    *m += *FacadeBuildingA(ur, ul, nb_storey, type).toMesh();
    *m += *FacadeBuildingA(ul, dl, nb_storey, type).toMesh();
}

void SquareTower::simpleSquareTower(Mesh* m)
{
    Mesh* components = NULL;
    int nb_storey = FLOORS +(rand() % FLOORS);
    int type = rand() % 4;
    switch (type)
    {
    case 0:
        components = polygon(ul, ur, dr, dl, HEIGHT);
        components->setColor(0.8,0.8,1.0);
        *m += *components;
        break;
    case 1:
        for(int i = 0; i < nb_storey; i++) {
            components = polygon(ul, ur, dr, dl, HEIGHT);
            components->translate(0, (HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(ul, ur, dr, dl, (float)HEIGHT/3);
            Vector c;
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            Vector scale(0.9,1,0.9);
            components->scale(scale);
            components->translate(c[0], 0, c[2]);
            components->translate(0, HEIGHT + (HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    case 2:
        for(int i = 0; i < nb_storey; i++) {
            components = polygon(ul, ur, dr, dl, HEIGHT);
            components->translate(0, (HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(ul, ur, dr, dl, (float)HEIGHT/10);
            Vector c;
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            Vector scale(1.1,1,1.1);
            components->scale(scale);
            components->translate(c[0], 0, c[2]);
            components->translate(0, HEIGHT + (HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    case 3:
        for(int i = 0; i < nb_storey ; i++) {
            Vector scale0(0.7f + 0.3f *  sin(M_PI / (float)(nb_storey ) * i),
                          1.f,
                          0.7f + 0.3f *  sin(M_PI / (float)(nb_storey ) * i));
            Vector c;
            components = polygon(ul, ur, dr, dl, (float)HEIGHT);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->translate(0, ((float)HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->scale(scale0);
            components->translate(c[0], 0, c[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(ul, ur, dr, dl, (float)HEIGHT/3);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->scale(scale0);
            Vector scale(0.9,1,0.9);
            components->scale(scale);
            components->translate(c[0], 0, c[2]);
            components->translate(0, (float)HEIGHT + ((float)HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    case 4:
        for(int i = 0; i < nb_storey ; i++) {
            Vector rotate(0,M_PI / (nb_storey * 2 ) * i,0);
            Vector scale0(0.5f,1.f,0.5f);
            Vector c;
            components = polygon(dl, ul, ur, dr, (float)HEIGHT);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->translate(0, ((float)HEIGHT + ((float)HEIGHT/5)) * i, 0);
            components->rotate(rotate);
            components->scale(scale0);
            components->translate(c[0], 0, c[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(dl, ul, ur, dr, (float)HEIGHT/5);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->rotate(rotate);
            components->scale(scale0);
            Vector scale(0.9,1,0.9);
            components->scale(scale);
            components->translate(c[0], 0, c[2]);
            components->translate(0, (float)HEIGHT + ((float)HEIGHT + ((float)HEIGHT/5)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    }
}


Mesh* SquareTower::toMesh()
{
    Mesh* m = new Mesh;
    *m += *elevate();

    return m;
}

float SquareTower::surface()
{	
    float z = ur[2] - dr[2];
    float x = ur[0] - ul[0];
    return (x*z);
}
