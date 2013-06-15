#ifndef ROUNDTOWER_H_
#define ROUNDTOWER_H_

//#include "LotList.h"
#include "Lot.h"

class RoundTower : public Lot
{
public:
	RoundTower(const Vector&, float);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

	void simpleRoundTower(Mesh*);

	
private:
	Vector center; 
	float radius;
};

#endif
