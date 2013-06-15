#include "TBuilding.h"


TBuilding::TBuilding(const Vector& a, const Vector& b, const Vector& c) : a(a), b(b), c(c)
{
}

Mesh* TBuilding::elevate()
{
	Mesh* m = new Mesh();
	simpleBuilding(m);
	return m;
}

void TBuilding::simpleBuilding(Mesh* m)
{
    Mesh* components = NULL;
    int nb_storey = 1+(rand() % FLOORS);
    int type = rand() % 3;
    switch (type)
    {
//    case 0:
//        components = polygon(a, b, c, HEIGHT*nb_storey);
//        components->setColor(0.8,0.8,1.0);
//        *m += *components;
//        break;
    case 0:
        for(int i = 0; i < nb_storey; i++) {
            components = polygon(a, b, c, HEIGHT);
            components->translate(0, (HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(a, b, c, (float)HEIGHT/3);
            Vector d;
            components->centroid(d);
            components->translate(-d[0], 0, -d[2]);
            Vector scale(0.9,1,0.9);
            components->scale(scale);
            components->translate(d[0], 0, d[2]);
            components->translate(0, HEIGHT + (HEIGHT + ((float)HEIGHT/3)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    case 1:
        for(int i = 0; i < nb_storey; i++) {
            components = polygon(a, b, c, HEIGHT);
            components->translate(0, (HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(a, b, c, (float)HEIGHT/10);
            Vector d;
            components->centroid(d);
            components->translate(-d[0], 0, -d[2]);
            Vector scale(1.1,1,1.1);
            components->scale(scale);
            components->translate(d[0], 0, d[2]);
            components->translate(0, HEIGHT + (HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    case 2:
        for(int i = 0; i < nb_storey ; i++) {
            Vector scale0(0.8f + 0.2f *  sin(M_PI / (float)(nb_storey ) * i),
                          1.f,
                          0.8f + 0.2f *  sin(M_PI / (float)(nb_storey ) * i));
            Vector d;
            components = polygon(a, b, c, (float)HEIGHT);
            components->centroid(d);
            components->translate(-d[0], 0, -d[2]);
            components->translate(0, ((float)HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->scale(scale0);
            components->translate(d[0], 0, d[2]);
            components->setColor(0.8,0.8,1.0);
            *m += *components;
            components = polygon(a, b, c,  (float)HEIGHT/10);
            components->centroid(d);
            components->translate(-d[0], 0, -d[2]);
            components->scale(scale0);
            Vector scale(1.1,1,1.1);
            components->scale(scale);
            components->translate(d[0], 0, d[2]);
            components->translate(0, (float)HEIGHT + ((float)HEIGHT + ((float)HEIGHT/10)) * i, 0);
            components->setColor(0.2,0.2,0.2);
            *m += *components;
        }
        break;
    }
}


Mesh* TBuilding::toMesh()
{
	Mesh* m = new Mesh;
	*m += *elevate();

	return m;
}

float TBuilding::surface()
{	
	float area = a[0] * (b[2] - c[2]);
	area += b[0] * (c[2] - a[2]);
	area += c[0] * (a[2] - b[2]);
	area /= 2.0;
	//area = abs(area);
	// if(area < 0)
	// {
	// 	area *= -1.0;
	// }

	return abs(area);
}
