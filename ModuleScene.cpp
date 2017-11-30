#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "Line.h"
#include <math.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene(bool start_enabled) : Module(start_enabled)
{
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");
	graphics2 = App->textures->Load("Sprites/BeachTrack.png");
	App->player->Enable();
	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading ken scene");

//	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

void ModuleScene::PrintTrack()
{

	//CREA BUCLE PARA QUE LA PISTA SEA INFINITA
    //while (pos >= N * 200) pos -= N*SEGMENT_LENGTH;
	//while (pos < 0) pos += N*SEGMENT_LENGTH;
	//while (App->player->playerX >= N * 200) App->player->playerX -= N*SEGMENT_LENGTH;
	//while (App->player->playerX < 0) App->player->playerX += N*SEGMENT_LENGTH;


	float x = 0; 
	float dx = 0;
	//int segL = SEGMENT_LENGTH;

	startPos = (int)(App->player->playerX /SEGMENT_LENGTH );
	//int camH = (int)(1500 + lines[startPos].y);
	int maxY = SCREEN_HEIGHT;

	////draw background

	for (int n = startPos; n < startPos + 300; n++)
	{
			Line &l = lines[n%N];
		//	l.project((int)(playerX - x), camH, pos - (n >= N ? N*segL : 0));
			l.project(playerZ - x, 1500, App->player->playerX);

			x += dx;
			dx += l.curve;
			
			
			
		//	l.clip = (float)maxY;

		//CIELO EN NEGRO	
		if (l.Y > maxY)continue;
		maxY = (int)(l.Y);

		//Alternate in colors
		Color grass = (n / 3) % 2 ? grass1 : grass2;
		Color rumble = (n / 3) % 2 ? rumble1 : rumble2;
		Color road = (n / 3) % 2 ? road1 : road2;

		//	Color Line;
			if (n == 0)n++;
			Line p = lines[(n - 1) % N]; //previos line

			App->renderer->BlitPolygon(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
			App->renderer->BlitPolygon(rumble, (short)p.X,(short)p.Y, (short)(p.W*1.2),(short)l.X,(short)l.Y,(short)(l.W*1.2));
			App->renderer->BlitPolygon(road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
		   // App->renderer->BlitPolygon(line,(short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
			
		  

			//DRAW OBJECTS **EN CONSTRUCCION**
			//App->renderer->Blit(graphics2, l.X, l.Y, &l.rectline, 1.0f, -1, -1);
			
	}
	
	//pos = App->player->playerX / segL;

	//for (int n = 1 + pos; n <pos + 300; n++)
	//{

	//	Color grass = (n / 3) % 2 ? grass1 : grass2;
	//	Color rumble = (n / 3) % 2 ? rumble1 : rumble2;
	//	Color road = (n / 3) % 2 ? road1 : road2;

	//	Line &l = lines[n%N];
	//	l.project(App->player->playerZ, 1500, App->player->playerX);
	//	//		
	//	Line p = lines[(n - 1) % N];
	//	////
	//		App->renderer->BlitPolygon(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
	//		App->renderer->BlitPolygon(rumble, (short)p.X,(short)p.Y, (short)(p.W*1.2),(short)l.X,(short)l.Y,(short)(l.W*1.2));
	//		App->renderer->BlitPolygon(road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);

	//}



	

}
// Update: draw background
update_status ModuleScene::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		playerZ += 70;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		playerZ -= 70;
	}

	int startPos = App->player->playerX / SEGMENT_LENGTH;
	float currentCurve = lines[startPos%N].curve;
	if (currentCurve > 3.5) playerZ -= 60;
	else if (currentCurve > 2) playerZ -= 45;
	else if (currentCurve > 1) playerZ -= 25;
	else if (currentCurve > 0) playerZ -= 15;
	else if (currentCurve < 0) {
		if (currentCurve > -1) playerZ += 15;
		else if (currentCurve > 2) playerZ += 25;
		else if (currentCurve > 3.5) playerZ += 45;
		else playerZ += 60;
	}

	PrintTrack();

	return UPDATE_CONTINUE;

}



