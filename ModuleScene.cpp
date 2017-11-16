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
#include <math.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene(bool start_enabled) : Module(start_enabled)
{
	
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


Line::~Line()
{

}
void Line::project(int camX, int camY, int camZ)
{
	ModuleScene scene;
	scale = scene.camD / (z - camZ);
	X = (1 + scale * (x - camX)) *  SCREEN_WIDTH / 2;
	Y = (1 - scale * (y - camY)) * SCREEN_HEIGHT / 2;
	W = scale * scene.roadW * SCREEN_WIDTH / 2;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
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
bool ModuleScene::CleanUp()
{
	LOG("Unloading ken scene");

//	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	//PUJAR AL CONSTRUCTOR//
	for (int i = 0; i < 1600; i++)
	{
		//canviar a punters
		Line line;
		
		line.z = i*segL;

		lines.push_back(line);
	
	}
	int N = lines.size();
	pos = App->player->playerX / segL;
	
	for (int n = 1+pos; n <pos+300; n++)
	{
		Line &l = lines[n%N];
		l.project(0, 1500, App->player->playerX);
//		
		(n / 3) % 2 ? (grass[0] = 16, grass[1] = 200, grass[2] = 16) : (grass[0] = 0, grass[1] = 154, grass[2] = 0);
		(n / 3) % 2 ? (rumble[0] = 255, rumble[1] = 255, rumble[2] = 255) : (rumble[0] = 0, rumble[1] = 0, rumble[2] = 0);
		(n / 3) % 2 ? (road[0] = 107, road[1] = 107, road[2] = 107) : (road[0] = 105, road[1] = 105, road[2] = 105);

		Line p = lines[(n - 1) % N];
////
		App->renderer->BlitPolygon(0, p.Y, SCREEN_WIDTH, 0, l.Y, SCREEN_WIDTH, grass[0], grass[1], grass[2]);
	    App->renderer->BlitPolygon(p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2,rumble[0], rumble[1], rumble[2]);
		App->renderer->BlitPolygon(p.X, p.Y, p.W, l.X, l.Y, l.W, road[0], road[1], road[2]);

	}





	return UPDATE_CONTINUE;
}

