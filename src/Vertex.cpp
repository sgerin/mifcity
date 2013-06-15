#include "Vertex.h"

Vertex::Vertex()
{
	location[0] = .0;
	location[1] = .0;
	location[2] = .0;
	texture[0] = .0;
	texture[1] = .0;
	faces.clear();
}


Vertex::Vertex(float a, float b, float c)
{
	location[0] = a;
	location[1] = b;
	location[2] = c;
	texture[0] = .0;
	texture[1] = .0;
	faces.clear();	
}

Vertex::Vertex(double a, double b, double c)
{
	location[0] = a;
	location[1] = b;
	location[2] = c;
	texture[0] = .0;
	texture[1] = .0;
	faces.clear();	
}

Vertex::Vertex(const Vector& v)
{
	location[0] = v[0];
	location[1] = v[1];
	location[2] = v[2];
	faces.clear();	
}

Vertex::Vertex(const Vector& v, const Vector& c)
{
	location[0] = v[0];
	location[1] = v[1];
	location[2] = v[2];
	texture[0] = .0;
	texture[1] = .0;
	faces.clear();	
}


Vertex::Vertex(const Vector& v, float t1, float t2)
{
	location[0] = v[0];
	location[1] = v[1];
	location[2] = v[2];
	texture[0] = t1;
	texture[1] = t2;
	faces.clear();	
}


Vertex::~Vertex()
{
	faces.clear();
}



