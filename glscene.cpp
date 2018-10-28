//#include <windows.h> /*naglowek dla windowsa*/
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
#include <string>       // std::string


#define _USE_MATH_DEFINES
#include <cmath>

#include "glscene.h"
using namespace std;

/*OKNO*/
GLfloat przemieszczenie = 0.0f; //ZMIENNA PRZEMIESZCZENIA
GLfloat prze_bat_N = 0.0f; //ZMIENNA Batman tyl przod X
GLfloat prze_bat_L = 0.0f; //ZMIENNA Batman tyl przod Z
GLint glScene::winx_ = 0;
GLint glScene::winy_ = 0;



glScene::glScene()
:
	repaintRequest_(GL_FALSE)
{
	rot_[0] = rot_[1] = rot_[2] = 0.0f;
}

glScene::~glScene()
{
}

void glScene::Resize()
{
   Resize(winx_, winy_);
}

void glScene::Resize(int _w, int _h)
{
	winx_ = _w;
	winy_ = _h;

	if(_h == 0)
   		_h = 1;
	if(_w == 0)
   		_w = 1;/*nie dziel przez zero*/

	//ustawienie viewportu
	glViewport(0, 0, _w, _h);

	//macierze projekcji potrzebna do perspektywy
	glMatrixMode(GL_PROJECTION);
	//ustaw aktualna macierz na I (resetuje macierz do pierwotnego stanu)
	glLoadIdentity();

	//ustaw uklad wspolrzednych
	//glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	//perspektywa
	gluPerspective(70.0,(double)_w/(double)_h, 0.1, 1000.0);

	//macierze modelowania transformacje oddziąłują na macierz modeli
	glMatrixMode(GL_MODELVIEW);
	//ustaw aktualna macierz na I
	glLoadIdentity();
}

