#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <vector>
#include "Mesh.h"

inline Mesh* sphere(float radius, int meridians, int parallels)
{
    Mesh* m = new Mesh();
    double x, y, z;
    for(int i=0; i<meridians; ++i)
    {
        for(int j=0; j<parallels; ++j)
        {
            x = sin(M_PI*i/(meridians-1)) * cos(2*M_PI*j/(parallels-1));
            y = sin(M_PI*i/(meridians-1)) * sin(2*M_PI*j/(parallels-1));
            z = cos(M_PI*i/(meridians-1));
            m->addVertex(radius*x, radius*y, radius*z);
        }
    }

    for(int i=0; i < meridians-1; i++)
    {
        for(int j=0; j < parallels-1; j++)
        {
            m->addFace(i*parallels+j, (i+1)*parallels+j, i*parallels+j+1);
            m->addFace(i*parallels+j+1, (i+1)*parallels+j, (i+1)*parallels+j+1);
        }
    }
    return m;
}

inline Mesh* cone(float radius, float height, int slices)
{
    Mesh* m = new Mesh();
    double x, y, z;

    m->addVertex(0.0, height/2, 0.0);
    m->addVertex(0.0, -height/2, 0.0);
    for(int i=0; i < slices; ++i)
    {
        x = radius * cos(2*M_PI*i/slices);
        y = -height/2;
        z = radius * sin(2*M_PI*i/slices);
        m->addVertex(x, y, z);
    }

    for(int i=0; i < slices; ++i)
    {
        if(2+i+1 <= slices+1)
        {
            m->addFace(0, 2+i, 2+i+1);
            m->addFace(1, 2+i, 2+i+1);
        }
        else
        {
            m->addFace(0, 2+i, 2);
            m->addFace(1, 2+i, 2);
        }
    }

    return m;
}

inline Mesh* cylinder(float radius, float length, int slices)
{
    Mesh* m = new Mesh();
    double x, y, z;

    if(radius != radius)
	std::cout << "NAN" << std::endl;

    m->addVertex(0.0, length, 0.0);
    m->addVertex(0.0, 0, 0.0);

    for(int i=0; i < slices; ++i)
    {
        if(i==0)
            x = radius*cos(0);
        else
            x = radius * cos(2*M_PI*(i/slices));
        y = length;
        if(i==0)
            z = radius*sin(0);
        else
            z = radius * sin(2*M_PI*(i/slices));
        m->addVertex(x, y, z);
    }

    for(int i=0; i < slices; ++i)
    {
        if(i==0)
            x = radius*cos(0);
        else
            x = radius * cos(2*M_PI*(i/slices));
        y = 0;
        if(i==0)
            z = radius*sin(0);
        else
            z = radius * sin(2*M_PI*(i/slices));
        m->addVertex(x, y, z);
    }

    for(int i=0; i < slices; ++i)
    {
        if(2+i+1 <= slices+1)
            m->addFace(0, 2+i+1, 2+i);
        else
            m->addFace(0, 2, 2+i);
    }

    for(int i=0; i < slices; ++i)
    {
        if(2+i+1 <= slices+1)
            m->addFace(1, slices+2+i+1, slices+2+i);
        else
            m->addFace(1, slices+2, slices+2+i);
    }

    for(int i=0; i<slices; ++i)
    {
        if(2+i+1 <= slices+1)
        {
            m->addFace(2+i, 2+i+1, 2+i+slices);
            m->addFace(2+i+slices, 2+i+1, 2+i+1+slices);
        }
        else
        {
            m->addFace(2+i, 2, 2+i+slices);
            m->addFace(2+i+slices, 2, 2+slices);
        }
    }

    return m;
}

inline Mesh* cube(float size)
{
    Mesh* m = new Mesh();
    m->addVertex(-size/2, size/2, -size/2);
    m->addVertex(size/2, size/2, -size/2);
    m->addVertex(size/2, size/2, size/2);
    m->addVertex(-size/2, size/2, size/2);
    m->addVertex(-size/2, -size/2, -size/2);
    m->addVertex(size/2, -size/2, -size/2);
    m->addVertex(size/2, -size/2, size/2);
    m->addVertex(-size/2, -size/2, size/2);

    m->addFace(0, 1, 2);
    m->addFace(0, 2, 3);
    m->addFace(4, 5, 6);
    m->addFace(4, 6, 7);
    m->addFace(0, 4, 5);
    m->addFace(0, 1, 5);
    m->addFace(1, 5, 6);
    m->addFace(1, 2, 6);
    m->addFace(2, 6, 7);
    m->addFace(2, 3, 7);
    m->addFace(0, 3, 7);
    m->addFace(0, 4, 7);

    return m;
}

