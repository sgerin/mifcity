#ifndef FACE_H_
#define FACE_H_


#ifdef __linux
	#include <GL/glew.h>
    #include <GL/glut.h>
#elif __APPLE__
	#include <GLUT/glut.h>
#else
    # include <gl/glew.h>
    # include <gl/glut.h>
#endif


//#include "Vertex.h"

class Face
{
	public:
		Face();
		Face(int, int, int);
        Face(const Face& face);

		inline void setVertices(int a, int b, int c){vertices[0]=a; vertices[1]=b; vertices[2]=c;}
		inline void setNormal(float x, float y, float z){normal[0]=x; normal[1]=y; normal[2]=z;}
        inline void setTexture(float a, float b, int i){texture[i][0]=a; texture[i][1]=b;}
        inline void setColour(float r, float g, float b, float a){colour[0]=r; colour[1]=g; colour[2]=b; colour[3]=a;}

        GLfloat texture[3][2];
        GLfloat normal[3];
        GLfloat colour[4];
        int vertices[3];

};

#endif
