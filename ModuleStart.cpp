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
	OutrunStart.frames.push_back({ 55,38,176,86 });
	OutrunStart.frames.push_back({ 236,38,176,86 });
	OutrunStart.frames.push_back({ 417,38,176,86 });
	OutrunStart.frames.push_back({ 55,131,176,86 });
	OutrunStart.frames.push_back({ 237,131,176,86 });
	OutrunStart.frames.push_back({ 417,131,176,86 });
	OutrunStart.speed = 0.01f;

	//Background Start
	Background.x = 5;
	Background.y = 314;
	Background.h = 476;
	Background.w = 680;
}

ModuleStart::~ModuleStart()
{

}

bool ModuleStart::Start()
{
	LOG("Loading Sega Intro");

	graphics = App->textures->Load("StartAnimation.png");

	//// TODO 7: Enable the player module

	//// TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg");

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

	App->renderer->Blit(graphics, (SCREEN_WIDTH - 2*OutrunStart.GetCurrentFrame().w) / 2, (SCREEN_HEIGHT - 2*OutrunStart.GetCurrentFrame().h) / 3,
		&(OutrunStart.GetCurrentFrame()), 0.0f, OutrunStart.GetCurrentFrame().w*2, OutrunStart.GetCurrentFrame().h*2);

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->fade->FadeToBlack((Module*)App->scene, App->outrun_start, 0.0f);
	}

	return UPDATE_CONTINUE;
}