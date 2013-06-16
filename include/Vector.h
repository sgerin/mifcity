#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <iostream>

//inline double min( double a, double b)
//{
//  return (a<b)?a:b;
//}
//
//inline double max( double a, double b)
//{
//  return (a>b)?a:b;
//}

//! \class Vector vector.h
//! \brief Cette classe définit des vecteurs et des sommets dans l'espace.
class Vector
{
protected:
	double x,y,z;
public:
	Vector() { }
	Vector(const double& a, const double& b, const double& c) { x=a; y=b; z=c; }
	Vector(const Vector& v) { x=v[0]; y=v[1]; z=v[2]; }

	// Functions to access Vector class components
	double& operator[] (int i)
	{
		if (i == 0)    return x;
		else if (i == 1) return y;
		else	     return z;
	}

	const double operator[] (int i) const
	{
		if (i == 0)    return x;
		else if (i == 1) return y;
		else	     return z;
	}

	Vector Scale(const Vector& b) const { return Vector(x*b.x,y*b.y,z*b.z); }

	// Unary operators
	Vector operator+ () const;
	Vector operator- () const;

	// Assignment operators
	Vector& operator+= (const Vector&);
	Vector& operator-= (const Vector&);
	Vector& operator*= (const Vector&);
	Vector& operator/= (const Vector&);
	Vector& operator*= (double);
	Vector& operator/= (double);

	void display(){std::cout << "Vector " << x << "  " << y << "  " << z << std::endl;}

	// Binary operators
	friend Vector operator+ (const Vector&, const Vector&);
	friend Vector operator- (const Vector&, const Vector&);

	friend double operator* (const Vector&, const Vector&);

	friend Vector operator* (const Vector&, double);
	friend Vector operator* (double, const Vector&);
	friend Vector operator/ (const Vector&, double);

	friend Vector operator/ (const Vector&, const Vector&);

	// Boolean functions
	friend int operator==(const Vector&,const Vector&);
	friend int operator!=(const Vector&,const Vector&);
	friend int operator<(const Vector&,const Vector&);
	friend int operator>(const Vector&,const Vector&);
    //friend Vector min(const Vector&,const Vector&);
    //friend Vector max(const Vector&,const Vector&);

	friend Vector Orthogonal(const Vector&);

	friend Vector Intersect(const Vector&, const Vector&, const Vector&, const Vector&);
	friend float sign(const Vector&, const Vector&, const Vector&);
	friend bool inTriangle(const Vector&, const Vector&, const Vector&, const Vector&);

	// Norm
	friend double Norm(const Vector&);
	friend Vector Normalized(const Vector&);

	friend float dot(const Vector&, const Vector&);
};

// Unary operators

inline Vector Vector::operator+ () const
{
	return *this;
}

inline Vector Vector::operator- () const
{
	return Vector(-x,-y,-z);
}

// Assignment unary operators
inline Vector& Vector::operator+= (const Vector& u)
{
	x+=u.x; y+=u.y; z+=u.z;
	return *this;
}

inline Vector& Vector::operator-= (const Vector& u)
{
	x-=u.x; y-=u.y; z-=u.z;
	return *this;
}

inline Vector& Vector::operator*= (double a)
{
	x*=a; y*=a; z*=a;
	return *this;
}

inline Vector& Vector::operator/= (double a)
{
	x/=a; y/=a; z/=a;
	return *this;
}

inline Vector& Vector::operator*= (const Vector& u)
{
	x*=u.x; y*=u.y; z*=u.z;
	return *this;
}

inline Vector& Vector::operator/= (const Vector& u)
{
	x/=u.x; y/=u.y; z/=u.z;
	return *this;
}

// Binary operators
inline Vector operator+ (const Vector& u, const Vector& v)
{
	return Vector(u.x+v.x,u.y+v.y,u.z+v.z);
}

inline Vector operator- (const Vector& u, const Vector& v)
{
	return Vector(u.x-v.x,u.y-v.y,u.z-v.z);
}

