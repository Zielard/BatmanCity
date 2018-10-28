#include <cstdlib>
#include <iostream>

#include <gl/gl.h>/*naglowek dla opengl32*/
#include <gl/glu.h>/*naglowek dla glu32*/
#include <gl/freeglut.h> /*naglowek dla freeglut'a*/
#include <gl/glext.h> //naglowek do gluBuild2DMipmaps
#include <stdio.h>
#include <math.h>


#include <string>
#include <fstream>
#include <sstream>


#define _USE_MATH_DEFINES
#include <cmath>

class Model {
private:

    int indexf;  //zmienna sluzaca jako index do petli wypisywania vertexow
	int numberv; //liczba odczytanych vertexow
	int numbert; //liczba odczytanych kordynatow dla tekstur
	int numberf; //liczba scian
    int numbern; //liczba scian
	int VFindex[10000][3];  //tablica indexow-vertexow zczytanych dla scian
	int UVindex[10000][3];  //tablica indexow-cordynatow tekstur zczytanych dla scian
	int Nindex[10000][3];   //tablica indexow-normalnych zczytanych dla scian
	GLfloat normal[10000][3];   //tablica indexow-normalnych zczytanych dla scian
	GLfloat vertex[10000][3]; //tablica vertexow
	GLfloat uv[10000][2];     //tablica kordynatow tekstur
	std::string f[10000][3];//tablica kordynatow dla scian, czyli tablica vertecow po trzy punkty

public:

    void Render_MOD_TEX();          //funkcja wypisujaca obiekty
    void LoadObj(std::string name); //funkcja ladujaca obiekt OBJ
	bool flag_load;                 //
	bool flag_uv;                   //
    bool flag;                      //
	Model();
	~Model();

};
