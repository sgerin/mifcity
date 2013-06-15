#ifndef LOT_H_
#define LOT_H_

#include "Mesh.h"
#include "Primitives.h"

#define HEIGHT 0.3
#define FLOORS 15

class Lot
{
public:
	virtual Mesh* elevate() = 0;
	virtual Mesh* toMesh() = 0;
	virtual float surface() = 0;
};

#endif
