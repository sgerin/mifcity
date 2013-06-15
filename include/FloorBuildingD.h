#ifndef FLOOR_BUILDING_D_H_
#define FLOOR_BUILDING_D_H_

#include "Textures.h"
#include "Vector.h"
#include "Mesh.h"
//#include "LotList.h"
//#include "Lot.h"


class FloorBuildingD
{
public:
	FloorBuildingD(const Vector&, const Vector&, float*);

	Mesh* toMesh();

	
private:
	Vector ul;
	Vector ur;
	Vector dr;
	Vector dl;
	//std::vector<Vector> 
};

#endif
