#ifndef STREET_H_
#define STREET_H_

#include "Lot.h"

class Street : public Lot
{
public:
	Street(const Vector&, const Vector&, const Vector&, const Vector&);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

	
private:
	Vector ul;
	Vector ur;
    Vector dr;
    Vector dl;
};

#endif
