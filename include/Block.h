#ifndef BLOCK_H_
#define BLOCK_H_

#include "Mesh.h"

#include "Park.h"
#include "House.h"
#include "Building.h"
#include "TBuilding.h"
#include "Street.h"
#include "RoundTower.h"
#include "SquareTower.h"
#include "Floor.h"

#define MIN_SURFACE 10
#define STREET_SIZE 0.2
#define CITY_SIZE 40

class BlockList;
class LotList; 

class Block
{
public:
	// virtual ~Block();

	virtual void subdivide(BlockList&) = 0;
	virtual void generateLots(LotList&) = 0;

	//virtual void erode(float, LotList&) = 0;
	
	virtual Mesh* toMesh() = 0;
	virtual float surface() = 0;
	virtual void erode(float) = 0;
};

#endif