void glScene::SetupRC()
{
//glEnable(GL_CULL_FACE);

    //glEnable( GL_COLOR_MATERIAL );
    glTranslated(0.0f,-10.0f,0.0f); //cofniecie perspektywy do tyłu
   glClearColor(0.123f, 0.125f, 0.125f, 1.0f); //
  // glClearColor(0.0f, 0.5f, 0.2f, 1.0f);


///////////////////////////////////////////////////////////
   glEnable(GL_DEPTH_TEST);                              //
                                                         //
    glEnable(GL_LIGHT0);                                 //
    glEnable(GL_NORMALIZE);                              //
    glEnable(GL_COLOR_MATERIAL);                         //
    glEnable(GL_LIGHTING);                               //
                                                         //
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);    //
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);    //
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);   //
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);   //
                                                         //
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);   //
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);   //
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);  //
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
            IDtext[2] = Mod_TEX[1].loadBMP("Tex/built.bmp");
            glGenTextures(1,&IDtext[2]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[2]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[1].width,Mod_TEX[1].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[1].data);

                delete [] Mod_TEX[1].data;
            IDtext[1]= Mod_TEX[2].loadBMP("Tex/batman.bmp");		//załadowanie pliku (z folderu z projektem)
            glGenTextures(1,&IDtext[1]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[1]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[2].width,Mod_TEX[2].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[2].data);

                            delete [] Mod_TEX[2].data;
            IDtext[3]= Mod_TEX[3].loadBMP("Tex/grass.bmp");		//załadowanie pliku (z folderu z projektem)
            glGenTextures(1,&IDtext[3]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[3]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[3].width,Mod_TEX[3].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[3].data);
                                    delete [] Mod_TEX[3].data;

            IDtext[4]= Mod_TEX[4].loadBMP("Tex/pave.bmp");		//załadowanie pliku (z folderu z projektem)
            glGenTextures(1,&IDtext[4]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[4]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[4].width,Mod_TEX[4].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[4].data);
                            delete [] Mod_TEX[4].data;

            IDtext[5]= Mod_TEX[5].loadBMP("Tex/way.bmp");		//załadowanie pliku (z folderu z projektem)
            glGenTextures(1,&IDtext[5]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[5]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[5].width,Mod_TEX[5].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[5].data);
                            delete [] Mod_TEX[5].data;

            IDtext[6] = Mod_TEX[6].loadBMP("Tex/anim.bmp");
            glGenTextures(1,&IDtext[6]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[6]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[6].width,Mod_TEX[6].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[6].data);

                delete [] Mod_TEX[6].data;

            IDtext[7] = Mod_TEX[7].loadBMP("Menu/menu.bmp");
            glGenTextures(1,&IDtext[7]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[7]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[7].width,Mod_TEX[7].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[7].data);

                delete [] Mod_TEX[7].data;

            IDtext[8] = Mod_TEX[8].loadBMP("Menu/menu1.bmp");
            glGenTextures(1,&IDtext[8]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[8]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[8].width,Mod_TEX[8].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[8].data);

                delete [] Mod_TEX[8].data;

            IDtext[9] = Mod_TEX[9].loadBMP("Tex/wood.bmp");
            glGenTextures(1,&IDtext[9]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[9]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[9].width,Mod_TEX[9].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[9].data);

                delete [] Mod_TEX[9].data;

            IDtext[10] = Mod_TEX[10].loadBMP("Tex/wall.bmp");
            glGenTextures(1,&IDtext[10]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[10]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[10].width,Mod_TEX[10].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[10].data);

                delete [] Mod_TEX[10].data;

            IDtext[11] = Mod_TEX[11].loadBMP("Tex/ground.bmp");
            glGenTextures(1,&IDtext[11]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[11]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[11].width,Mod_TEX[11].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[11].data);

                delete [] Mod_TEX[11].data;

            IDtext[12] = Mod_TEX[12].loadBMP("Tex/floor.bmp");
            glGenTextures(1,&IDtext[12]);		//generowanie tekstury
            glEnable(GL_TEXTURE_2D);		//włączenie trybu tekstur
            glBindTexture(GL_TEXTURE_2D,IDtext[12]);	//ustawienie tej tekstury (nią będą kolorowane przedmioty)
            //pięć poniższych nie jest wymagane
            glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);		//załadowanie pliku (z folderu z projektem)
            gluBuild2DMipmaps(GL_TEXTURE_2D,3,Mod_TEX[12].width,Mod_TEX[12].height,GL_BGR_EXT,GL_UNSIGNED_BYTE,Mod_TEX[12].data);

                delete [] Mod_TEX[12].data;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            MOD_[0].LoadObj(MOD_NAME_1); //batman
            MOD_[1].LoadObj(MOD_NAME_2); //building_1 door
            MOD_[2].LoadObj(MOD_NAME_3); //building_2
            MOD_[3].LoadObj(MOD_NAME_4); //building_3
            MOD_[4].LoadObj(MOD_NAME_5); //building_4
            MOD_[5].LoadObj(MOD_NAME_6); //grass
            MOD_[6].LoadObj(MOD_NAME_7); //pavent
            MOD_[7].LoadObj(MOD_NAME_8); //way
            MOD_[8].LoadObj(MOD_NAME_9); //logo
            MOD_[9].LoadObj(MOD_NAME_10); //batmobile
            MOD_[10].LoadObj(MOD_NAME_11); //menu
            MOD_[11].LoadObj(MOD_NAME_12); //door

            MOD_[13].LoadObj(MOD_NAMEH_2); //ground
            MOD_[14].LoadObj(MOD_NAMEH_3); //wall
            LoadLargeAnim();
            LoadLargeAnimWC();
            LoadLargeAnimPush();
            LoadLargeAnimGrab();
            glShadeModel(GL_FLAT);
                glEnable(GL_DEPTH_TEST);
}

void glScene::CleanRC()
{
}

