#ifndef LOT_LIST_H_
#define LOT_LIST_H_

#include <vector>
#include "Lot.h"

class LotList
{
private:
	std::vector<Lot*> lots;
	
public:
	std::vector<Lot*> getLots() const;
	void addLot(Lot*);

	Mesh* toMesh();
	
	LotList& operator+(const LotList&);
};

#endif
