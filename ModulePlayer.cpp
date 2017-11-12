#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	

}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

//	graphics = App->textures->Load("Ferrari1.png"); // arcade version


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	//App->renderer->Blit(graphics, position.x, 120, &Ferrari);

	/*if (App->input->GetKey(SDLK_RIGHT)) {
		App->renderer->Blit(graphics, position.x, position.y-90, &(forward.GetCurrentFrame()), 1.0f);
		position.x = position.x + 2;
	}
	
	else if (App->input->GetKey(SDLK_LEFT)) {
		App->renderer->Blit(graphics, position.x, position.y - 90, &(backward.GetCurrentFrame()), 1.0f);
		position.x = position.x - 1.5;
	}
	else {
		App->renderer->Blit(graphics, position.x, position.y - 90, &(idle.GetCurrentFrame()), 1.0f);
	}*/
	return UPDATE_CONTINUE;
}