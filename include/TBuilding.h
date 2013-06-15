#ifndef TBUILDING_H_
#define TBUILDING_H_

//#include "LotList.h"
#include "Lot.h"

class TBuilding : public Lot
{
public:
	TBuilding(const Vector&, const Vector&, const Vector&);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

	void simpleBuilding(Mesh*);

	
private:
	Vector a;
	Vector b;
	Vector c;
};

#endif
