#include "BlockList.h"

std::vector<Block*> BlockList::getBlocks() const
{
	return blocks;
}

BlockList& BlockList::operator+(const BlockList& bl)
{
	for(unsigned int i=0; i<bl.getBlocks().size(); i++)
		blocks.push_back(bl.getBlocks()[i]);
	return *this;
}

Mesh* BlockList::toMesh()
{
	Mesh* m = new Mesh();
	for(unsigned int i=0; i<blocks.size(); i++)
	{
		*m += *( blocks[i]->toMesh() );
	}
	return m;
}

void BlockList::addBlock(Block* b)
{
	blocks.push_back(b);
}

void BlockList::subdivide(Block& init)
{
	//init.loadParis(*this);
	init.subdivide(*this);
}
