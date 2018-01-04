
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleFontManager.h"


ModuleFontManager::ModuleFontManager(bool start_enabled) : Module(start_enabled)
{
}

ModuleFontManager::~ModuleFontManager()
{
}

bool ModuleFontManager::Start()
{
	LOG("Loading Fonts");

	bool ret = true;

	//graphics = App->textures->Load("Sprites/player.png");


	return ret;
}
