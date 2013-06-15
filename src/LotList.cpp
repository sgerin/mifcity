#include "LotList.h"

std::vector<Lot*> LotList::getLots() const
{
	return lots;
}

LotList& LotList::operator+(const LotList& ll)
{
	for(unsigned int i=0; i<ll.getLots().size(); i++)
		lots.push_back(ll.getLots()[i]);
	return *this;
}

Mesh* LotList::toMesh()
{
	Mesh* m = new Mesh();
	for(unsigned int i=0; i<lots.size(); i++)
	{
		*m += *( lots[i]->toMesh() );
	}
	return m;
}

void LotList::addLot(Lot* l)
{
	lots.push_back(l);
}
