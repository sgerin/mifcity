#ifndef HOUSE_H_
#define HOUSE_H_

//#include "LotList.h"
#include "Lot.h"

class House : public Lot
{
public:
	House(Vector, Vector, Vector, Vector);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

	void simpleHouse(Mesh*);

	
private:
	Vector ul;
	Vector ur;
	Vector dl;
	Vector dr;
};

#endif
