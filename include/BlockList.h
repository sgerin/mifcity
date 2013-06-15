#ifndef BLOCK_LIST_H_
#define BLOCK_LIST_H_

#include <vector>
#include "Block.h"

class BlockList
{
private:
	std::vector<Block*> blocks;
	
public:
	// ~BlockList();
		
	std::vector<Block*> getBlocks() const;
	void addBlock(Block*);

	void subdivide(Block&);
	Mesh* toMesh();
	
	BlockList& operator+(const BlockList& bl);
};

#endif
