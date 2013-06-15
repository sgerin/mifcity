#include "Building.h"


Building::Building(const Vector& ul, const Vector& ur, const Vector& dr, const Vector& dl) : ul(ul), ur(ur), dr(dr), dl(dl)
{
}

Mesh* Building::elevate()
{
    Mesh* m = new Mesh();
    simpleBuilding(m);
    return m;
}

void Building::simpleBuilding(Mesh* m)
{
    Mesh* components = new Mesh();
    int nb_storey = (rand() % FLOORS);
    int type = (rand()%4);
    switch (type)
    {
    case 0:
        components = polygon(ul, ur, dr, dl, HEIGHT);
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
        //        for(int i = 0; i < nb_storey; i++) {
        Vector _ul = ul,_ur = ur,_dr = dr,_dl = dl;
        getSquare(_ul,_ur,_dr,_dl);
        Vector d1 = _ur - _ul;
        Vector d2 = _ul - _dl;

        double ratio = Norm(d1) / Norm(d2);


        if((ratio < 1.5) && (ratio > 0.5))
        {
            //            components = polygon(_ul,_ur,_dr,_dl, 10 * HEIGHT);
            //            components->setColor(1.0,0.0,0.0);
            Vector center  = Intersect(_ul,_ur,_dr,_dl);
            float radius = (Norm(_ur - _ul) / 2) / M_PI;
            tower(components,radius,center,_ul,_ur,_dr,_dl);
        }
        else
        {
            if(ratio > 1)
            {
                //                components = polygon(_dl,
                //                                     _ul,
                //                                     _ul + Normalized(_ur - _ul) * (Norm(_ur - _ul) / 2),
                //                                     _dl + Normalized(_dr - _dl) * (Norm(_dr - _dl) / 2),
                //                                     10 * HEIGHT);
                Vector center  = Intersect(_dl,
                                           _ul + Normalized(_ur - _ul) * (Norm(_ur - _ul) / 2),
                                           _ul,
                                           _dl + Normalized(_dr - _dl) * (Norm(_dr - _dl) / 2)
                                           );
                float radius = (Norm(_ur - _ul) / 2) / M_PI;
                tower(components,radius,center,_dl,_ul,
                      _ul + Normalized(_ur - _ul) * (Norm(_ur - _ul) / 2),
                      _dl + Normalized(_dr - _dl) * (Norm(_dr - _dl) / 2));
                *m += *components;
                //                components = polygon(_ur,
                //                                     _dr,
                //                                     _dr + Normalized(_dl - _dr) * (Norm(_dl - _dr) / 2),
                //                                     _ur + Normalized(_ul - _ur) * (Norm(_ul - _ur) / 2),
                //                                     10 * HEIGHT);
                center  = Intersect(_ur,
                                    _dr + Normalized(_dl - _dr) * (Norm(_dl - _dr) / 2),
                                    _dr,
                                    _ur + Normalized(_ul - _ur) * (Norm(_ul - _ur) / 2)
                                    );
                radius = (Norm(_dl - _dr) / 2) / M_PI;
                tower(components,radius,center,_ur,_dr,
                      _dr + Normalized(_dl - _dr) * (Norm(_dl - _dr) / 2),
                      _ur + Normalized(_ul - _ur) * (Norm(_ul - _ur) / 2));
            }
            else
            {
                //                components = polygon(_ul,
                //                                     _ur,
                //                                     _ur + Normalized(_dr - _ur) * (Norm(_dr - _ur) / 2),
                //                                     _ul + Normalized(_dl - _ul) * (Norm(_dl - _ul) / 2),
                //                                     10 * HEIGHT);
                Vector center  = Intersect(_ul,
                                           _ur + Normalized(_dr - _ur) * (Norm(_dr - _ur) / 2),
                                           _ur,
                                           _ul + Normalized(_dl - _ul) * (Norm(_dl - _ul) / 2)
                                           );
                float radius = (Norm(_dr - _ur) / 2) / M_PI;
                tower(components,radius,center,_ul,_ur,
                      _ur + Normalized(_dr - _ur) * (Norm(_dr - _ur) / 2),
                      _ul + Normalized(_dl - _ul) * (Norm(_dl - _ul) / 2));
                *m += *components;
                //                components = polygon(_dr,
                //                                     _dl,
                //                                     _dl + Normalized(_ul - _dl) * (Norm(_ul - _dl) / 2),
                //                                     _dr + Normalized(_ur - _dr) * (Norm(_ur - _dr) / 2),
                //                                     10 * HEIGHT);
                center = Intersect(_dr,
                                   _dl + Normalized(_ul - _dl) * (Norm(_ul - _dl) / 2),
                                   _dl,
                                   _dr + Normalized(_ur - _dr) * (Norm(_ur - _dr) / 2)
                                   );
                radius = (Norm(_ul - _dl) / 2) / M_PI;
                tower(components,radius,center,_dr,_dl,
                      _dl + Normalized(_ul - _dl) * (Norm(_ul - _dl) / 2),
                      _dr + Normalized(_ur - _dr) * (Norm(_ur - _dr) / 2));

            }
        }

        *m += *components;

    }

}

