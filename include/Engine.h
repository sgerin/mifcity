#ifndef ENGINE_H_
#define ENGINE_H_

#include "LotList.h"
#include "BlockList.h"
//#include "QBlock.h"

//#define CITY_SIZE 20
class LotList;

class Engine
{
public:
	Mesh* createCity();
private:
	BlockList* generateBlocks();
	void erodeBlocks(BlockList&);
	LotList* generateLots(BlockList&);
};

#endif
