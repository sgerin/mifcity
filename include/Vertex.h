#ifndef VERTEX_H_
#define VERTEX_H_

//#include <GLUT/glut.h>
#include "Face.h"
#include "Vector.h"
#include <set>

typedef struct
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat colour[4];
	GLubyte padding[16];
} Vert;


class Vertex
{
	public:
        Vertex();
        Vertex(float, float, float);
        Vertex(double, double, double);
        Vertex(const Vector&);
        Vertex(const Vector&, float, float);
        Vertex(const Vector&, const Vector&);
        ~Vertex();

        inline std::set<int>& getFaces(){return faces;}
        inline const std::set<int>& getFaces() const {return faces;}
        inline void setLocation(float x, float y, float z){location[0]=x; location[1]=y; location[2]=z;}
		inline void addFace(int f){faces.insert(f);}

        GLfloat location[3];
        GLfloat texture[2];        

	private:
        std::set<int> faces;
};

#endif
