#ifndef __MODULEFONTMANAGER_H__
#define __MODULEFONTMANAGER_H__

#include "Module.h"

class ModuleFontManager :public  Module
{
public:
	
	ModuleFontManager(bool start_enabled = true);
	~ModuleFontManager();

	bool Start();
	bool CleanUp();

	SDL_Rect FindCharacter(char characterToFind);
	void PrintCharacter(SDL_Texture* font, int positionX, int positionY, std::string textToPrint);

	SDL_Texture* purpleFont;
	SDL_Texture* blueFont;
	SDL_Texture* yellowFont;
	SDL_Texture* speed;



}; 






#endif // __MODULEFONTMANAGER_H__