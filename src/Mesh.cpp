#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh& m)
{
    vertices = m.getVertices();
    faces = m.getFaces();
}

void Mesh::addVertex(double x, double y, double z)
{
    Vertex v(x, y, z);
    vertices.push_back(v);
}

void Mesh::addVertex(const Vertex& v)
{
    vertices.push_back(v);
}

void Mesh::addVertex(const Vector& v)
{
    vertices.push_back(v);
}

void Mesh::addVertex(const Vector& v, const Vector& color)
{
    vertices.push_back(Vertex(v, color));
}

void Mesh::addVertex(const Vector& v, float t1, float t2)
{
    vertices.push_back(Vertex(v, t1, t2));
}


void Mesh::addFace(int a, int b, int c)
{
    faces.push_back(Face(a, b, c));
}

void Mesh::addFace(int a, int b, int c, float u1, float v1, float u2, float v2, float u3, float v3)
{
    Face face(a, b, c);
    face.texture[0][0] = u1;
    face.texture[0][1] = v1;
    face.texture[1][0] = u2;
    face.texture[1][1] = v2;
    face.texture[2][0] = u3;
    face.texture[2][1] = v3;
    faces.push_back(face);
}

void Mesh::translate(double x, double y, double z)
{
    translate(Vector(x, y, z));
}

void Mesh::translate(const Vector& v)
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        vertices[i].location[0] += v[0];
        vertices[i].location[1] += v[1];
        vertices[i].location[2] += v[2];
    }
}


/*void Mesh::setPosition(const Vector& v)
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        vertices[i].location[0] = v[0];
        vertices[i].location[1] = v[1];
        vertices[i].location[2] = v[2];
    }
}*/


void Mesh::scale(double x, double y, double z)
{
    scale(Vector(x, y, z));
}

void Mesh::scale(const Vector& v)
{
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        vertices[i].location[0] *= v[0];
        vertices[i].location[1] *= v[1];
        vertices[i].location[2] *= v[2];
    }
}

void Mesh::centroid(Vector& c) {
    float area, sum;
    unsigned int i, j;
    c[0] = c[2] = sum = 0.0;

    for(i = vertices.size()-1, j = 0; j < vertices.size(); i = j++) {
        sum += area = vertices[i].location[0] * vertices[j].location[2] - vertices[i].location[2] * vertices[j].location[0];
        c[0] += (vertices[i].location[0] + vertices[j].location[0]) * area;
        c[2] += (vertices[i].location[2] + vertices[j].location[2]) * area;
    }
    sum *= 3.0;
    c[0] /= sum;
    c[2] /= sum;
    c[1] = 0.0f;
}

void Mesh::rotate_x(float ax)
{
    float cos_a = cos(ax);
    float sin_a = sin(ax);
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        float y = vertices[i].location[1];
        float z = vertices[i].location[2];
        vertices[i].location[1] = y*cos_a - z*sin_a;
        vertices[i].location[2] = y*sin_a + z*cos_a;
    }
}

void Mesh::rotate_y(float ay)
{
    float cos_a = cos(ay);
    float sin_a = sin(ay);
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        float x = vertices[i].location[0];
        float z = vertices[i].location[2];
        vertices[i].location[0] = z*sin_a + x*cos_a;
        vertices[i].location[2] = z*cos_a - x*sin_a;
    }
}

void Mesh::rotate_z(float az)
{
    float cos_a = cos(az);
    float sin_a = sin(az);
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        float x = vertices[i].location[0];
        float y = vertices[i].location[1];
        vertices[i].location[0] = x*cos_a - y*sin_a;
        vertices[i].location[1] = x*sin_a + y*cos_a;
    }
}

void Mesh::rotate(const Vector& v)
{
    rotate_x(v[0]);
    rotate_y(v[1]);
    rotate_z(v[2]);
}

void Mesh::setColor(float r, float g, float b, float a)
{
    std::vector<Face>::iterator it;
    for(it = faces.begin(); it != faces.end(); it++)
    {
        (*it).setColour(r,g,b,a);
    }
}

Mesh& Mesh::operator+= (const Mesh& m)
{
    //TODO Remove doubles
    int nb_vertices = getVertices().size();
    for(unsigned int i=0; i<m.getVertices().size(); i++)
        addVertex(m.getVertices()[i]);
    std::vector<Face>::const_iterator it;
    for(it = m.faces.begin(); it != m.faces.end(); it++)
    {
        Face face(*it);
        face.setVertices(it->vertices[0] + nb_vertices,
                         it->vertices[1] + nb_vertices,
                         it->vertices[2] + nb_vertices);
        faces.push_back(face);
    }
    return *this;
}


