#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleStart.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModuleStart::ModuleStart(bool start_enabled) : Module(start_enabled)
{
	//Outrun Logo Start
	OutrunStart.frames.push_back({ 55,38,176,88 });
	OutrunStart.frames.push_back({ 236,38,176, 88});
	OutrunStart.frames.push_back({ 417,38,176,88 });
	OutrunStart.frames.push_back({ 55,131,176,88 });
	OutrunStart.frames.push_back({ 237,131,176,88 });
	OutrunStart.frames.push_back({ 417,131,176,88 });
	OutrunStart.speed = 0.01f;

	//Background Start
	Background.x = 5;
	Background.y = 314;
	Background.h = 476;
	Background.w = 680;

	//Press Start
	InsertCoin.frames.push_back({ 152,260,417,33 });
	InsertCoin.frames.push_back({ 1,1,417,33 });
	InsertCoin.speed = 0.025f;

}

ModuleStart::~ModuleStart()
{

}

bool ModuleStart::Start()
{
	LOG("Loading Sega Intro");

	graphics = App->textures->Load("Sprites/StartAnimation.png");

	
	//App->audio->PlayMusic("Music/Magical_Sound_Shower.ogg", 0.0f);
	

	return true;
}

bool ModuleStart::CleanUp()
{
	LOG("Unloading Sega Intro");

	App->textures->Unload(graphics);
	

	return true;
}

update_status ModuleStart::Update()
{
	App->renderer->Blit(graphics, 0, 0, &Background, 1.0f,SCREEN_WIDTH,SCREEN_HEIGHT);

	App->renderer->Blit(graphics, (SCREEN_WIDTH - 2*OutrunStart.GetCurrentFrame().w) / 2, (SCREEN_HEIGHT - 2*OutrunStart.GetCurrentFrame().h) / 1.85,
		&(OutrunStart.GetCurrentFrame()), 0.0f, OutrunStart.GetCurrentFrame().w*2, OutrunStart.GetCurrentFrame().h*2);

	App->renderer->Blit(graphics, (SCREEN_WIDTH -   209) / 2, SCREEN_HEIGHT - 115,
		&(InsertCoin.GetCurrentFrame()), 0.0f, 209, 16);

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->fade->FadeToBlack((Module*)App->music_select, App->outrun_start, 0.5f);
	}

	return UPDATE_CONTINUE;
}