#ifndef OBJ_MANAGER_H_
#define OBJ_MANAGER_H_

#include <iostream>
#include <fstream>

#include "Mesh.h"

class ObjManager
{
public:
	void writeToObj(const Mesh&, const char* file);
	Mesh* createFromObj(const char* file);
private:
};

#endif
