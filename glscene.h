#if !defined(_glscene_h)
#define _glscene_h
#include <string>
#include "Model.h"
#include "Tex.h"
#include <ctime>
#include <string>       // std::string
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
class glScene : public Tex
{
	public:



GLfloat bat_position[16];
GLfloat sam_position[16];
GLfloat door_position[16];
GLfloat grap_position[16];
////////////swiatlo//////////////////////////////////////////////////
const GLfloat light_ambient[4]  = { 0.0f, 0.0f, 0.0f, 1.0f };////////
const GLfloat light_diffuse[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };////////
const GLfloat light_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };////////
const GLfloat light_position[4] = { 2.0f, 5.0f, 5.0f, 0.0f };////////
                                                             ////////
const GLfloat mat_ambient[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };////////
const GLfloat mat_diffuse[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };////////
const GLfloat mat_specular[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };////////
const GLfloat high_shininess[4] = { 100.0f };                  //////
/////////////////////////////////////////////////////////////////////

	    //sciezki do modeli 3D//
//////////////////////////////////////////////////////////////////////////////////
    std::string MOD_NAME_1="Models/batman.obj";
    std::string MOD_NAME_2="Models/built_1.obj";
    std::string MOD_NAME_3="Models/built_2.obj";
    std::string MOD_NAME_4="Models/built_3.obj";
    std::string MOD_NAME_5="Models/built_4.obj";
    std::string MOD_NAME_6="Models/grass.obj";
    std::string MOD_NAME_7="Models/pavent.obj";
    std::string MOD_NAME_8="Models/way.obj";
    std::string MOD_NAME_9="Models/bumerank.obj";
    std::string MOD_NAME_10="Models/batmobile.obj";
    std::string MOD_NAME_11="Models/menu.obj";
    std::string MOD_NAME_12="Models/door.obj";

    std::string MOD_NAMEH_1="hospital_level/floor.obj";
    std::string MOD_NAMEH_2="hospital_level/ground.obj";
    std::string MOD_NAMEH_3="hospital_level/wall.obj";
///////////////////////////////////////////////////////////////////////////////////


           int LargeAnimFrame=0;
            int LargeAnimPush=0;
//////////////////////////////////////////////////////////////////////////////////
    GLuint IDtext[13];       // IDtekstur
    Model MOD_[14];  //tablica modeli
    Model Anim[31]; //tablica modeli uzywana jako ramki dla animacji
    Model Anim_BB[155]; //tablica modeli uzywana jako ramki dla animacji
    Model Anim_WB[31]; //tablica modeli uzywana jako ramki dla animacji
    Model Anim_WW[87]; //tablica modeli uzywana jako ramki dla animacji
    Model Anim_Push[27]; //tablica modeli uzywana jako ramki dla animacji
    Model Anim_Grab[61]; //tablica modeli uzywana jako ramki dla animacji
    Tex Mod_TEX[13]; //zmienne tekstur
    bool switchh=false;  //zmienna prawdy dla przlaczania animacji na sztywny model
    bool Anim_check =false; //zmienna do animacji
    bool pomocnicza =false; //zmienna pomocnicza do animacji
    bool walk_animation =true;
    bool menu=true;
    bool push_attack=false;
    bool carInter=false;
    bool Inter=false;
    bool doorInter=false;
    bool grabInter=false;
    float hightvalue=1.1f;
    float globalY=-1.0f;
    int GrabFrameAnim=0;
    int happens=0;
    int frame_1=1;            //zmienna jako indeks modeli do animacji
    int frame_2=46;            //zmienna jako indeks modeli do animacji
    int frameMenu=0;
    bool manuclip=true;
    int check=1;
    float h=0.0f;
    float distanceB=0.0f;
    float RotValue=2.5f;
    float DistanceValue=1.0f;
    float DoorCord=0.0f;
    bool switchLevel = true;
/////////////////////FPS/////////////////////////////
    clock_t current_ticks, delta_ticks;            //
    clock_t fps = 0;                               //
/////////////////////////////////////////////////////
   	glScene();
      virtual ~glScene();
      int __key = 0;
    int i=0;
    int j=0;
    void LoadLargeAnim();
    void LoadLargeAnimW();
    void LoadLargeAnimWC();
    void LoadLargeAnimPush();
    void LoadLargeAnimGrab();
      //wywolywana gdy rozmiar okna na ekranie ulega zmianie
      virtual void Resize(int, int);
      virtual void Resize();

		//wolana gdy zostanie wcisniety klawisz z klawiatury
      //Kody klawiszy VK_ z naglowka windows.h
      virtual void KeyboardFunction(char, int, int);
      virtual void KeyboardFunction(int, int, int);

      virtual void MouseMove(int, int);
	  virtual void MouseLBDown(int, int);
	  virtual void MouseLBUp(int, int);

      //wywolywana po utworzeniu klasy sceny. Ma za zadanie inicjalizacje OpenGL
      virtual void SetupRC();

      //wolana przed zniszczeniem objektu sceny. Ma za zadanie przywrocic
      //stan poczatkowy OpenGL
      virtual void CleanRC();

      //Wolana przez Timer.
      virtual void Timer();

      //ma zwrocic prawde jesli nasza scena wymaga timera
      virtual bool WantTimer();

      //ma zwrocic liczbe milisekund co ile ma byc wolana metoda Timer()
      virtual int GetTimer();


	  //zwraca stan flagi repaintRequest_ - jesli prawda to OGLmain powinien odmalowac okno
      //Wykozystywane w Idle

	  virtual bool NeedRefresh();
      virtual void RenderScene();

   protected:
		GLfloat rot_[3];

      static GLint winx_, winy_;
	  GLboolean repaintRequest_;
};

inline
bool glScene::NeedRefresh()
{
	return (bool)(repaintRequest_ == GL_TRUE ? true : false);
}


#endif
