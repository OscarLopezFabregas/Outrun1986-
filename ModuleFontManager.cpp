
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleTextures.h"
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

	yellowFont = App->textures->Load("Fonts/yellowFont.png");

	//graphics = App->textures->Load("Sprites/player.png");


	return ret;
}

bool ModuleFontManager::CleanUp()
{
	LOG("Cleaning fonts")
		App->textures->Unload(yellowFont);
	return true;
}

SDL_Rect ModuleFontManager::FindCharacter(char characterToFind) {
	std::string CharacterMask = FONT;
	SDL_Rect pos = { 0,0,0,0 };
	int count = 0;
	for each (char c in CharacterMask)
	{
		if (c == characterToFind) {
			pos.x = 17 * count;
			pos.y = 0;
			pos.w = 17;// *count;
			pos.h = 15;
			return pos;
		}
		else {
			count++;
		}
	}
	return pos;
}

void ModuleFontManager::PrintCharacter(SDL_Texture* font, int positionX, int positionY, std::string textToPrint) {
	SDL_Texture* fontToPrint = font;
	SDL_Rect printRect;
	printRect.x = positionX;
	printRect.y = positionY - 5;

	for each (char character in textToPrint)
	{
		SDL_Rect charPointer = FindCharacter(character);

		if (&charPointer != nullptr) {
			printRect.h = charPointer.h*1.5;
			printRect.w = charPointer.w*1.5;
			if (character == ':')printRect.y -= 5;
			if (SDL_RenderCopy(App->renderer->renderer, fontToPrint, &charPointer, &printRect) != 0)
			{
				LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			}
			printRect.y = positionY - 5;
			printRect.x += 20;
		}
	}
}