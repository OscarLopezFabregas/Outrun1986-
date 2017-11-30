#ifndef __MODULEBEACHTRACK__
#define __MODULEBEACHTRACK__

#include "Animation.h"
#include "ModuleScene.h"
#include "Globals.h"





class ModuleBeachTrack : public ModuleScene
{

public:
	ModuleBeachTrack(bool start_enabled = true);
	bool Start();
	~ModuleBeachTrack();
public:
	
	SDL_Rect StartBanner;

};

#endif // __MODULEBEACHTRACK__