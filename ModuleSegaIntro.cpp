#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSegaIntro.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModuleSegaIntro::ModuleSegaIntro(bool start_enabled) : Module(start_enabled)
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 3; j++) {

			sega.frames.push_back({ 49 + 216 * i, 97 + 73 * j, 207,64 });
		}
	}
			

	sega.speed = 0.15f;
}

ModuleSegaIntro::~ModuleSegaIntro()
{

}

bool ModuleSegaIntro::Start()
{
	LOG("Loading Sega Intro");

	graphics = App->textures->Load("SEGA.png");

	//// TODO 7: Enable the player module
	
	//// TODO 0: trigger background music
	//App->audio->PlayMusic("ken.ogg");

	return true;
}

bool ModuleSegaIntro::CleanUp()
{
	LOG("Unloading Sega Intro");

	App->textures->Unload(graphics);
	//App->sega_intro->Disable(); //AIXO PRODUEIX UN ERROR!! PERQUÈ!

	return true;
}

update_status ModuleSegaIntro::Update()
{
	App->renderer->Blit(graphics, (384-207)/2 , (224-74)/2 , &(sega.GetCurrentFrame()), 1.0f);

	return UPDATE_CONTINUE;
}