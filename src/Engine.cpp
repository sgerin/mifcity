#include "Engine.h"
#include "QBlock.h"


Mesh* Engine::createCity()
{
	BlockList* bl = generateBlocks();
	LotList* ll = generateLots(*bl);
	erodeBlocks(*bl);
	return ll->toMesh();
}

BlockList* Engine::generateBlocks()
{
	BlockList* bl = new BlockList();

	QBlock* init = new QBlock(Vector(-CITY_SIZE/2, 0, -CITY_SIZE/2), Vector(CITY_SIZE/2, 0, CITY_SIZE/2));
	init->loadRound(*bl);
	
	return bl;
}

void Engine::erodeBlocks(BlockList& bl)
{
	std::vector<Block*> blocks = bl.getBlocks();
	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); ++it)
	{
	 	(*it)->erode(STREET_SIZE);
	}
}

LotList* Engine::generateLots(BlockList& bl)
{
	LotList* lots = new LotList();
	std::vector<Block*> blocks = bl.getBlocks();
	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); ++it)
	{
		(*it)->generateLots(*lots);
	}
	return lots;
}
