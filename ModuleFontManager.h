#ifndef __MODULEFONTMANAGER_H__
#define __MODULEFONTMANAGER_H__

#include "Module.h"

class ModuleFontManager :public  Module
{
public:
	
	ModuleFontManager(bool start_enabled = true);
	~ModuleFontManager();

	bool Start();

	SDL_Texture* purpleFont;
	SDL_Texture* blueFont;
	SDL_Texture* yellowFont;
	SDL_Texture* speed;

}; 






#endif // __MODULEFONTMANAGER_H__