#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleBeachTrack;
class ModuleSegaIntro;
class ModuleStart;
class ModuleMusicSelect;
class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModulePlayer* player;
	ModuleBeachTrack* beach_track;
	ModuleStart* outrun_start;
	ModuleSegaIntro* sega_intro;
	ModuleMusicSelect* music_select;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__