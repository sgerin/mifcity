#include "Park.h"
#include "ObjManager.h"
#include "Engine.h"

int Park::nb_instance = 0; 
Mesh* Park::tree = NULL;

Park::Park(const Vector& ul, const Vector& ur, const Vector& dr, const Vector& dl)
{
    Park::ul = ul;
    Park::ur = ur;
    Park::dr = dr;
    Park::dl = dl;
	triangle = false;

	ObjManager om;

	if(Park::nb_instance == 0)
	{
		#ifdef __linux
			//ObjManager om;
			tree = om.createFromObj("../data/low_poly_tree.obj");
		#elif __APPLE__
			//ObjManager om;
			tree = om.createFromObj("data/low_poly_tree.obj");
		#endif
	}

	++Park::nb_instance;
}

Park::Park(const Vector& a, const Vector& b, const Vector& c)
{
	ul = a; 
	ur = b; 
	dr = c; 
	triangle = true;

	ObjManager om;

	if(Park::nb_instance == 0)
	{
		//ObjManager om;
		#ifdef __linux
			//ObjManager om;
			tree = om.createFromObj("../data/low_poly_tree.obj");
		#elif __APPLE__
			//ObjManager om;
			tree = om.createFromObj("data/low_poly_tree.obj");
		#endif

	}
	++Park::nb_instance;
}

Mesh* Park::elevate()
{
	int nb_tree = surface()*10 + 4;
	//double x, y, z;
	float u, v;
	Vector pos; 
	Mesh* trees = new Mesh();

	Mesh* tree = new Mesh();
	*tree += *Park::tree;
	//tree->scale(0.4, 0.4, 0.4);

	tree->scale(HEIGHT*2, HEIGHT*2, HEIGHT*2);
	tree->translate(0, HEIGHT/2, 0);
	tree->setColor(69.f/255.f, 139.f/255.f, 0.0);

	for(int i=0; i<nb_tree; ++i)
	{
		u = (float)rand()/(float)RAND_MAX;
		v = (float)rand()/(float)RAND_MAX;
		if(triangle)
			pos = (1 - sqrt(u)) * ul + (sqrt(u) * (1 - v)) * ur + (sqrt(u) * v) * dr;
		else
			pos = dl + u*(ul-dl) + v*(dr-dl);

		tree->translate(pos[0], 0, pos[2]);
		*trees += *tree;
		tree->translate(-pos[0], 0, -pos[2]);
}
	Mesh* floor;
	if (triangle)
		floor = polygon(dr, ur, ul, HEIGHT/2);
	else
		floor = polygon(dl, ul, ur, dr, HEIGHT/2);

	floor->setColor(124.f/255.f, 205.f/255.f, 124.f/255.f);

	*trees += *floor;
	
	return trees;
}

Mesh* Park::toMesh()
{
	Mesh* m = new Mesh;
	
	/*if(!triangle)
	{	
        m->addVertex(ul, Vector(42, 162, 51));
		m->addVertex(ur, Vector(42, 162, 51));
        m->addVertex(dr, Vector(42, 162, 51));
		m->addVertex(dl, Vector(42, 162, 51));
		m->addFace(0, 1, 2);
		m->addFace(2, 3, 0);
	}
	else
	{
		m->addVertex(ul, Vector(42, 162, 51));
		m->addVertex(ur, Vector(42, 162, 51));
		m->addVertex(dr, Vector(42, 162, 51));
		m->addFace(0, 1, 2);
	}*/

	Mesh* trees = elevate();
	if(trees != NULL)
		*m += *trees;

	return m;
}

float Park::surface()
{
	float area;
	if(triangle)
	{
		area = ul[0] * (ur[2] - dr[2]);
		area += ur[0] * (dr[2] - ul[2]);
		area += dr[0] * (ul[2] - ur[2]);
		area /= 2.0;
		if(area < 0)
		{
			area *= -1.0;
		}
	}

	else
	{	
		float z = ur[2] - dr[2];
		float x = ur[0] - ul[0];
		area = x*z;
	}

	return area;

}
