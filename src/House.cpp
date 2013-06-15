#include "House.h"

House::House(Vector a, Vector b, Vector c, Vector d)
{
	ul = a; 
	ur = b; 
	dr = c; 
	dl = d; 
}

Mesh* House::elevate()
{
    Mesh* house = polygon(ul, ur, dr, dl, HEIGHT);//new Mesh();
    switch(rand() % 4)
    {
    case 0:
        house->setColor(0.6,0.4,0.1);
        break;
    case 1:
        house->setColor(1.0,0.5,0.4);
        break;
    case 2:
        house->setColor(0.8,0.5,0.2);
        break;
    case 3:
        house->setColor(0.5,0.2,0.1);
        break;
    }
	return house;
}

void House::simpleHouse(Mesh* house)
{
	Mesh* components = NULL;
	int nb_storey = 1 + (rand() % 3);

	Vector center = (((ur+ul)/2) + ((dl+dr)/2)) /2;
	float x = ur[0]-ul[0];
	x = x<0 ? -x : x; 
	float z = ul[2]-dl[2];
	z = z<0 ? -z : z; 

 	int type = rand() % 1;
    switch (type)
    {
    case 0:
    	for(int i=0; i<nb_storey; ++i)
		{
			components = box(x, z, 0.2);
			components->translate(center[0], 0.1+i*0.1, center[2]); 
			*house += *components;
		}

		components = pyramid(x, z, 0.3);
		components->translate(center[0], (nb_storey+1)*0.1, center[2]); 
		*house += *components;
        break;

   	case 1:
   		for(int i=0; i<nb_storey; ++i)
   		{
   			components = box(x, z, 0.2);
   			components->translate(center[0], 0.1+i*0.1, center[2]); 
   			*house += *components;
   		}

   		components = pyramid(x, z, 0.3);
   		components->translate(center[0], (nb_storey+1)*0.1, center[2]); 
   		*house += *components;
	  	break;

	default:
		for(int i=0; i<nb_storey; ++i)
		{
			components = box(x, z, 0.2);
			components->translate(center[0], 0.1+i*0.1, center[2]); 
			*house += *components;
		}

		components = pyramid(x, z, 0.3);
		components->translate(center[0], (nb_storey+1)*0.1, center[2]); 
		*house += *components;
		break;
	}	
	
}

Mesh* House::toMesh()
{
	Mesh* m = new Mesh;

	*m += *elevate();

	return m;
}

float House::surface() { return 0; }