void Building::tower(Mesh *m, float radius, Vector &center, const Vector &_ul, const Vector &_ur, const Vector &_dr, const Vector &_dl)
{
    Mesh* components = NULL;
    int type = rand() % 6;
    switch (type)
    {
    case 0:
        for(int i = 0; i < 7; i++) {

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
    case 1:
        for(int i = 0; i < 7; i++) {
            Vector scale0(0.9f + 0.5f *  sin(M_PI / (float)(7 ) * i),
                          1.f,
                          0.9f + 0.5f *  sin(M_PI / (float)(7 ) * i));
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
    case 2:
        for(int i = 0; i < 7; i++) {
            components = polygon(_ul, _ur, _dr, _dl, HEIGHT);
            components->translate(0, (HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(_ul, _ur, _dr, _dl, (float)HEIGHT/3);
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
    case 3:
        for(int i = 0; i < 7; i++) {
            components = polygon(_ul, _ur, _dr, _dl, HEIGHT);
            components->translate(0, (HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(_ul, _ur, _dr, _dl, (float)HEIGHT/10);
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
    case 4:
        for(int i = 0; i < 7 ; i++) {
            Vector scale0(0.7f + 0.3f *  sin(M_PI / (float)(7 ) * i),
                          1.f,
                          0.7f + 0.3f *  sin(M_PI / (float)(7 ) * i));
            Vector c;
            components = polygon(_ul, _ur, _dr, _dl, (float)HEIGHT);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->translate(0, ((float)HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->scale(scale0);
            components->translate(c[0], 0, c[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(_ul, _ur, _dr, _dl, (float)HEIGHT/3);
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
    case 5:
        for(int i = 0; i < 7 * 2; i++) {
            Vector rotate(0,M_PI / (7 * 2) * i,0);
            Vector scale0(0.7f,1.f,0.7f);
            Vector c;
            components = polygon(_dl, _ul, _ur, _dr, (float)HEIGHT/2);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->translate(0, ((float)HEIGHT/2 + ((float)HEIGHT/10)) * i, 0);
            components->rotate(rotate);
            components->scale(scale0);
            components->translate(c[0], 0, c[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(_dl, _ul, _ur, _dr, (float)HEIGHT/10);
            components->centroid(c);
            components->translate(-c[0], 0, -c[2]);
            components->rotate(rotate);
            components->scale(scale0);
            Vector scale(0.9,1,0.9);
            components->scale(scale);
            components->translate(c[0], 0, c[2]);
            components->translate(0, (float)HEIGHT/2 + ((float)HEIGHT/2 + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    }
    components->translate(-center[0], 0, -center[2]);
    components->scale(0.9,1.0,0.9);
    components->translate(center[0], 0, center[2]);
}



Mesh* Building::toMesh()
{
    Mesh* m = new Mesh;
    *m += *elevate();

    return m;
}

float Building::surface()
{
    float z = ur[2] - dr[2];
    float x = ur[0] - ul[0];
    return (x*z);
}
