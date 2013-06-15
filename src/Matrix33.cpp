#include "Matrix33.h"

Matrix33::Matrix33()
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			data[i][j] = (i == j);
}

Matrix33::Matrix33(const float entry[9])
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			data[i][j] = entry[i*3 + j];
}

Matrix33::Matrix33(const Vector entry[3])
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			data[i][j] = entry[i][j];
}

void Matrix33::Debug_display()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix33& Matrix33::operator*(const Vector& v)
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			data[i][j] *= v[j];
		}
	}
	return *this;
}

Matrix33& Matrix33::operator*(float lambda)
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			data[i][j] *= lambda;
	return *this;
}

Matrix33& Matrix33::operator*(const Matrix33&)
{
	//TODO
	return *this;
}
