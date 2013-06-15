#include "HLot.h"

HLot::HLot(const Vector* a, const Vector* b, const Vector* c, const Vector* d)
{
    dl = *a;
    ul = *b;
    ur = *c;
    dr = *d;
}

Mesh* loadBuilding()
{
	ObjManager om;
	//int a = rand()%1;
	//if (a == 0)
	#ifdef __linux
		return om.createFromObj("../data/eiffel.obj");
	#elif __APPLE__
		return om.createFromObj("data/eiffel.obj");
	#endif
}

Mesh* HLot::elevate()
{
	Vector i1, i2, i3, i4;
	Vector ii1, ii2, ii3, ii4;

	erodeSquare(0.1, dl, ul, ur, dr, &i1, &i2, &i3, &i4);
	Mesh* m = polygon(i1, i2, i3, i4, HEIGHT/3);

	erodeSquare(0.1, i1, i2, i3, i4, &ii1, &ii2, &ii3, &ii4);
	*m += *polygon(ii1, ii2, ii3, ii4, 2*HEIGHT/3);
	
	Mesh* m2 = loadBuilding();
	Vector center = ((ul+ur)/2 + (dl+dr)/2)/2;
	center[1] = 2*HEIGHT/3;
	m2->scale(10, 10, 10);
	m2->translate(center);

	*m += *m2;
	
	//int s = Norm(ul - ur);

	return m;
}

Mesh* HLot::toMesh()
{
    return elevate();
}

float HLot::surface() { return 0; }