void glScene::RenderScene()
{
    //////////////////////////FPS/////////////////////
    current_ticks = clock();                       //
	/////////////////////////////////////////////////

	//malujemy scene, mozna skasowac flage aby scena ciagle sie nie odmalowywala
	repaintRequest_ = GL_FALSE;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//czyszcenie okna



	glPushMatrix();
	glTranslated(0.0f,globalY,-11.0f+distanceB+globalY); //cofniecie perspektywy do tyłu
      	glRotatef(90,0,1,0);
      	glRotatef(35,0,0,1);

	glRotatef(rot_[0], 1.0, 0.0, 0.0);
	glRotatef(rot_[1], 0.0, 1.0, 0.0);
	glRotatef(rot_[2], 0.0, 0.0, 1.0);

glPointSize(5.0f);
            if(menu)
                {
            glPushMatrix();
                    glTranslated(-5.0f,5.0f,0.0f);
                    glRotatef(-90,0,1,0);
                    glRotatef(45,1,0,0);
                    glScalef(4.0f,4.0f,4.0f);
                    if(manuclip==true && frameMenu<10)
                    {
                    frameMenu++;
                    Mod_TEX[7].ON_tex(IDtext[7]); //menu
                         if(frameMenu==9)
                         {
                             manuclip=false;
                         }
                    }
                    if(manuclip==false && frameMenu>=9)
                    {
                        frameMenu++;
                     Mod_TEX[8].ON_tex(IDtext[8]); //menu
                         if(frameMenu==20)
                         {
                             manuclip=true;
                             frameMenu=0;
                         }
                    }

        glBegin(GL_TRIANGLES);
        MOD_[10].Render_MOD_TEX();
          glEnd();
            glPopMatrix();
                }

///////////CHARAKTER ANIM AND OBJ/////////////////////////////////////////////////////////////////////////////
glPushMatrix();//////////////////////////////////////////////////////////////////////////////////////////////
        glTranslated(0.0f,h,0.0f);
        glRotatef(0+prze_bat_N,0,1,0);

if(carInter)
    {

        distanceB=-9.0f;
        glRotatef(90,0,1,0);
        glBegin(GL_TRIANGLES);
         MOD_[9].Render_MOD_TEX();
         glEnd();

    }
    else
    {
    distanceB=0.0f;
       if(switchh == false && Anim_check == true && pomocnicza==true) /////////////chodzenie
        {

                    if(frame_2==87)
                    {
                    frame_2=46;
                    }
                glScalef(0.8f,0.8f,0.8f);
                Mod_TEX[6].ON_tex(IDtext[1]); //batman
            glBegin(GL_TRIANGLES);
            Anim_WW[frame_2].Render_MOD_TEX();
                frame_2++;
              glEnd();


        }
        else if(switchh == false && Anim_check==false && push_attack==false && grabInter==false) /////////oddyhcnaie
        {

            glScalef(0.8f,0.8f,0.8f);
            Mod_TEX[6].ON_tex(IDtext[1]); //batman
            glBegin(GL_TRIANGLES);
                    if(LargeAnimFrame == 155)
                    {
                    LargeAnimFrame=0;
                    }
                    Anim_BB[LargeAnimFrame].Render_MOD_TEX();
                    LargeAnimFrame++;

             glEnd();

        }
        else if(switchh == false && Anim_check==false && push_attack==true && grabInter==false) //////////////push
        {
                    glScalef(0.8f,0.8f,0.8f);
            Mod_TEX[6].ON_tex(IDtext[1]); //batman
            glBegin(GL_TRIANGLES);
                    if(LargeAnimPush == 27)
                    {
                    LargeAnimPush=0;
                    push_attack=false;
                    }
                    Anim_Push[LargeAnimPush].Render_MOD_TEX();
                    LargeAnimPush++;

             glEnd();
        }
        else if(switchh == false && Anim_check==false && grabInter==true) //////////////grab
        {
            glScalef(0.8f,0.8f,0.8f);
            Mod_TEX[6].ON_tex(IDtext[1]); //batman
            glBegin(GL_TRIANGLES);
                    if(GrabFrameAnim == 60)
                    {
                    GrabFrameAnim=0;
                    grabInter=false;
                    check=2;
                    }
                        if(check==1)
                        {
                        Anim_Grab[GrabFrameAnim].Render_MOD_TEX();
                        GrabFrameAnim++;
                        h+=hightvalue;
                        globalY--;
                        }
                        else if(check==2)
                        {
                        h-=hightvalue;
                        globalY++;
                            if(globalY==-1.0f)
                            {
                                check=1;
                                grabInter=false;
                            }
                        }
             glEnd();
        }
    }

    glGetFloatv(GL_MODELVIEW_MATRIX, bat_position);
glPopMatrix();/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




if(switchLevel) /////////////////////////////outside_level
    {

    glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
    Mod_TEX[2].ON_tex(IDtext[2]); //buldings
    glBegin(GL_TRIANGLES);

     MOD_[2].Render_MOD_TEX();
     MOD_[3].Render_MOD_TEX();
     MOD_[4].Render_MOD_TEX();
     glEnd();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(-30.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
    Mod_TEX[2].ON_tex(IDtext[2]); //buldings
    glBegin(GL_TRIANGLES);
     MOD_[1].Render_MOD_TEX();

     glEnd();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(-30.f+przemieszczenie,0.0f,DoorCord+prze_bat_L);
    Mod_TEX[9].ON_tex(IDtext[9]); //door
    glBegin(GL_TRIANGLES);
     MOD_[11].Render_MOD_TEX();

     glEnd();
     glGetFloatv(GL_MODELVIEW_MATRIX, door_position);

        float dxx = door_position[12] - bat_position[12];
		float dyy = door_position[13] - bat_position[13];
		float dzz = door_position[14] - bat_position[14];
		float distancee = sqrt(dxx*dxx + dyy*dyy + dzz*dzz);
		if (distancee <= 10.0f)
		{
		//std::cout << "KOLIZJA!!!" << "\n";
			happens=2;
		}
		else
        {
        //std::cout << "nie sadze!!!" << "\n";
        }
  glPopMatrix();

  glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
   Mod_TEX[3].ON_tex(IDtext[3]); //grass
    glBegin(GL_TRIANGLES);
     MOD_[5].Render_MOD_TEX();
     glEnd();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
   Mod_TEX[4].ON_tex(IDtext[4]); //pave
    glBegin(GL_TRIANGLES);
     MOD_[6].Render_MOD_TEX();
     glEnd();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
    Mod_TEX[4].ON_tex(IDtext[5]); //way
    glBegin(GL_TRIANGLES);
     MOD_[7].Render_MOD_TEX();
     glEnd();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
   // Mod_TEX[4].ON_tex(IDtext[5]); //way
   glRotatef(-90,0,1,0);
    glBegin(GL_TRIANGLES);
     MOD_[8].Render_MOD_TEX();

     glEnd();
  glPopMatrix();


    glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
   // Mod_TEX[4].ON_tex(IDtext[5]); //way
   glRotatef(-90,0,1,0);
    glBegin(GL_TRIANGLES);
     MOD_[8].Render_MOD_TEX();

     glEnd();
  glPopMatrix();

    glPushMatrix();
          glTranslatef(-45.0f+przemieszczenie,0.0f,-73.0f+prze_bat_L);

              if(!carInter)
              {
                      //    glDisable(GL_TEXTURE_2D);
                glBegin(GL_TRIANGLES);
                 MOD_[9].Render_MOD_TEX();
                 glEnd();
                      //   glEnable(GL_TEXTURE_2D);
              }
        glGetFloatv(GL_MODELVIEW_MATRIX, sam_position);
      //  std::cout << "Pozycja bat: " << ludzik_position[12] << " " << ludzik_position[13] << " " << ludzik_position[14] << "\n";
      //  std::cout << "Pozycja batmobila : " << pocisk_position[12] << " " << pocisk_position[13] << " " << pocisk_position[14] << "\n";
        		//colision
		float dx = sam_position[12] - bat_position[12];
		float dy = sam_position[13] - bat_position[13];
		float dz = sam_position[14] - bat_position[14];
		float distance = sqrt(dx*dx + dy*dy + dz*dz);
		if (distance <= 5.0f)
		{
		//std::cout << "KOLIZJA!!!" << "\n";
			happens=1;
		}
		else
        {
        //std::cout << "nie sadze!!!" << "\n";
        }
  glPopMatrix();

    glPushMatrix();////////////////////////////////////////////////////////GRAP_INTERN

   glTranslatef(-30.f+przemieszczenie,0.0f,15.0f+prze_bat_L);
  glutSolidCube(4);
   glGetFloatv(GL_MODELVIEW_MATRIX, grap_position);
   		float dxxx = grap_position[12] - bat_position[12];
		float dyyy = grap_position[13] - bat_position[13];
		float dzzz = grap_position[14] - bat_position[14];
		float distanc = sqrt(dxxx*dxxx + dyyy*dyyy + dzzz*dzzz);
		if (distanc <= 5.0f)
		{
		    happens=3;
		//std::cout << "KOLIZJA!!!" << "\n";
		}
		else
        {
        //std::cout << "nie sadze!!!" << "\n";
        }


  glPopMatrix();

    }
  else
  {
      glPushMatrix(); ///////////////////////glowna_LEVEL_II


          glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
    Mod_TEX[11].ON_tex(IDtext[11]); //ground
    glBegin(GL_TRIANGLES);
     MOD_[13].Render_MOD_TEX();
     glEnd();
  glPopMatrix();

            glPushMatrix();
      glTranslatef(0.0f+przemieszczenie,0.0f,0.0f+prze_bat_L);
    Mod_TEX[10].ON_tex(IDtext[10]); //wall
    glBegin(GL_TRIANGLES);
     MOD_[14].Render_MOD_TEX();
     glEnd();
  glPopMatrix();

  glPopMatrix();}///////////////////////LEVEL_II


    glPopMatrix();
glFlush();


//////////////////////////////////////////////////////////////////////////////////////////////
    delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene //
    if(delta_ticks > 0)                                                                     //
        fps = CLOCKS_PER_SEC / delta_ticks;                                                 //
     //   system("cls");                                                                      //
    //std::cout << fps <<"FPS"<< std::endl;                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void glScene::KeyboardFunction(char _key, int, int)
{
	if(_key == 32)
	{
		rot_[0] = rot_[1] = rot_[2] = 0.0;
		Resize(winx_, winy_);
	}
	repaintRequest_ = GL_TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////KEY_FUN
void glScene::KeyboardFunction(int _key, int, int)
{
    menu=false;
    GLfloat motion = fmod( rot_[1], 360.f );
    if(_key == GLUT_KEY_RIGHT)
    {
            rot_[1] -=RotValue;
            prze_bat_N +=RotValue;
         //  std::cout<<rot_[1]<<std::endl;
    }
	else if(_key == GLUT_KEY_LEFT)
	{
        rot_[1] +=RotValue;
        prze_bat_N -=RotValue;
      //  std::cout<<rot_[1]<<std::endl;
	}
	else if(_key == GLUT_KEY_DOWN)
    {
                przemieszczenie+=1.0f*cos(3.14*(-rot_[1])/180.0);
                prze_bat_L-=1.0f*sin(3.14*(-rot_[1])/180.0);
    }
    else if(_key == 'q')
    {
            switch(happens)
            {


                case 0:
                    std::cout<<"nie ma interackji"<<std::endl;
                 break;

                case 1:
                    if(carInter)
                    {
                        std::cout<<"dziala"<<std::endl;
                        RotValue=2.5f;
                        DistanceValue=1.0f;
                       carInter=false;
                         PlaySound("Music/Batman-The-Animated-Series-Extended-Main-Title-Soundtrack.wav",NULL,SND_SYNC|SND_ASYNC);
                       return;
                    }
                    if(!carInter)
                    {
                        RotValue=5.0f;
                        DistanceValue=2.5f;
                                PlaySound("Music/car.wav",NULL,SND_SYNC|SND_LOOP);
                                PlaySound("Music/elvis.wav",NULL,SND_SYNC|SND_ASYNC);
                                            carInter=true;
                    }
                break;

                case 2:

                    if(doorInter)
                    {
                    DoorCord +=6.0f;
                    doorInter=false;
                    return;
                    }
                    if(!doorInter)
                    {
                    DoorCord -=6.0f;
                    doorInter=true;
                    }
                 break;

                case 3:
                    if(grabInter)
                    {
                        grabInter=false;
                    return;
                    }
                    if(!grabInter)
                    {
                    grabInter=true;
                    }
                 break;
                 default:
            cout<<":)";
            break;
            }
    }
    else if(_key == '-')
    {
        glTranslatef(0.0f,0.0f,-2.0f);
    }
        else if(_key == 'z')
    {
        push_attack=true;
    }
    else if(_key == '+')
    {
        glTranslatef(0.0f,0.0f,2.0f);
    }
        else if(_key == 'l')
    {
        if(switchLevel)
        {
        hightvalue=1.1f;
        switchLevel=false;
        }
        else
        {
        hightvalue=4.0f;
        switchLevel=true;
        }

    }
    else if(_key == GLUT_KEY_UP)
    {
                przemieszczenie-=DistanceValue*cos(3.14*(-rot_[1])/180.0);
                prze_bat_L+=DistanceValue*sin(3.14*(-rot_[1])/180.0);
        if(switchh == false)
        {
        Anim_check = true;
        pomocnicza = true;
        }
        return;
    }

    Anim_check = false;
    pomocnicza=false;
    walk_animation=true;
        frame_1=0;
        frame_2=46;

		repaintRequest_ = GL_TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void glScene::MouseMove(int, int)
{
}
void glScene::MouseLBDown(int, int)
{
}
void glScene::MouseLBUp(int, int)
{
}

void glScene::Timer()
{
	repaintRequest_ = GL_TRUE;

    //rot_[2] += 0.0f;
    if (rot_[3] > 360) rot_[3] -= 360.0f;
}

bool glScene::WantTimer()
{
	return true;
}

int glScene::GetTimer()
{
	return 10;
}

void glScene::LoadLargeAnim()
{
    std::string name;

    //std::string Anim_B[156];
    std::string * Anim_B = new std::string[156];
for(int i=0;i<155;i++)
{
    //int * tablica = new int[rozmiar];
        std::stringstream ss;
        ss << i;
    if(i<10)
    {
        std::string name =  "Anim/Batman_B/oddychanie_00000"; //33

         Anim_B[i]={name+=ss.str()+".obj"};
      // std::cout<<Anim_B[i]<<std::endl;
    }
    else if(i>=10 && i<100)
    {
         std::string name =  "Anim/Batman_B/oddychanie_0000";
         Anim_B[i]={name+=ss.str()+".obj"};
    //    std::cout<<Anim_B[i]<<std::endl;
    }
    else if(i>=100 )
    {
         std::string name =  "Anim/Batman_B/oddychanie_000";
         Anim_B[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_B[i]<<std::endl;
    }

Anim_BB[i].LoadObj(Anim_B[i]);

 name.clear();
}
}

void glScene::LoadLargeAnimWC()
{
    std::string name;

    //std::string Anim_B[156];
    std::string * Anim_C = new std::string[88];
for(int i=46;i<87;i++)
{
    //int * tablica = new int[rozmiar];
        std::stringstream ss;
        ss << i;
    if(i<10)
    {
         std::string name =  "Anim/Batman_W/Batman_C/Chodzenie_c_00000"; //33

         Anim_C[i]={name+=ss.str()+".obj"};
       std::cout<<Anim_C[i]<<std::endl;
    }
    else if(i>=10 && i<100)
    {
         std::string name =  "Anim/Batman_W/Batman_C/Chodzenie_c_0000";
         Anim_C[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_C[i]<<std::endl;
    }
    else if(i>=100 )
    {
         std::string name =  "Anim/Batman_W/Batman_C/Chodzenie_c_000";
         Anim_C[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_C[i]<<std::endl;
    }


Anim_WW[i].LoadObj(Anim_C[i]);
 name.clear();
}
}



void glScene::LoadLargeAnimPush()
{
    std::string name;

    //std::string Anim_B[156];
    std::string * Anim_C = new std::string[88];
for(int i=0;i<27;i++)
{
    //int * tablica = new int[rozmiar];
        std::stringstream ss;
        ss << i;
    if(i<10)
    {
         std::string name =  "Anim/Batman_Push/attack_push_00000"; //33

         Anim_C[i]={name+=ss.str()+".obj"};
       std::cout<<Anim_C[i]<<std::endl;
    }
    else if(i>=10 && i<100)
    {
         std::string name =  "Anim/Batman_Push/attack_push_0000";
         Anim_C[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_C[i]<<std::endl;
    }
    else if(i>=100)
    {
         std::string name =  "Anim/Batman_Push/attack_push_000";
         Anim_C[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_C[i]<<std::endl;
    }


Anim_Push[i].LoadObj(Anim_C[i]);
////////////////////////////////////////////////////////MUSIC FUNKCJA WIN_API
  //PlaySound("Music/Batman-The-Animated-Series-Extended-Main-Title-Soundtrack.wav",NULL,SND_SYNC|SND_ASYNC);
///////////////////////////////////////////////////////
 name.clear();
}
}

void glScene::LoadLargeAnimGrab()
{
    std::string name;

    //std::string Anim_B[156];
    std::string * Anim_C = new std::string[60];
for(int i=0;i<60;i++)
{
    //int * tablica = new int[rozmiar];
        std::stringstream ss;
        ss << i;
    if(i<10)
    {
         std::string name =  "Anim/Batman_Grap/grap_00000"; //33

         Anim_C[i]={name+=ss.str()+".obj"};
       std::cout<<Anim_C[i]<<std::endl;
    }
    else if(i>=10 && i<100)
    {
         std::string name =  "Anim/Batman_Grap/grap_0000";
         Anim_C[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_C[i]<<std::endl;
    }
    else if(i>=100)
    {
         std::string name =  "Anim/Batman_Grap/grap_000";
         Anim_C[i]={name+=ss.str()+".obj"};
        std::cout<<Anim_C[i]<<std::endl;
    }


Anim_Grab[i].LoadObj(Anim_C[i]);
////////////////////////////////////////////////////////MUSIC FUNKCJA WIN_API
  PlaySound("Music/Batman-The-Animated-Series-Extended-Main-Title-Soundtrack.wav",NULL,SND_SYNC|SND_ASYNC);
///////////////////////////////////////////////////////
 name.clear();
}
}