inline Mesh* box(float length, float width, float height)
{
    Mesh* m = new Mesh();
    m->addVertex(-length/2, height/2, -width/2);
    m->addVertex(length/2, height/2, -width/2);
    m->addVertex(length/2, height/2, width/2);
    m->addVertex(-length/2, height/2, width/2);
    m->addVertex(-length/2, -height/2, -width/2);
    m->addVertex(length/2, -height/2, -width/2);
    m->addVertex(length/2, -height/2, width/2);
    m->addVertex(-length/2, -height/2, width/2);

    m->addFace(0, 1, 2);
    m->addFace(0, 2, 3);
    m->addFace(4, 5, 6);
    m->addFace(4, 6, 7);
    m->addFace(0, 4, 5);
    m->addFace(0, 1, 5);
    m->addFace(1, 5, 6);
    m->addFace(1, 2, 6);
    m->addFace(2, 6, 7);
    m->addFace(2, 3, 7);
    m->addFace(0, 3, 7);
    m->addFace(0, 4, 7);

    return m;
}

inline Mesh* pyramid(float length, float width, float height)
{
    Mesh* m = new Mesh();
    m->addVertex(-length/2, 0, -width/2);
    m->addVertex(length/2, 0, -width/2);
    m->addVertex(length/2, 0, width/2);
    m->addVertex(-length/2, 0, width/2);
    m->addVertex(0, height, 0);

    m->addFace(0, 1, 2);
    m->addFace(0, 2, 3);
    m->addFace(0, 1, 4);
    m->addFace(1, 2, 4);
    m->addFace(2, 3, 4);
    m->addFace(0, 3, 4);

    return m;
}

inline Mesh* pyramid(const Vector& c1, const Vector& c2, const Vector& c3, const Vector& c4, float height)
{
    Mesh* m = new Mesh();

    m->addVertex(c1);
    m->addVertex(c2);
    m->addVertex(c3);
    m->addVertex(c4);

    m->addFace(0, 1, 2);
    m->addFace(0, 3, 2);

    Vector top = ((c1 + c2)/2 + (c3 + c4)/2)/2;
    top[1] += height;

    m->addVertex(top);

    m->addFace(0, 1, 4);
    m->addFace(1, 2, 4);
    m->addFace(2, 3, 4);
    m->addFace(3, 0, 4);

    return m;
}

inline Mesh* pyramid(const Vector& c1, const Vector& c2, const Vector& c3, float height)
{
    Mesh* m = new Mesh();

    m->addVertex(c1);
    m->addVertex(c2);
    m->addVertex(c3);

    m->addFace(0, 1, 2);

    Vector top = ((c1 + c2)/2 + c3)/2;
    top[1] += height;

    m->addVertex(top);

    m->addFace(0, 1, 3);
    m->addFace(1, 2, 3);
    m->addFace(2, 0, 3);

    return m;
}

inline Mesh* polygon(const Vector& c1, const Vector& c2, const Vector& c3, const Vector& c4, float height)
{
    Mesh* m = new Mesh();

    m->addVertex(c1);
    m->addVertex(c2);
    m->addVertex(c3);
    m->addVertex(c4);

    //bottom
    m->addFace(0, 2, 3);
    m->addFace(0, 1, 2);

    if (height == 0)
        return m;

    Vector c1_u = c1;
    c1_u[1] = height;
    Vector c2_u = c2;
    c2_u[1] = height;
    Vector c3_u = c3;
    c3_u[1] = height;
    Vector c4_u = c4;
    c4_u[1] = height;

    m->addVertex(c1_u);
    m->addVertex(c2_u);
    m->addVertex(c3_u);
    m->addVertex(c4_u);

    //left
    m->addFace(0, 5, 4);
    m->addFace(0, 1, 5);
    //right
    m->addFace(3, 7, 6);
    m->addFace(3, 6, 2);
    //front
    m->addFace(0, 4, 7);
    m->addFace(0, 7, 3);
    //back
    m->addFace(2, 6, 5);
    m->addFace(5, 1, 2);
    //up
    m->addFace(4, 5, 6);
    m->addFace(4, 6, 7);

    return m;
}

inline void getSquare(Vector& ul,Vector& ur,Vector& dr,Vector& dl)
{
    Vector u = (ul + ur) / 2;
    Vector r = (ur + dr) / 2;
    Vector d = (dl + dr) / 2;
    Vector l = (ul + dl) / 2;
    Vector d1 = r - l;
    Vector d2 = d - u;
    if(Norm(d1) > Norm(d2))
    {
        float sub = (Norm(d1) - Norm(d2)) / 2.0;
        l += Normalized(d1) * sub;
        r -= Normalized(d1) * sub;
    }
    else if (Norm(d1) < Norm(d2))
    {
        float sub = (Norm(d2) - Norm(d1)) / 2.0;
        u += Normalized(d2) * sub;
        d -= Normalized(d2) * sub;
    }
    ul = u;
    ur = r;
    dr = d;
    dl = l;
}

