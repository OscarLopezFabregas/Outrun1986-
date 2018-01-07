#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Animation.h"


 class Line; 
 struct SDL_Texture;

 //Falta poner una Y para poder elevar el sprite!

 struct Sprite {
	 SDL_Rect rect;
 };

 struct Enemy {
	 float posZ;
	 float posX;
	 float animationTime = 0;
	 int posStopSprint;
	 int color;
	 int speed;
	 int position = 3;
	 Animation* current_animation = nullptr;
 };

class ModuleScene : public Module
{
public:
	ModuleScene( bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	/*update_status PostUpdate();*/
	bool CleanUp();

	void TimeManager();
	

public:
	SDL_Texture* graphics;
	SDL_Texture* background;
	SDL_Texture* Sprites;
	SDL_Texture* GUI;

	int lanes = 3;
	int grass[3];
	int rumble[3];
	int road[3];
	int startPos;
	int pos;
	int N;
	int playerX;
	int playerZ;
	bool prueba = false;


	Color grass1;
	Color grass2;
	Color rumble1;
	Color rumble2;
	Color sideline1;
	Color sideline2;
	Color road1;
	Color road2;
	Color trafficline1;
	Color trafficline2;

	SDL_Rect Background;
	SDL_Rect guiTime;
	SDL_Rect guiScore;
	SDL_Rect guiLap;
	SDL_Rect guiKmh;
	SDL_Rect guiStage;
	SDL_Rect guiMap;

	std::vector<Sprite*> sprites;
	int start_banner;
	int palm_left;
	int palm_right;
	int traffic_light;
	int column;
	int grandstand;
	int checkpoint;
	int water;
	int bushright;
	int bushleft;
	int boathouse;
	int boathouse2;
	int offs;
	int secondsPassed;
	int secondsToQuit;
	int secondsLap;
	int secondsAux;
	long initTimer;
	int miliSecondsLap;
	int minuteLap;
	int score;
	int speed;
	int backgroundX;
	int parallaxFactor;

	std::vector<Line> lines;
private:
	void PrintTrack();
	void PrintGUI();
	void AnimationPlayer();
	
};

#endif // __MODULESCENE_H__