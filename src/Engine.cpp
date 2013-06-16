#include "Engine.h"
#include "QBlock.h"

Mesh* Engine::createCity()
{
	BlockList* bl = generateBlocks();
	//erodeBlocks(*bl);
	LotList* ll = generateLots(*bl);
	// std::vector<Lot*> lots = ll->getLots();
	erodeBlocks(*bl);
	//return bl->toMesh();
	return ll->toMesh();
}

BlockList* Engine::generateBlocks()
{
	BlockList* bl = new BlockList();

	QBlock* init = new QBlock(Vector(-CITY_SIZE/2, 0, -CITY_SIZE/2), Vector(CITY_SIZE/2, 0, CITY_SIZE/2));
	//TBlock* init = new TBlock(Vector(-CITY_SIZE/2, 0, -CITY_SIZE/2), Vector(CITY_SIZE/2, 0, CITY_SIZE/2), Vector(-CITY_SIZE/2, 0, CITY_SIZE/2));
	//bl->subdivide(*init);
// <<<<<<< HEAD
	//init->loadRound(*bl);
	init->loadRound(*bl);
// =======
    // init->loadRound(*bl);
//	init->loadHisto(*bl);
// >>>>>>> e118d48eedbf3ffa41490b34bc1606a4d9d01429
	//init->empty(*bl);
	
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
	//TODO : a erode function that doesn't erode the same amount at different spots
}

LotList* Engine::generateLots(BlockList& bl)
{
	LotList* lots = new LotList();
	//std::vector<Lot*> lots;
	std::vector<Block*> blocks = bl.getBlocks();
	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); ++it)
	{
		(*it)->generateLots(*lots);
	}
	return lots;
}
