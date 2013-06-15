#ifndef FACADE_BUILDING_A_H_
#define FACADE_BUILDING_A_H_

// #include "Texture.h"
#include "FloorBuildingA.h"
#include "FloorBuildingB.h"
#include "FloorBuildingC.h"
#include "FloorBuildingD.h"
#include "FloorBuildingE.h"
#include "FloorBuildingF.h"
//#include "LotList.h"
//#include "Lot.h"


class FacadeBuildingA
{
public:
	FacadeBuildingA(const Vector&, const Vector&, int, int);

	Mesh* toMesh();

	
private:
	Vector ul;
	Vector ur;
	Vector dr;
	Vector dl;
	int storey; 
	int type;
	//std::vector<Vector> 
};

#endif
