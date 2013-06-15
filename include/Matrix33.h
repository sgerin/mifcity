#ifndef MATRIX_33_H
#define MATRIX_33_H

#include <iostream>
#include "Vector.h"

class Matrix33
{
protected:
	float data[3][3];
public:
	Matrix33();
    Matrix33(const float[9]);
	Matrix33(const Vector[3]);

	Matrix33& operator*(const Vector&);
	Matrix33& operator*(const Matrix33&); //TODO
	Matrix33& operator*(float);

	void Debug_display();
};

#endif
