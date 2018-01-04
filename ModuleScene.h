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

class ModuleScene : public Module
{
public:
	ModuleScene( bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	/*update_status PostUpdate();*/
	bool CleanUp();
	

public:
	SDL_Texture* graphics;
	SDL_Texture* background;
	SDL_Texture* Sprites;

	int lanes = 3;
	int grass[3];
	int rumble[3];
	int road[3];
	int startPos;
	int pos;
	int N;
	int playerX;
	int playerZ = 0;
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

	std::vector<Sprite*> sprites;
	int start_banner;
	int palm_left;
	int palm_right;
	int traffic_light;
	int column;
	int grandstand;
	std::vector<Line> lines;
private:
	void PrintTrack();

	
	
};

#endif // __MODULESCENE_H__