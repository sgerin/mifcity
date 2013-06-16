#ifndef HBLOCK_H_
#define HBLOCK_H_

#include "LotList.h"
#include "BlockList.h"
#include "HLot.h"
#include "TBlock.h"

class HBlock : public Block
{
public:
	HBlock(const Vector&, const Vector&, const Vector&, const Vector&);

	void subdivide(BlockList&);
	Mesh* toMesh();
	float surface();

	Vector& getCoord_UpLeft() { return ul; }
	Vector& getCoord_UpRight() { return ur; }
	Vector& getCoord_DownLeft() { return dl; }
	Vector& getCoord_DownRight() { return dr; }

	void erode(float);
	void erode(float, Vector*, Vector*, Vector*, Vector*);

	void generateLots(LotList&);

private:
	Vector ul;
	Vector ur;
	Vector dl;
	Vector dr;
};

#endif