inline Mesh* polygon(const Vector& c1, const Vector& c2, const Vector& c3, float height)
{
    Mesh* m = new Mesh();

    m->addVertex(c1);
    m->addVertex(c2);
    m->addVertex(c3);

    //bottom
    m->addFace(0, 1, 2);

    if (height == 0)
        return m;

    Vector c1_u = c1;
    c1_u[1] = height;
    Vector c2_u = c2;
    c2_u[1] = height;
    Vector c3_u = c3;
    c3_u[1] = height;

    m->addVertex(c1_u);
    m->addVertex(c2_u);
    m->addVertex(c3_u);
    //side_1
    m->addFace(0, 4, 3);
    m->addFace(0, 1, 4);
    //side_2
    m->addFace(0, 3, 2);
    m->addFace(2, 3, 5);
    //side3
    m->addFace(2, 5, 1);
    m->addFace(1, 5, 4);
    //up
    m->addFace(3, 4, 5);

    return m;
}

inline void erodeSquare(float f,
                        const Vector& ul, const Vector& ur, const Vector& dr, const Vector& dl,
                        Vector* n_ul, Vector* n_ur, Vector* n_dr, Vector* n_dl)
{
    Vector u = ul - ur;
    Vector l = dl - ul;
    Vector u_normal = Vector(u[2], u[1], -u[0]);
    double dota = u_normal*l;

    Vector d = dr - dl;
    Vector r = ur - dr;

    Vector l_normal;
    Vector d_normal;
    Vector r_normal;

    if(dota > 0)
    {
        //CW
        l_normal = Vector(l[2], l[1], -l[0]);
        d_normal = Vector(d[2], d[1], -d[0]);
        r_normal = Vector(r[2], r[1], -r[0]);
    }
    else if(dota < 0)
    {
        //CCW
        u_normal[0] = -u_normal[0];
        u_normal[2] = -u_normal[2];
        l_normal = Vector(-l[2], l[1], l[0]);
        d_normal = Vector(-d[2], d[1], d[0]);
        r_normal = Vector(-r[2], r[1], r[0]);
    }

    u_normal = Normalized(u_normal);
    l_normal = Normalized(l_normal);
    d_normal = Normalized(d_normal);
    r_normal = Normalized(r_normal);

    Vector ur1 = ur + f*u_normal;
    Vector ur2 = ur + f*r_normal;

    Vector ul1 = ul + f*u_normal;
    Vector ul2 = ul + f*l_normal;

    Vector dl1 = dl + f*d_normal;
    Vector dl2 = dl + f*l_normal;

    Vector dr1 = dr + f*d_normal;
    Vector dr2 = dr + f*r_normal;

    *n_ur = Intersect(ul1, ur1, dr2, ur2);
    *n_ul = Intersect(ur1, ul1, dl2, ul2);
    *n_dr = Intersect(ur2, dr2, dl1, dr1);
    *n_dl = Intersect(ul2, dl2, dr1, dl1);
}

inline void erodeTriangle(float f,
                          const Vector& a, const Vector& b, const Vector& c,
                          Vector* n_a, Vector* n_b, Vector* n_c)
{
    // Finding vector representing the line segment ab and bc
    // Compute normal of ab_normal. We do not know is this normal is pointing outward or inward of the TBlock
    // then compute the cross product
    Vector ab = b - a;
    Vector bc = c - b;
    Vector ab_normal = Vector(ab[2], ab[1], -ab[0]);
    double dota = ab_normal*bc;

    Vector ca = a - c;

    Vector bc_normal;
    Vector ca_normal;

    // Builds normals wether normal is pointing outward or inward
    if(dota > 0)
    {
        //CW
        bc_normal = Vector(bc[2], bc[1], -bc[0]);
        ca_normal = Vector(ca[2], ca[1], -ca[0]);
    }
    else if(dota < 0)
    {
        //CCW
        ab_normal[0] = -ab_normal[0];
        ab_normal[2] = -ab_normal[2];
        bc_normal = Vector(-bc[2], bc[1], bc[0]);
        ca_normal = Vector(-ca[2], ca[1], ca[0]);
    }

    ab_normal = Normalized(ab_normal);
    ca_normal = Normalized(ca_normal);
    bc_normal = Normalized(bc_normal);

    Vector a1 = a + f*ab_normal;
    Vector a2 = a + f*ca_normal;

    Vector c1 = c + f*bc_normal;
    Vector c2 = c + f*ca_normal;

    Vector b1 = b + f*bc_normal;
    Vector b2 = b + f*ab_normal;

    // Compute the intersection of lines a1b2 & c1b1
    *n_b = Intersect(a1, b2, c1, b1);
    *n_a = Intersect(b2, a1, c2, a2);
    *n_c = Intersect(b1, c1, a2, c2);
}


#endif
