#ifndef HLOT_H_
#define HLOT_H_

#include "Lot.h"
#include "ObjManager.h"
#include "Primitives.h"

class HLot : public Lot
{
public:
	HLot(const Vector*, const Vector*, const Vector*, const Vector*);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();


private:
	Vector ul;
	Vector ur;
	Vector dl;
	Vector dr;
};

#endif
