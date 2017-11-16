#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation idleferrari;
	Animation idlepilot;
	Animation idlegirl;
	int playerX = 1; //unused
	int playerZ; //unused 
	double speed; //unused
	//Animation backward;
	//Animation forward;
	iPoint position;
	//SDL_Rect Ferrari;
	//SDL_Rect Pilot;
	//SDL_Rect Girl;
};

#endif // __MODULEPLAYER_H__