#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <cmath>

#include "Vector.h"
#include "Vertex.h"
#include "Matrix33.h"

class Mesh
{
public:
	Mesh();
	Mesh(const Mesh&);
	
	void addVertex(double, double, double);
	void addVertex(const Vector&);
	void addVertex(const Vertex&);
	void addVertex(const Vector&, const Vector&);
	void addVertex(const Vector&, float, float);
	void addFace(int, int , int);
    void addFace(int, int , int,
                 float u1, float v1,
                 float u2, float v2,
                 float u3, float v3);

    //NOTE: now pass by reference for performance issues.
    const std::vector<Vertex>& getVertices() const { return vertices; }
    const std::vector<Face>& getFaces() const { return faces; }

	void getVertices(Vert*&, int&);
    void getIndexes(int*&, int&);

	void buildNormals();

	void translate(double, double, double);
	void translate(const Vector&);

	void setPosition(const Vector&);
	
	void rotate_x(float);
	void rotate_y(float);
	void rotate_z(float);
	void rotate(const Vector&);

    void setColor(float r, float g, float b, float a = 1.f);

	void scale(double, double, double);
	void scale(const Vector&);

    void centroid(Vector &c);

	Mesh& operator+= (const Mesh&);

	//void loadCube(const Vector&, double);

	std::vector<Vertex> vertices;
	std::vector<Face> faces;

};

#endif
