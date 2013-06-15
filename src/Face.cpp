#include "Face.h"

Face::Face()
{
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0;
    normal[0] = 0.f;
    normal[1] = 1.f;
    normal[2] = 0.f;
    colour[0] = 0.5f;
    colour[1] = 0.5f;
    colour[2] = 0.5f;
    colour[3] = 1.0f;
    texture[0][0] = 125.f/512.f;
    texture[0][1] = 42.f/512.f;
    texture[1][0] = 130.f/512.f;
    texture[1][1] = 42.f/512.f;
    texture[2][0] = 130.f/512.f;
    texture[2][1] = 27.f/512.f;
}

Face::Face(int a, int b, int c)
{
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
    normal[0] = 0.f;
    normal[1] = 1.f;
    normal[2] = 0.f;
    colour[0] = 0.5f;
    colour[1] = 0.5f;
    colour[2] = 0.5f;
    colour[3] = 1.0f;
    texture[0][0] = 125.f/512.f; // 470.f/512.f; 
    texture[0][1] = 42.f/512.f; // 125.f/512.f; 
    texture[1][0] = 130.f/512.f; // 470.f/512.f; 
    texture[1][1] = 42.f/512.f; // 130.f/512.f; 
    texture[2][0] = 130.f/512.f; // 485.f/512.f; 
    texture[2][1] = 27.f/512.f; // 130.f/512.f; 
}

Face::Face(const Face &face)
{
    vertices[0] = face.vertices[0];
    vertices[1] = face.vertices[1];
    vertices[2] = face.vertices[2];
    normal[0] = face.normal[0];
    normal[1] = face.normal[1];
    normal[2] = face.normal[2];
    colour[0] = face.colour[0];
    colour[1] = face.colour[1];
    colour[2] = face.colour[2];
    colour[3] = face.colour[3];
    texture[0][0] = face.texture[0][0];
    texture[0][1] = face.texture[0][1];
    texture[1][0] = face.texture[1][0];
    texture[1][1] = face.texture[1][1];
    texture[2][0] = face.texture[2][0];
    texture[2][1] = face.texture[2][1];
}
