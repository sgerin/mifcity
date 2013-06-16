#include "RoundTower.h"

RoundTower::RoundTower(const Vector& center, float radius) : center(center), radius(radius)
{
}

Mesh* RoundTower::elevate()
{
    Mesh* m = new Mesh();
    simpleRoundTower(m);
    return m;
}

void RoundTower::simpleRoundTower(Mesh* m)
{
    Mesh* components = NULL;
    int nb_storey = FLOORS + (rand() % FLOORS);
    int type = rand() % 4;
    switch (type)
    {
    case 0:
//        components = sphere(radius*4,20,20);
//        components->translate(center[0], radius*8, center[2]);
//        *m += *components;
        components = cylinder(radius, HEIGHT * nb_storey, 30);
        components->translate(center[0], 0, center[2]);
        components->setColor(0.8,0.8,1.0);
        *m += *components;

        components = cylinder(radius / 20, HEIGHT * 1.5f , 30);
        components->translate(center[0], HEIGHT * nb_storey, center[2]);
        components->setColor(0.2,0.2,0.2);
        *m += *components;
        break;
    case 1:
        for(int i = 0; i < nb_storey; i++) {
            float rad = radius - radius * (((float)i / (float)nb_storey));
            components = cylinder(rad, HEIGHT, 30);
            components->translate(center[0], HEIGHT * i, center[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
        }
        break;
    case 2:
        for(int i = 0; i < nb_storey; i++) {
            components = cylinder(radius, HEIGHT, 30);
            components->translate(center[0],
                                  (HEIGHT + ((float)HEIGHT/10)) * i,
                                  center[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = cylinder(radius * 1.1f, (float)HEIGHT / 10, 30);
            components->translate(center[0],
                                  HEIGHT + (HEIGHT + ((float)HEIGHT/10)) * i,
                                  center[2]);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    case 3:
        for(int i = 0; i < nb_storey; i++) {
            Vector scale0(0.9f + 0.5f *  sin(M_PI / (float)(nb_storey ) * i),
                          1.f,
                          0.9f + 0.5f *  sin(M_PI / (float)(nb_storey ) * i));
            components = cylinder(radius,(float)HEIGHT,30);
            components->translate(0, ((float)HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->scale(scale0);
            components->translate(center[0], 0, center[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = cylinder(radius,(float)HEIGHT/10,30);
            components->scale(scale0);
            Vector scale(1.1,1,1.1);
            components->scale(scale);
            components->translate(center[0], 0, center[2]);
            components->translate(0, (float)HEIGHT + ((float)HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    }
}

Mesh* RoundTower::toMesh()
{
    Mesh* m = new Mesh;
    *m += *elevate();

    return m;
}

float RoundTower::surface()
{
    return M_PI*radius*radius;
}
