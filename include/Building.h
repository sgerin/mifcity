#ifndef BUILDING_H_
#define BUILDING_H_

//#include "LotList.h"
#include "Lot.h"

class Building : public Lot
{
public:
	Building(const Vector&, const Vector&, const Vector&, const Vector&);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

	void simpleBuilding(Mesh*);

    void tower(Mesh *m, float radius, Vector &center, const Vector &_ul, const Vector &_ur, const Vector &_dr, const Vector &_dl);

	
private:
	Vector ul;
	Vector ur;
	Vector dr;
	Vector dl;
};

#endif
