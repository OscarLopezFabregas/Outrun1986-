#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include <math.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// start flag
	startflag.x = 0;
	startflag.y = 2;
	startflag.w = 276;
	startflag.h = 78;

	

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	//redship.x = 8;
	//redship.y = 23;
	//redship.w = 522;
	//redship.h = 181;
	
	// Background / sky
	//background.x = 72;
	//background.y = 208;
	//background.w = 768;
	//background.h = 176;

	// flag animation
	//flag.frames.push_back({848, 208, 40, 40});
	//flag.frames.push_back({848, 256, 40, 40});
	//flag.frames.push_back({848, 304, 40, 40});
	//flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	//girl.frames.push_back({ 624,16,31,55 });
	//girl.frames.push_back({ 624,80,31,55 });
	//girl.frames.push_back({ 624,144,31,55});
	//girl.speed = 0.05f;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
//	graphics = App->textures->Load("start.png");

	//// TODO 7: Enable the player module
	App->player->Enable();
	//// TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down
	//yk += 1.1 * cos(d);
	//d = d + 0.15;
	//
	//

	//// Draw everything --------------------------------------
	//// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &startflag, 0.7f); // sea and sky
	//App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.7f); // flag animation

	//// TODO 3: Draw the ship. Be sure to tweak the speed.
	//App->renderer->Blit(graphics, 0, yk, &redship, 1.0f);
	//// TODO 6: Draw the girl. Make sure it follows the ship movement!
	//App->renderer->Blit(graphics, 192, yk+105, &(girl.GetCurrentFrame()), 1.0f);
	//App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder
	

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module

	return UPDATE_CONTINUE;
}