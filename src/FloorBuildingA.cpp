#include "FloorBuildingA.h"

FloorBuildingA::FloorBuildingA(const Vector& a, const Vector& b, float* height)
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


Mesh* FloorBuildingA::toMesh()
{
	//ROOF1_LEFT_UL_X;

	Mesh* m = new Mesh();
	m->addVertex(ul); //0
	m->addVertex(ur); //1
	m->addVertex(dr); //2
	m->addVertex(dl); //3

	Vector border_ul, border_ur, border_dr, border_dl, norm;
	norm = ur - ul;
	//norm = Normalized(norm);
	border_ul = ul + Normalized(norm)*BORDER;
	//border_ul[2] += BORDER;
	border_dl = border_ul;
	border_dl[1] = dl[1];
	border_ur = ur;
	//border_ur[2] -= BORDER;
	border_ur = ur - Normalized(norm)*BORDER;
	border_dr = border_ur;
	border_dr[1] = dr[1];

	m->addVertex(border_ul); //4
	m->addVertex(border_ur); //5
	m->addVertex(border_dr); //6
	m->addVertex(border_dl); //7

/*

	m->addVertex(ul, ROOF1_LEFT_UL_X/divide, ROOF1_LEFT_UL_Y/divide); //0
	m->addVertex(ur, ROOF1_RIGHT_UR_X/divide, ROOF1_RIGHT_UR_Y/divide); //1
	m->addVertex(dr, ROOF1_RIGHT_DR_X/divide, ROOF1_RIGHT_DR_Y/divide); //2
	m->addVertex(dl, ROOF1_LEFT_DL_X/divide, ROOF1_LEFT_DL_Y/divide); //3

	m->addVertex(border_ul, ROOF1_LEFT_UR_X/divide, ROOF1_LEFT_UR_Y/divide); //4
	m->addVertex(border_ur, ROOF1_RIGHT_UL_X/divide, ROOF1_RIGHT_UL_Y/divide); //5
	m->addVertex(border_dr, ROOF1_RIGHT_DL_X/divide, ROOF1_RIGHT_DL_Y/divide); //6
	m->addVertex(border_dl, ROOF1_LEFT_DR_X/divide, ROOF1_LEFT_DR_Y/divide); //7

*/
	//Vector norm2 = ur-ul;
	// float length = Norm(norm);
	// float current_length = 0.6;
	// int nb_win = length / (BORDER*2); 

	// for(int i = 0; i<=nb_win*2; ++i)
	// {
	// 	Vector a = border_ul + Normalized(norm)*BORDER*i;
	// 	Vector b = border_dl + Normalized(norm)*BORDER*i;
	// 	m->addVertex(a);
	// 	m->addVertex(b);
	// }


	m->addFace(0, 4, 3, ROOF1_LEFT_UL_X/divide, ROOF1_LEFT_UL_Y/divide, ROOF1_LEFT_UR_X/divide, ROOF1_LEFT_UR_Y/divide, ROOF1_LEFT_DL_X/divide, ROOF1_LEFT_DL_Y/divide);
	m->addFace(3, 4, 7, ROOF1_LEFT_DL_X/divide, ROOF1_LEFT_DL_Y/divide, ROOF1_LEFT_UR_X/divide, ROOF1_LEFT_UR_Y/divide, ROOF1_LEFT_DR_X/divide, ROOF1_LEFT_DR_Y/divide);
	m->addFace(5, 1, 6, ROOF1_RIGHT_UL_X/divide, ROOF1_RIGHT_UL_Y/divide, ROOF1_RIGHT_UR_X/divide, ROOF1_RIGHT_UR_Y/divide, ROOF1_RIGHT_DL_X/divide, ROOF1_RIGHT_DL_Y/divide);
	m->addFace(6, 1, 2, ROOF1_RIGHT_DL_X/divide, ROOF1_RIGHT_DL_Y/divide, ROOF1_RIGHT_UR_X/divide, ROOF1_RIGHT_UR_Y/divide, ROOF1_RIGHT_DR_X/divide, ROOF1_RIGHT_DR_Y/divide);
	m->addFace(4, 5, 7, WIN1_UL_X/divide, WIN1_UL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DL_X/divide, WIN1_DL_Y/divide);
	m->addFace(7, 5, 6, WIN1_DL_X/divide, WIN1_DL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DR_X/divide, WIN1_DR_Y/divide);
	// m->addFace(4, 5, 7, WIN1_UL_X/divide, WIN1_UL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DL_X/divide, WIN1_DL_Y/divide);
	// m->addFace(7, 5, 6, WIN1_DL_X/divide, WIN1_DL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DR_X/divide, WIN1_DR_Y/divide);

	// m->addFace(4, 8, 7, WIN1_UL_X/divide, WIN1_UL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DL_X/divide, WIN1_DL_Y/divide);
	// m->addFace(7, 8, 9, WIN1_DL_X/divide, WIN1_DL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DR_X/divide, WIN1_DR_Y/divide);
	// m->addFace(8, 10, 9, FILL1_UL_X/divide, FILL1_UL_Y/divide, FILL1_UR_X/divide, FILL1_UR_Y/divide, FILL1_DL_X/divide, FILL1_DL_Y/divide);
	// m->addFace(9, 10, 11, FILL1_DL_X/divide, FILL1_DL_Y/divide, FILL1_UR_X/divide, FILL1_UR_Y/divide, FILL1_DR_X/divide, FILL1_DR_Y/divide);


	// for(int i = 0; i<nb_win-2; ++i)
	// {
	// 	m->addFace(8+4*i, 10+4*i, 9+4*i, WIN1_UL_X/divide, WIN1_UL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DL_X/divide, WIN1_DL_Y/divide);
	// 	m->addFace(9+4*i, 10+4*i, 11+4*i, WIN1_DL_X/divide, WIN1_DL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DR_X/divide, WIN1_DR_Y/divide);
	// 	m->addFace(10+4*i, 12+4*i, 11+4*i, FILL1_UL_X/divide, FILL1_UL_Y/divide, FILL1_UR_X/divide, FILL1_UR_Y/divide, FILL1_DL_X/divide, FILL1_DL_Y/divide);
	// 	m->addFace(9+4*i, 12+4*i, 13+4*i, FILL1_DL_X/divide, FILL1_DL_Y/divide, FILL1_UR_X/divide, FILL1_UR_Y/divide, FILL1_DR_X/divide, FILL1_DR_Y/divide);

	// }

	// m->addFace(12+4*nb_win-2, 5, 13+4*nb_win-2, WIN1_UL_X/divide, WIN1_UL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DL_X/divide, WIN1_DL_Y/divide);
	// m->addFace(13+4*nb_win-2, 5, 6, WIN1_DL_X/divide, WIN1_DL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DR_X/divide, WIN1_DR_Y/divide);
	//m->addFace(4, 8, 7, WIN1_UL_X/divide, WIN1_UL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DL_X/divide, WIN1_DL_Y/divide);
	//m->addFace(7, 8, 9, WIN1_DL_X/divide, WIN1_DL_Y/divide, WIN1_UR_X/divide, WIN1_UR_Y/divide, WIN1_DR_X/divide, WIN1_DR_Y/divide);

	return m;

	//m->addVertex(0.0, height/2, 0.0);
	//m->addFace(0, 2+i, 2+i+1);
}
