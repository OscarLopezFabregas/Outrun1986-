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
	//Background
	Background.x = 0;
	Background.y = 0;
	Background.w = 1891;
	Background.h = 245;
	

	Sprite* Start_Banner = new Sprite();
	Start_Banner->maxX = 0;
	Start_Banner->minX = 0;
	Start_Banner->rect = { 51, 45, 587, 200};
	sprites.push_back(Start_Banner);
	start_banner = sprites.size() - 1;

	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");
	Sprites = App->textures->Load("Sprites/BeachTrack.png");
	background = App->textures->Load("Sprites/BeachTrackBackg2.png");

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
	int segL = SEGMENT_LENGTH;

	startPos = (int)(App->player->playerX /SEGMENT_LENGTH );
	int camH = (int)(1500 + lines[startPos].y);
	int maxY = SCREEN_HEIGHT;

	////draw background
	App->renderer->Blit(background, 0, 0, &Background, 0.0f);
	//draw track 
	for (int n = startPos; n < startPos + 300; n++)
	{
			Line &l = lines[n%N];
		//	l.project((int)(playerX - x), camH, pos - (n >= N ? N*segL : 0));
			l.project(playerZ - x, camH, App->player->playerX - (n>=N?N*segL:0));

			x += dx;
			dx += l.curve;
			

		//CIELO EN NEGRO	
	    l.clip = (float)maxY;
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
	//draw objects
	for (int n = startPos + 300; n > startPos; n--)
	{
		if (lines[n%N].id != -1)
			lines[n%N].DrawObject(sprites[lines[n%N].id]->rect, Sprites, 0);
	}
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



