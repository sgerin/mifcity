#include "FloorBuildingC.h"

FloorBuildingC::FloorBuildingC(const Vector& a, const Vector& b, float* height)
{
	// dl = a; 
	// ur = b; 
	// ul = a; 
	// ul[1] = ur[1];
	// dr = b;
	// dr[1] = dl[1]; 

	dl = a; 
	dr = b; 
	ul = a; 
	ur = b;
	dl[1] += *height; 
	dr[1] += *height; 
	*height += STOREY_HEIGHT;
	ul[1] += *height; 
	ur[1] += *height;
}


Mesh* FloorBuildingC::toMesh()
{
	//ROOF3_LEFT_UL_X;

	Mesh* m = new Mesh();
	m->addVertex(ul, ROOF3_LEFT_UL_X/divide, ROOF3_LEFT_UL_Y/divide); //0
	m->addVertex(ur, ROOF3_RIGHT_UR_X/divide, ROOF3_RIGHT_UR_Y/divide); //1
	m->addVertex(dr, ROOF3_RIGHT_DR_X/divide, ROOF3_RIGHT_DR_Y/divide); //2
	m->addVertex(dl, ROOF3_LEFT_DL_X/divide, ROOF3_LEFT_DL_Y/divide); //3

	Vector border_ul, border_ur, border_dr, border_dl, norm;
	norm = ur - ul;
	norm = Normalized(norm);
	border_ul = ul + norm*BORDER;
	//border_ul[2] += BORDER;
	border_dl = border_ul;
	border_dl[1] = dl[1];
	border_ur = ur;
	//border_ur[2] -= BORDER;
	border_ur = ur - norm*BORDER;
	border_dr = border_ur;
	border_dr[1] = dr[1];

	m->addVertex(border_ul, ROOF3_LEFT_UR_X/divide, ROOF3_LEFT_UR_Y/divide); //4
	m->addVertex(border_ur, ROOF3_RIGHT_UL_X/divide, ROOF3_RIGHT_UL_Y/divide); //5
	m->addVertex(border_dr, ROOF3_RIGHT_DL_X/divide, ROOF3_RIGHT_DL_Y/divide); //6
	m->addVertex(border_dl, ROOF3_LEFT_DR_X/divide, ROOF3_LEFT_DR_Y/divide); //7

	// m->addVertex(border_ul, ROOF3_MID_UL_X/divide, ROOF3_MID_UL_Y/divide); //8
	// m->addVertex(border_ur, ROOF3_MID_UR_X/divide, ROOF3_MID_UR_Y/divide); //9
	// m->addVertex(border_dr, ROOF3_MID_DR_X/divide, ROOF3_MID_DR_Y/divide); //10
	// m->addVertex(border_dl, ROOF3_MID_DL_X/divide, ROOF3_MID_DL_Y/divide); //11


	// m->addFace(0, 1, 3);
	// m->addFace(1, 2, 3);
/*

	m->addVertex(ul, ROOF3_LEFT_UL_X/divide, ROOF3_LEFT_UL_Y/divide); //0
	m->addVertex(ur, ROOF3_RIGHT_UR_X/divide, ROOF3_RIGHT_UR_Y/divide); //1
	m->addVertex(dr, ROOF3_RIGHT_DR_X/divide, ROOF3_RIGHT_DR_Y/divide); //2
	m->addVertex(dl, ROOF3_LEFT_DL_X/divide, ROOF3_LEFT_DL_Y/divide); //3

	m->addVertex(border_ul, ROOF3_LEFT_UR_X/divide, ROOF3_LEFT_UR_Y/divide); //4
	m->addVertex(border_ur, ROOF3_RIGHT_UL_X/divide, ROOF3_RIGHT_UL_Y/divide); //5
	m->addVertex(border_dr, ROOF3_RIGHT_DL_X/divide, ROOF3_RIGHT_DL_Y/divide); //6
	m->addVertex(border_dl, ROOF3_LEFT_DR_X/divide, ROOF3_LEFT_DR_Y/divide); //7

	m->addVertex(border_ul, ROOF3_MID_UL_X/divide, ROOF3_MID_UL_Y/divide); //8
	m->addVertex(border_ur, ROOF3_MID_UR_X/divide, ROOF3_MID_UR_Y/divide); //9
	m->addVertex(border_dr, ROOF3_MID_DR_X/divide, ROOF3_MID_DR_Y/divide); //10
	m->addVertex(border_dl, ROOF3_MID_DL_X/divide, ROOF3_MID_DL_Y/divide); //11

*/
	m->addFace(0, 4, 3);//, ROOF3_LEFT_UL_X/divide, ROOF3_LEFT_UL_Y/divide, ROOF3_LEFT_UR_X/divide, ROOF3_LEFT_UR_Y/divide, ROOF3_LEFT_DL_X/divide, ROOF3_LEFT_DL_Y/divide);
	m->addFace(3, 4, 7);//, ROOF3_LEFT_DL_X/divide, ROOF3_LEFT_DL_Y/divide, border_ul, ROOF3_LEFT_UR_X/divide, ROOF3_LEFT_UR_Y/divide, ROOF3_LEFT_DR_X/divide, ROOF3_LEFT_DR_Y/divide);
	m->addFace(5, 1, 6);//, ROOF3_RIGHT_UL_X/divide, ROOF3_RIGHT_UL_Y/divide, ur, ROOF3_RIGHT_UR_X/divide, ROOF3_RIGHT_UR_Y/divide, ROOF3_RIGHT_DL_X/divide, ROOF3_RIGHT_DL_Y/divide);
	m->addFace(6, 1, 2);//, ROOF3_RIGHT_DL_X/divide, ROOF3_RIGHT_DL_Y/divide, ROOF3_RIGHT_UR_X/divide, ROOF3_RIGHT_UR_Y/divide, ROOF3_RIGHT_DR_X/divide, ROOF3_RIGHT_DR_Y/divide);
	m->addFace(4, 5, 7);//, ROOF3_MID_UL_X/divide, ROOF3_MID_UL_Y/divide, ROOF3_MID_UR_X/divide, ROOF3_MID_UR_Y/divide, ROOF3_MID_DL_X/divide, ROOF3_MID_DL_Y/divide);
	m->addFace(7, 5, 6);//, ROOF3_MID_DL_X/divide, ROOF3_MID_DL_Y/divide, ROOF3_MID_UR_X/divide, ROOF3_MID_UR_Y/divide, ROOF3_MID_DR_X/divide, ROOF3_MID_DR_Y/divide);

	return m;

	//m->addVertex(0.0, height/2, 0.0);
	//m->addFace(0, 2+i, 2+i+1);
}
