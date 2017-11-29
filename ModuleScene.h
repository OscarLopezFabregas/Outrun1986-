#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Animation.h"


 class SDL_Texture;
 class Line; 

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
	
	SDL_Texture* graphics = nullptr;




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
	Color road1;
	Color road2;

	std::vector<Line> lines;
private:
	void PrintTrack();

	
	
};

#endif // __MODULESCENE_H__