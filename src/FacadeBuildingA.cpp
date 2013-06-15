#include "FacadeBuildingA.h"

#include "Primitives.h"

FacadeBuildingA::FacadeBuildingA(const Vector& a, const Vector& b, int storey, int type) : storey(storey), type(type)
{
	dl = a;
	dr = b;
		
	// dl = a; 
	// ur = b; 
	// ul = a; 
	// ul[1] = ur[1];
	// dr = b;
	// dr[1] = dl[1]; 
}


Mesh* FacadeBuildingA::toMesh()
{
	Mesh* m = new Mesh();
	float current_height = .0;
	
	//TO COMMENT
	// Vector ul = dl; 
	// Vector ur = dr; 
	// ul[1] += storey*0.3;
	// ur[1] += storey*0.3;
	// Mesh* m = NULL;
	// m = polygon(ul, ur, dr, dl, 0.4);

	// std::cout << "jello" << std::endl;

	for(int i=0; i < storey; ++i)
	{
		switch(type)
		{
    		case 0:
    			*m += *FloorBuildingA(dl, dr, &current_height).toMesh(); 
    			//current_height is incremetend in FloorBuildingA constructor
				break;
			case 1:
    			*m += *FloorBuildingB(dl, dr, &current_height).toMesh(); 
				break;
			case 2:
    			*m += *FloorBuildingC(dl, dr, &current_height).toMesh(); 
				break;
			case 3:
    			*m += *FloorBuildingD(dl, dr, &current_height).toMesh(); 
				break;
			case 4:
    			*m += *FloorBuildingE(dl, dr, &current_height).toMesh(); 
				break;
			case 5:
    			*m += *FloorBuildingF(dl, dr, &current_height).toMesh(); 
				break;
			default:
				break;
		}
	}

	return m;
}
