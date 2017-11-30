#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__


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
	float playerX = 0;
	float playerZ = 0;
	double speed; //unused
	//Animation backward;
	//Animation forward;
	iPoint position;

};

#endif // __MODULEPLAYER_H__