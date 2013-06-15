#include "Street.h"
#define SIDEWALK_HEIGHT 0.02

Street::Street(const Vector& a, const Vector& b, const Vector& c, const Vector& d)
{
       ul = a;
       ur = b;
       dr = c;
       dl = d;
}

Mesh* Street::elevate()
{
       //return polygon(ul, ur, dr, dl, 0);

      Vector sidewalk_ul, sidewalk_ur, sidewalk_dr, sidewalk_dl;
      sidewalk_ul = (4*ul+ur)/5;
      sidewalk_ur = (ul+4*ur)/5;
      sidewalk_dr = (dl+4*dr)/5;
      sidewalk_dl = (4*dl+dr)/5;
      Mesh* sidewalks = polygon(ul, sidewalk_ul, sidewalk_dl, dl, SIDEWALK_HEIGHT);
      *sidewalks += *polygon(sidewalk_ur, ur, dr, sidewalk_dr, SIDEWALK_HEIGHT);
      *sidewalks += *polygon(sidewalk_ul, sidewalk_ur, sidewalk_dr, sidewalk_dl, 0);
      return sidewalks;
}

Mesh* Street::toMesh()
{

       // m->addVertex(ur, Vector(138, 138, 138));
       // m->addVertex(ul, Vector(138, 138, 138));
       // m->addVertex(dl, Vector(138, 138, 138));
       // m->addVertex(dr, Vector(138, 138, 138));
       // m->addFace(0, 1, 2);
       // m->addFace(2, 3, 0);

       //Mesh* m = new Mesh;

       return elevate();
}

float Street::surface() { return 0; }
