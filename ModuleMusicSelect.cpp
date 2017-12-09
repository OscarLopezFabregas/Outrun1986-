#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleMusicSelect.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModuleMusicSelect::ModuleMusicSelect(bool start_enabled) :Module(start_enabled)
{
	//Background Select Music
	Background.x = 202;
	Background.y = 348;
	Background.h = 283;
	Background.w = 405;

	//Hand cases
	Handidle.x = 430;
	Handidle.y = 176;
	Handidle.w = 128;
	Handidle.h = 56;

	Handleft.x = 426;
	Handleft.y = 114;
	Handleft.w = 130;
	Handleft.h = 58;

	Handright.x = 439;
	Handright.y = 233;
	Handright.w = 115;
	Handright.h = 58;

	//Press Start
	PressStart.frames.push_back({ 315,320,156,8 });
	PressStart.frames.push_back({ 1,1,156,8 });		
	PressStart.speed = 0.008f;

	//Music Tittles
	Magicalsound.x = 250;
	Magicalsound.y = 206;
	Magicalsound.w = 175;
	Magicalsound.h = 16;

	Passingbreeze.x = 274;
	Passingbreeze.y = 223;
	Passingbreeze.w = 144;
	Passingbreeze.h = 16;

	Splashwave.x = 282;
	Splashwave.y = 240;
	Splashwave.w = 124;
	Splashwave.h = 16;

	//Volume Animation
	VolumeRadio.frames.push_back({ 377,112,47,8 });
	VolumeRadio.frames.push_back({ 377,122,47,8 });
	VolumeRadio.frames.push_back({ 377,132,47,8 });
	VolumeRadio.frames.push_back({ 377,142,47,8 });
	VolumeRadio.frames.push_back({ 377,152,47,8 });
	VolumeRadio.frames.push_back({ 377,162,47,8 });
	VolumeRadio.frames.push_back({ 377,172,47,8 });
	VolumeRadio.frames.push_back({ 377,182,47,8 });//Last
	VolumeRadio.frames.push_back({ 377,172,47,8 });
	VolumeRadio.frames.push_back({ 377,162,47,8 });
	VolumeRadio.frames.push_back({ 377,152,47,8 });
	VolumeRadio.frames.push_back({ 377,142,47,8 });
	VolumeRadio.frames.push_back({ 377,132,47,8 });
	VolumeRadio.frames.push_back({ 377,122,47,8 });
	VolumeRadio.speed = 0.25f;

	//Radiodial
	Radiodialleft.x = 257;
	Radiodialleft.y = 120;
	Radiodialleft.w = 55;
	Radiodialleft.h = 8;

	Radiodialidle.x = 257;
	Radiodialidle.y = 151;
	Radiodialidle.w = 55;
	Radiodialidle.h = 8;
	
	Radiodialright.x = 257;
	Radiodialright.y = 182;
	Radiodialright.w = 55;
	Radiodialright.h = 8;

}

bool ModuleMusicSelect::Start()
{
	bool ret = true;
	graphics2 = App->textures->Load("Sprites/MusicSelect.png");

	return ret;
}

bool ModuleMusicSelect::CleanUp()
{
	bool ret = true;
	App->textures->Unload(graphics);


	return ret;
}

update_status ModuleMusicSelect::Update() //FALTA PREVISUALITZACIÓ DE LES CANÇONS
{
	bool play = false;
	
	App->renderer->Blit(graphics2, 0, 0, &Background, 1.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	App->renderer->Blit(graphics2, (SCREEN_WIDTH-94) / 2, SCREEN_HEIGHT - 80, &(VolumeRadio.GetCurrentFrame()), 0.0f,
		2*VolumeRadio.GetCurrentFrame().w, 2*VolumeRadio.GetCurrentFrame().h);
	App->renderer->Blit(graphics2, (SCREEN_WIDTH - 2 * PressStart.GetCurrentFrame().w) / 2, SCREEN_HEIGHT - 150,
		&(PressStart.GetCurrentFrame()), 0.0f, 2 * PressStart.GetCurrentFrame().w, 2 * PressStart.GetCurrentFrame().h);
	

	if (App->input->GetKey(SDL_SCANCODE_RIGHT)) 
	{
		Keyboardid = SDL_SCANCODE_RIGHT;
		App->renderer->Blit(graphics2, SCREEN_WIDTH / 2.37, SCREEN_HEIGHT / 1.29, &Radiodialright, 1.0f, 2 * Radiodialright.w, 2 * Radiodialright.h);
		App->renderer->Blit(graphics2, SCREEN_WIDTH/2.7 + Handright.w/7, SCREEN_HEIGHT-2*Handright.h, &Handright, 1.0f, 2* Handright.w, 2 * Handright.h);
		App->renderer->Blit(graphics2, (SCREEN_WIDTH - 2 * Splashwave.w) / 2, SCREEN_HEIGHT / 2.65, &Splashwave, 1.0f, 2 * Splashwave.w, 2 * Splashwave.h);
	
		if (App->input->GetKey(SDL_SCANCODE_SPACE))
		{
			music = RIGHT;
			play = true;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{   
		Keyboardid = SDL_SCANCODE_LEFT;
		App->renderer->Blit(graphics2, SCREEN_WIDTH / 2.37, SCREEN_HEIGHT / 1.29, &Radiodialright, 1.0f, 2 * Radiodialright.w, 2 * Radiodialright.h);
		App->renderer->Blit(graphics2, SCREEN_WIDTH/2.7 - Handleft.w/11 , SCREEN_HEIGHT - 2*Handleft.h, &Handleft, 1.0f, 2 * Handleft.w, 2 * Handleft.h);
		App->renderer->Blit(graphics2, (SCREEN_WIDTH - 2 * Magicalsound.w) / 2, SCREEN_HEIGHT / 2.65, &Magicalsound, 1.0f, 2 * Magicalsound.w, 2 * Magicalsound.h);
		
		if (App->input->GetKey(SDL_SCANCODE_SPACE))
		{	
			music = LEFT;	
			play = true;
		}
	}
	else {
		
		App->renderer->Blit(graphics2, SCREEN_WIDTH/ 2.37, SCREEN_HEIGHT/1.29 , &Radiodialidle, 1.0f, 2*Radiodialidle.w, 2*Radiodialidle.h);
		App->renderer->Blit(graphics2, SCREEN_WIDTH / 2.7, SCREEN_HEIGHT - 2 * Handidle.h, &Handidle, 1.0f, 2 * Handidle.w, 2 * Handidle.h);
		App->renderer->Blit(graphics2, (SCREEN_WIDTH - 2 * Passingbreeze.w) / 2, SCREEN_HEIGHT / 2.65, &Passingbreeze, 1.0f, 2 * Passingbreeze.w, 2 * Passingbreeze.h);
		if (App->input->GetKey(SDL_SCANCODE_SPACE) && App->fade->isFading() == false)
		{
			music = IDLE;
			play = true;
		}
	}

	switch (music)
	{
	case LEFT:
		App->audio->PlayMusic("Music/Magical_Sound_Shower.ogg", 0.f);
		break;
	case RIGHT:
		App->audio->PlayMusic("Music/Splash_Wave.ogg", 0.0f);
		break;
	case IDLE:
		App->audio->PlayMusic("Music/Passing_Breeze.ogg", 0.f);
		break;
	}
	if (play) {
		App->fade->FadeToBlack((Module*)App->beach_track,App->music_select,0.5f);
	}

	

	return UPDATE_CONTINUE;
}