/*void Mesh::loadCube(const Vector& center, double size)
{
    vertices.clear();
    indexes.clear();

    float p = size/2.f;

    addVertex(p+center[0], center[1]-p, center[2]-p);
    addVertex(p+center[0], center[1]-p, p+center[2]);
    addVertex(center[0]-p, center[1]-p, p+center[2]);
    addVertex(center[0]-p, center[1]-p, center[2]-p);
    addVertex(p+center[0], p+center[1], center[2]-p);
    addVertex(p+center[0], p+center[1], p+center[2]);
    addVertex(center[0]-p, p+center[1], p+center[2]);
    addVertex(center[0]-p, p+center[1], center[2]-p);

    addFace(1, 2, 3);
    addFace(1, 3, 4);
    addFace(5, 8, 7);
    addFace(5, 7, 6);
    addFace(1, 5, 6);
    addFace(1, 6, 2);
    addFace(2, 6, 7);
    addFace(2, 7, 3);
    addFace(3, 7, 8);
    addFace(3, 8, 4);
    addFace(5, 1, 4);
    addFace(5, 4, 8);
}*/


void Mesh::getVertices(Vert*& v, int& size)
{
    size = faces.size() * 3;
    v = new Vert[size];
    std::vector<Face>::iterator it;
    int i = 0;
    for(it = faces.begin(); it != faces.end(); it++)
    {
        Vector vert[3];
        Vector n;
        v[i+0].location[0] = vert[0][0] = vertices.at(it->vertices[0]).location[0];
        v[i+0].location[1] = vert[0][1] = vertices.at(it->vertices[0]).location[1];
        v[i+0].location[2] = vert[0][2] = vertices.at(it->vertices[0]).location[2];

        v[i+1].location[0] = vert[1][0] = vertices.at(it->vertices[1]).location[0];
        v[i+1].location[1] = vert[1][1] = vertices.at(it->vertices[1]).location[1];
        v[i+1].location[2] = vert[1][2] = vertices.at(it->vertices[1]).location[2];

        v[i+2].location[0] = vert[2][0] = vertices.at(it->vertices[2]).location[0];
        v[i+2].location[1] = vert[2][1] = vertices.at(it->vertices[2]).location[1];
        v[i+2].location[2] = vert[2][2] = vertices.at(it->vertices[2]).location[2];

        n = Normalized((vert[1] - vert[0]) / (vert[2] - vert[0]));

        v[i+0].colour[0] = it->colour[0];
        v[i+0].colour[1] = it->colour[1];
        v[i+0].colour[2] = it->colour[2];
        v[i+0].colour[3] = it->colour[3];

        v[i+1].colour[0] = it->colour[0];
        v[i+1].colour[1] = it->colour[1];
        v[i+1].colour[2] = it->colour[2];
        v[i+1].colour[3] = it->colour[3];

        v[i+2].colour[0] = it->colour[0];
        v[i+2].colour[1] = it->colour[1];
        v[i+2].colour[2] = it->colour[2];
        v[i+2].colour[3] = it->colour[3];

        v[i+0].tex[0] = it->texture[0][0];
        v[i+0].tex[1] = it->texture[0][1];
        v[i+1].tex[0] = it->texture[1][0];
        v[i+1].tex[1] = it->texture[1][1];
        v[i+2].tex[0] = it->texture[2][0];
        v[i+2].tex[1] = it->texture[2][1];

        //        v[i+0].colour[0] = n[0] / 2 + 0.5f;
        //        v[i+0].colour[1] = n[1] / 2 + 0.5f;
        //        v[i+0].colour[2] = n[2] / 2 + 0.5f;
        //        v[i+0].colour[3] = 1.f;

        //        v[i+1].colour[0] = n[0] / 2 + 0.5f;
        //        v[i+1].colour[1] = n[1] / 2 + 0.5f;
        //        v[i+1].colour[2] = n[2] / 2 + 0.5f;
        //        v[i+1].colour[3] = 1.f;

        //        v[i+2].colour[0] = n[0] / 2 + 0.5f;
        //        v[i+2].colour[1] = n[1] / 2 + 0.5f;
        //        v[i+2].colour[2] = n[2] / 2 + 0.5f;
        //        v[i+2].colour[3] = 1.f;

        v[i+0].normal[0] = n[0];
        v[i+0].normal[1] = n[1];
        v[i+0].normal[2] = n[2];

        v[i+1].normal[0] = n[0];
        v[i+1].normal[1] = n[1];
        v[i+1].normal[2] = n[2];

        v[i+2].normal[0] = n[0];
        v[i+2].normal[1] = n[1];
        v[i+2].normal[2] = n[2];

        i+=3;

    }

}

void Mesh::getIndexes(int*& i, int& size)
{
    size = faces.size() * 3;
    i = new int[size];
    std::vector<Face>::iterator it;
    int j = 0;
    for(it = faces.begin(); it != faces.end(); it++)
    {
        i[j+0] = j+0;
        i[j+1] = j+1;
        i[j+2] = j+2;
        j+=3;
    }
}

