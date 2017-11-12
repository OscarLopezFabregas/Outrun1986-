#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect startflag;
	SDL_Rect background;
	SDL_Rect redship;
	Animation girl;
	Animation flag;
	int yk= 0;
	double d = 0;
};

#endif // __MODULESCENEKEN_H__