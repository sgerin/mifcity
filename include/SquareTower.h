#ifndef SQUARETOWER_H_
#define SQUARETOWER_H_

//#include "LotList.h"
#include "Lot.h"

class SquareTower : public Lot
{
public:
	SquareTower(const Vector&, const Vector&, const Vector&, const Vector&);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

	void test(Mesh*);
	void simpleSquareTower(Mesh*);

	
private:
	Vector ul; 
	Vector ur; 
	Vector dr; 
	Vector dl; 
};

#endif
