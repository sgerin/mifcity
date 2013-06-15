#ifndef PARK_H_
#define PARK_H_

// #include "LotList.h"
#include "Lot.h"

class Park : public Lot
{
public:
	static Mesh* tree;
    Park(const Vector&, const Vector&, const Vector&, const Vector&);
	Park(const Vector&, const Vector&, const Vector&);

	Mesh* elevate();
	Mesh* toMesh();
	float surface();

private:
	Vector ul;
	Vector ur;
	Vector dl;
	Vector dr;
	bool triangle;
	static int nb_instance; 
};

#endif
