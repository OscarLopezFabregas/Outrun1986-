#include "Globals.h"
#include "Application.h"
#include "ModuleFontManager.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


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

	yellowFont = App->textures->Load("Fonts/yellowFont.bmp");
    greenFont = App->textures->Load("Fonts/greenFont2.png");
	blueFont = App->textures->Load("Fonts/blueFont2.png");
	speedFont = App->textures->Load("Fonts/Speed.png");

	return ret;
}

bool ModuleFontManager::CleanUp()
{
	LOG("Cleaning fonts")
    App->textures->Unload(yellowFont);
	App->textures->Unload(greenFont);
	App->textures->Unload(blueFont);
	App->textures->Unload(speedFont);
	return true;
}

SDL_Rect ModuleFontManager::FindCharacter(char characterToFind, SDL_Texture* font) {
	std::string CharacterMask = FONT;
	std::string CharacterMask2 = FONT2;

	SDL_Rect pos = { 0,0,0,0 };
	int count = 0;
	if (font == yellowFont)
	{
		for each (char c in CharacterMask)
		{
			if (c == characterToFind)
			{
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
	}
	else if (font == blueFont)
	{
		for each (char c in CharacterMask2)
		{
			if (c == characterToFind) {
				pos.x = 17 * count;
				pos.y = 0;
				pos.w = 17;// *count;
				pos.h = 16;
				return pos;
			}
			else {
				count++;
			}
		}
	}
	else
	{
		for each (char c in CharacterMask2)
		{
			if (c == characterToFind) {
				pos.x = 17 * count;
				pos.y = 0;
				pos.w = 14;// *count;
				pos.h = 17;
				return pos;
			}
			else {
				count++;
			}
		}
	}
	
	return pos;
}
SDL_Rect ModuleFontManager::FindNumber(char characterToFind) {
	std::string CharacterMask = NUMBERMASK;
	SDL_Rect pos = { 0,0,0,0 };
	int count = 0;
	for each (char c in CharacterMask)
	{
		if (c == characterToFind) {
			switch (c)
			{
			case '0':
				pos.x = 0;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '1':
				pos.x = 37;
				pos.y = 1;
				pos.w = 10;
				pos.h = 57;
				break;
			case '2':
				pos.x = 50;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '3':
				pos.x = 87;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '4':
				pos.x = 123;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '5':
				pos.x = 159;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '6':
				pos.x = 196;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '7':
				pos.x = 233;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '8':
				pos.x = 270;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			case '9':
				pos.x = 305;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			default:
				pos.x = 0;
				pos.y = 1;
				pos.w = 33;
				pos.h = 57;
				break;
			}
			return pos;
		}
	}
	return pos;
}

void ModuleFontManager::PrintCharacter(SDL_Texture* font, int positionX, int positionY, std::string textToPrint)
{
SDL_Texture* fontToPrint = font;
SDL_Rect printRect;
printRect.x = positionX;
printRect.y = positionY - 5;

for each (char character in textToPrint)
{
	SDL_Rect charPointer = FindCharacter(character, font);

	if (&charPointer != nullptr) {
		printRect.h = charPointer.h*1.5;
		printRect.w = charPointer.w*1.5;
		if (character == ':')printRect.y -= 5;
		if (character == '.')printRect.y += 5;
		if (SDL_RenderCopy(App->renderer->renderer, fontToPrint, &charPointer, &printRect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		}
		printRect.y = positionY - 5;
		printRect.x += 20;
	}
}
}


void ModuleFontManager::PrintSpeed(SDL_Texture* font, int positionX, int positionY, std::string textToPrint) {
	SDL_Texture* fontToPrint = font;
	SDL_Rect printRect;
	printRect.x = positionX;
	printRect.y = positionY;

	for each (char character in textToPrint)
	{
		SDL_Rect charPointer = FindNumber(character);

		if (&charPointer != nullptr) {
			printRect.h = charPointer.h/2;
			printRect.w = charPointer.w/2;
			//if (character == ':')printRect.y -= 5;
			if (SDL_RenderCopy(App->renderer->renderer, fontToPrint, &charPointer, &printRect) != 0)
			{
				LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			}
			printRect.y = positionY;
			printRect.x += 19;
		}
	}
}