#ifdef __linux
#include <GL/glew.h>
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

#include <vector>
#include "Vertex.h"
#include "Engine.h"
#include "ObjManager.h"
#include "png_texture.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))

GLuint vertexVBOID, indexVBOID;
GLuint vertexNormalVBOID, indexNormalVBOID;
GLuint windows1; 
float angle = 0.0;
Vert* vertices = NULL;
Vert* normalsVertices = NULL;
int v_size = 0; 
int* indexes = NULL; 
int* normalsIndexes = NULL;
int i_size = 0;
bool rotate = true;  
float rate = 0.1;

void display() {
    //Color of background. We clear the color and depth buffers before drawing
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat light0_position[] = { 10.0, 10.0, 1.0, 1.0 };
    GLfloat light0_ambient[] = { 0.1, 0.1, 0.1, 0.1 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);

    if(rotate)
    {
        angle += rate;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

    glTexCoordPointer(2, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(12));
    glNormalPointer(GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(20));
    glColorPointer(4, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(0));

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_TRIANGLES, i_size, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glPopMatrix();
    glutSwapBuffers();
}



void initGL(Mesh* m)
{
    vertexVBOID = 0;
    if(m != NULL)
    {
        m->getVertices(vertices, v_size);
        m->getIndexes(indexes, i_size);
    }
    else
        std::cout << "Mesh is null and shoucldn't" << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    // Decommenter ces deux lignes pour activer les textures.
    // windows1 = png_texture_load("atlas.png", NULL, NULL);
    // glBindTexture(GL_TEXTURE_2D, windows1);

    //Bind and fill the buffer with the content of our mesh.
    //GL_STATIC_DRAW is here because we don't modify our model
    glGenBuffers(1, &vertexVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(Vert), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, v_size * sizeof(Vert), vertices);

    //Bind and fill the index array
    glGenBuffers(1, &indexVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size * sizeof(int), indexes, GL_STATIC_DRAW);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}


void reshape(int w, int h) {

    if (h == 0) // Prevent divide by zero
        h = 1;

    float ratio = 1.0 * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45, ratio, 2, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CITY_SIZE, CITY_SIZE, -CITY_SIZE,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}


void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 'w')
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else if(key == 'n')
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    else if(key == 'r')
        rotate = !rotate;
    else if(key == 't')
        rate += 0.1;
    else if(key == 'y')
        rate -= 0.1;
}


void specialKeyboard(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
    {
        break;
    }
    case GLUT_KEY_UP:
    {
        break;
    }
    case GLUT_KEY_RIGHT:
    {
        break;
    }
    case GLUT_KEY_DOWN:
    {
        break;
    }
    default: break;
    }
}


int main(int argc, char** argv)
{

    srand(time(NULL));

    Engine e;
    Mesh* m = e.createCity();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 640);
    glutCreateWindow("MIFCity");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
#ifndef __APPLE__
    glewInit();
#endif
    initGL(m);

    ObjManager om;
    om.writeToObj(*m, "city.obj");

    delete m;
    glutMainLoop();

    return 0;
}
