
#ifndef __MODULESTART__
#define __MODULESTART__


#include "Animation.h"
#include "Globals.h"


class ModuleStart : public Module
{
public:
	ModuleStart(bool start_enabled = false);
	~ModuleStart();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation OutrunStart;
	Animation PressStart;
	SDL_Rect Background;



};

#endif // __MODULESTART__