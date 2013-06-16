#ifndef QBLOCK_H_
#define QBLOCK_H_

#include "LotList.h"
#include "BlockList.h"
#include "TBlock.h"
#include "HBlock.h"

class QBlock : public Block
{
public:
	QBlock(const Vector&, const Vector&);
	QBlock(const Vector&, const Vector&, const Vector&, const Vector&);

	void subdivide(BlockList&);
	Mesh* toMesh();
	float surface();

	Vector& getCoord_UpLeft();
	Vector& getCoord_UpRight();
	Vector& getCoord_DownLeft();
	Vector& getCoord_DownRight();

	void loadRound(BlockList&);
	void empty(BlockList&);
	void loadHisto(BlockList&);

	void Q_QQ(BlockList&);
	void Q_QQQQ(BlockList&);
	//void Q_QTT(BlockList&);
	void Q_TTTT(BlockList&);
	void Q_QQT(BlockList&);

	void erode(float);
    void erode(float, Vector*, Vector*, Vector*, Vector*);
	
	void erode(float, LotList&);
	void generateLots(LotList&);

	void generateResidential(LotList&, const Vector&, const Vector&, const Vector&, const Vector&);
	void generateBuilding(LotList&, const Vector&, const Vector&, const Vector&, const Vector&);
	void generateHousewithGarden(LotList&, const Vector&, const Vector&, const Vector&, const Vector&);
	void generateRoundTower(LotList&, const Vector&, const Vector&, const Vector&, const Vector&);
	void generateSquareTower(LotList&, const Vector&, const Vector&, const Vector&, const Vector&);

private:
	Vector ul;
	Vector ur;
	Vector dl;
	Vector dr;
};

#endif
