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
	position.x = ((SCREEN_WIDTH*SCREEN_SIZE)-35)/2;
	position.y = (SCREEN_HEIGHT*SCREEN_SIZE) - 40;

	idleferrari.frames.push_back({ 207,198,77,40 });

	
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("player.png"); // arcade version


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

	App->renderer->Blit(graphics, position.x, position.y, &(idleferrari.GetCurrentFrame()), 1.0f);
	
	if (App->input->GetKey(SDLK_UP)) {
		playerX += 200;
	}
	
	/*else if (App->input->GetKey(SDLK_LEFT)) {
		App->renderer->Blit(graphics, position.x, position.y - 90, &(backward.GetCurrentFrame()), 1.0f);
		position.x = position.x - 1.5;
	}
	else {
		App->renderer->Blit(graphics, position.x, position.y - 90, &(idle.GetCurrentFrame()), 1.0f);
	}*/
	return UPDATE_CONTINUE;
}