// Scalar product
inline double operator* (const Vector& u, const Vector& v)
{
	return (u.x*v.x+u.y*v.y+u.z*v.z);
}

inline Vector operator* (const Vector& u,double a)
{
	return Vector(u.x*a,u.y*a,u.z*a);
}

inline Vector operator* (double a, const Vector& v)
{
	return v*a;
}

// Cross product
inline Vector operator/ (const Vector& u, const Vector& v)
{
	return Vector(u.y*v.z-u.z*v.y,u.z*v.x-u.x*v.z,u.x*v.y-u.y*v.x);
}

inline Vector operator/ (const Vector& u, double a)
{
	return Vector(u.x/a,u.y/a,u.z/a);
}

// Boolean functions
inline int operator== (const Vector& u,const Vector& v)
{
	return ((u.x==v.x)&&(u.y==v.y)&&(u.z==v.z));
}

inline int operator!= (const Vector& u,const Vector& v)
{
	return (!(u==v));
}

/*!
\brief Compute the Euclidean norm of a vector.
*/
inline double Norm(const Vector& u)
{
	return sqrt(u.x*u.x+u.y*u.y+u.z*u.z);
}

/*!
\brief Compute the Euclidean norm of a vector.
*/
inline Vector Normalized(const Vector& u)
{
	return u/sqrt(u.x*u.x+u.y*u.y+u.z*u.z);
}

inline int operator<(const Vector& a,const Vector& b)
{
	return ((a.x<b.x)&&(a.y<b.y)&&(a.z<b.z));
}

inline int operator>(const Vector& a,const Vector& b)
{
	return ((a.x>b.x)&&(a.y>b.y)&&(a.z>b.z));
}

///*!
//\brief Return a new vector with coordinates set to the minimum coordinates
//of the two argument vectors.
//*/
//inline Vector min(const Vector& a,const Vector& b)
//{
//    return Vector(a[0]<b[0]?a[0]:b[0],a[1]<b[1]?a[1]:b[1],a[2]<b[2]?a[2]:b[2]);
//}
//
///*!
//\brief Return a new vector with coordinates set to the maximum coordinates
//of the two argument vectors.
//*/
//inline Vector max(const Vector& a,const Vector& b)
//{
//    return Vector(a[0]>b[0]?a[0]:b[0],a[1]>b[1]?a[1]:b[1],a[2]>b[2]?a[2]:b[2]);
//}


/*!
\brief Returns a new vector orthogonal to the argument vector.
*/
inline Vector Orthogonal(const Vector& u)
{
	Vector a=Vector(fabs(u[0]),fabs(u[1]),fabs(u[2]));
	int i=0;
	int j=1;
	if (a[0]>a[1])
	{
		if (a[2]>a[1])
			j=2;
	}
	else
	{
		i=1;
		j=2;
		if (a[0]>a[2])
			j=0;
	}
	a=Vector(0.0,0.0,0.0);
	a[i]=u[j];
	a[j]=-u[i];
	return a;
}

inline Vector Intersect(const Vector& l10, const Vector& l11, const Vector& l20, const Vector& l21)
{
	// Compute the intersection of the two lines passing by the points l10, l11 and l20, l21
	// this function works if you are working in 2D with x and z axis. 

	double a1 = l11[0] - l10[0];
	double b1 = l20[0] - l21[0];
	double c1 = l20[0] - l10[0]; 

	double a3 = l11[2] - l10[2];
	double b3 = l20[2] - l21[2]; 
	double c3 = l20[2] - l10[2];

	float t = (b1*c3 - b3*c1) / (a3*b1 - a1*b3);

	return Vector(l10[0]+t*(l11[0]-l10[0]), 0, l10[2]+t*(l11[2]-l10[2])); 
}

inline float sign(const Vector& p1, const Vector& p2, const Vector& p3)
{
  return (p1[0] - p3[0]) * (p2[2] - p3[2]) - (p2[0]- p3[0]) * (p1[2] - p3[2]);
}

inline bool inTriangle(const Vector& pt, const Vector& v1, const Vector& v2, const Vector& v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}


#endif
