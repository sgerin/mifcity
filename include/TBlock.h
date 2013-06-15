#ifndef TBLOCK_H_
#define TBLOCK_H_

#include "LotList.h"
#include "BlockList.h"
#include "QBlock.h"

class TBlock : public Block
{
public:
    TBlock(const Vector& a, const Vector& b, const Vector& c);
    // ~TBlock(){}

	void subdivide(BlockList&);
	Mesh* toMesh();
	float surface();

	Vector& getCoord_A();
	Vector& getCoord_B();
	Vector& getCoord_C();

	//void T_TTT(BlockList&);
	void T_QTT(BlockList&);
	void T_QQT(BlockList&);

	void erode(float);
	void erode(float, Vector*, Vector*, Vector*);

	void erode(float, LotList&); 
	void generateLots(LotList&);

	void generateResidential(LotList&, const Vector&, const Vector& ,const Vector&);
	void generateHousewithGarden(LotList&, const Vector&, const Vector& ,const Vector&);
	void generateRoundTower(LotList&, const Vector&, const Vector& ,const Vector&);
	void generateBuilding(LotList&, const Vector&, const Vector& ,const Vector&);

private:
	Vector a;
	Vector b;
	Vector c;
};

#endif
