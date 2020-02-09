#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSegaIntro.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene.h"
#include "SDL.h"


ModuleSegaIntro::ModuleSegaIntro (bool start_enabled):
Module (start_enabled)
{
  for (int i = 0; i < 7; i++)
    {
      for (int j = 0; j < 3; j++)
	{

	  sega.frames.push_back (
				  {
				  49 + 216 * i, 97 + 73 * j, 207, 64});
	}
    }


  sega.speed = 0.05f;

}

ModuleSegaIntro::~ModuleSegaIntro ()
{

}

bool
ModuleSegaIntro::Start ()
{
  LOG ("Loading Sega Intro");

  graphics = App->textures->Load ("resources/Sprites/SEGA.png");


  return true;
}

bool
ModuleSegaIntro::CleanUp ()
{
  LOG ("Unloading Sega Intro");

  App->textures->Unload (graphics);


  return true;
}

update_status
ModuleSegaIntro::Update ()
{

  App->renderer->Blit (graphics,
		       (SCREEN_WIDTH - 1.5 * sega.GetCurrentFrame ().w) / 2,
		       (SCREEN_HEIGHT -
			1.5 * sega.GetCurrentFrame ().h) / 2.5,
		       &(sega.GetCurrentFrame ()), 1.0f,
		       1.5 * sega.GetCurrentFrame ().w,
		       1.5 * sega.GetCurrentFrame ().h);

  if (App->input->GetKey (SDL_SCANCODE_SPACE))
    {
      App->fade->FadeToBlack ((Module *) App->outrun_start, App->sega_intro,
			      1.0f);
    }

  return UPDATE_CONTINUE;
}
