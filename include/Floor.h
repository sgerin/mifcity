#ifndef FLOOR_H_
#define FLOOR_H_

//#include "LotList.h"
#include "Lot.h"

class Floor : public Lot
{
public:
	Floor(const Vector*, const Vector*, const Vector*, const Vector* v=0);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();


private:
	bool tgl;
	Vector ul;
	Vector ur;
	Vector dl;
	Vector dr;
};

#endif
