#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFontManager.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include <string>
#include "Line.h"
#include <math.h>
#include <time.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene(bool start_enabled) : Module(start_enabled)
{
	//Background
	Background.x = 0;
	Background.y = 0;
	Background.w = 1891;
	Background.h = 245;


	clock_t initT = clock();
	initTimer = initT;
	minuteLap = 0;
	secondsLap = 0;
	miliSecondsLap = 0;
	

	Sprite* Start_Banner = new Sprite();
	Start_Banner->rect = { 338, 38, 587, 250};
	sprites.push_back(Start_Banner);
	start_banner = sprites.size() - 1;//WHY

	Sprite* Palm_Left = new Sprite();
	Palm_Left->rect = { 40,38, 131, 287 };
	sprites.push_back(Palm_Left);
	palm_left = sprites.size() - 1;//WHY

	Sprite* Palm_Right = new Sprite();
	Palm_Right->rect = { 176,57,131,287 };
	sprites.push_back(Palm_Right);
	palm_right = sprites.size() - 1;

	Sprite* Traffic_Light = new Sprite();
	Traffic_Light->rect = {64,338,136,218};
	sprites.push_back(Traffic_Light);
	traffic_light = sprites.size() - 1;

	Sprite* Column = new Sprite();
	Column->rect = { 226,356,50,200 };
	sprites.push_back(Column);
	column = sprites.size() - 1;

	Sprite* GrandStand = new Sprite();
	GrandStand->rect = { 323,373,400,137 };
	sprites.push_back(GrandStand);
	grandstand = sprites.size() - 1;

	Sprite* CheckPoint = new Sprite();
	CheckPoint->rect = { 45,575,288,227 };
	sprites.push_back(CheckPoint);
	checkpoint = sprites.size() - 1;

	//GUI
	guiTime.x = 78;
	guiTime.y = 14;
	guiTime.w = 142;
	guiTime.h = 48;

	guiScore.x = 557;
	guiScore.y = 24;
	guiScore.w = 171;
	guiScore.h = 48;

	guiLap.x = 387;
	guiLap.y = 23;
	guiLap.w = 126;
	guiLap.h = 49;

	guiKmh.x = 268;
	guiKmh.y = 15;
	guiKmh.w = 83;
	guiKmh.h = 57;

	guiStage.x = 762;
	guiStage.y = 30;
	guiStage.w = 177;
	guiStage.h = 42;

	guiMap.x = 623;
	guiMap.y = 128;
	guiMap.w = 73;
	guiMap.h = 50;


}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");
	Sprites = App->textures->Load("Sprites/BeachTrack.png");
	background = App->textures->Load("Sprites/BeachTrackBackg2.png");
	GUI = App->textures->Load("Sprites/GUI.png");

	App->player->Enable();

	secondsToQuit = 20;
	secondsAux = 0;
	score = 0;
	playerX = 0;
	playerZ = 0;
	speed = 0;
	startPos = 0;

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

void ModuleScene::TimeManager() {
	secondsPassed = (clock() - initTimer) / CLOCKS_PER_SEC;
	if (secondsAux != secondsPassed) {
		secondsAux = secondsPassed;
		secondsToQuit--;
		secondsLap++;
	}
	miliSecondsLap++;
	miliSecondsLap++;
	if (secondsLap == 60) {
		secondsLap = 0;
		minuteLap++;
	}
	if (miliSecondsLap == 60)miliSecondsLap = 0;
}


void ModuleScene::PrintTrack()
{

	//CREA BUCLE PARA QUE LA PISTA SEA INFINITA
   // while (pos >= N * 200) pos -= N*SEGMENT_LENGTH;
	//while (pos < 0) pos += N*SEGMENT_LENGTH;
	//while (playerX >= N * 200) playerX -= N*SEGMENT_LENGTH;
	//while (playerX < 0) playerX += N*SEGMENT_LENGTH;


	float x = 0; 
	float dx = 0;
	int segL = SEGMENT_LENGTH;
	
    startPos = (playerX/segL);
	int camH = (int)(1500 + lines[startPos].y);
	int maxY = SCREEN_HEIGHT;

	////draw background
	App->renderer->Blit(background, 0, 0, &Background, 0.0f);
	
	//draw track 
	for (int n = startPos; n < startPos + 300; n++)
	{
		//linia actual del player
			Line &l = lines[n%N];
	
			l.project(playerZ - x , camH, playerX /*- (n >= N ? N*segL : 0)*/);

			x += dx;
			dx += l.curve;
			

		//CIELO EN NEGRO	
	    l.clip = (float)maxY;
		if (l.Y > maxY)continue;
		maxY = (int)(l.Y);

		//Alternate in colors
		Color grass =(int) (n / 3) % 2 ? grass1 : grass2;
		Color rumble = (int)(n / 3) % 2 ? rumble1 : rumble2;
		Color sideline = (n / 3) % 2 ? sideline1 : sideline2;
		Color road = (n / 3) % 2 ? road1 : road2;
		
		//	Color Line;
			if (n == 0)n++;
			Line p = lines[(n - 1) % N]; //previos line

			App->renderer->BlitPolygon(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
			App->renderer->BlitPolygon(rumble, (short)p.X,(short)p.Y, (short)(p.W*1.2),(short)l.X,(short)l.Y,(short)(l.W*1.2));
			App->renderer->BlitPolygon(sideline, (short)p.X, (short)p.Y, (short)(p.W*1.07), (short)l.X, (short)l.Y, (short)(l.W*1.07));
			App->renderer->BlitPolygon(road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
			App->renderer->BlitPolygon(sideline, (short)p.X, (short)p.Y, (short)(p.W*0.40), (short)l.X, (short)l.Y, (short)(l.W*0.40));
			App->renderer->BlitPolygon(road, (short)p.X, (short)p.Y, (short)p.W*0.33, (short)l.X, (short)l.Y, (short)l.W*0.33);	

		  }
	//draw objects
	for (int n = startPos + 300; n > startPos; n--)
	{
		if (lines[n%N].id != -1)
			lines[n%N].DrawObject(sprites[lines[n%N].id]->rect, Sprites);
	}
	for (int n = startPos; n < startPos+1; n++)
	{
		if (lines[n%N].id == checkpoint)
		{
			secondsToQuit += 10;
		}
	}
}
// Update: draw background
void ModuleScene::PrintGUI()
{
	App->renderer->Blit(GUI, 30, 30, &guiTime, 0.0f, guiTime.w/2, guiTime.h/2);
	App->renderer->Blit(GUI, 180, 30, &guiScore, 0.0f,  guiScore.w / 2, guiScore.h / 2);
	App->renderer->Blit(GUI, 420, 30, &guiLap, 0.0f, guiLap.w / 2, guiLap.h / 2);
	App->renderer->Blit(GUI, 120, SCREEN_HEIGHT - 50, &guiKmh, 0.0f, guiKmh.w/2 , guiKmh.h/2 );
	App->renderer->Blit(GUI, 470, SCREEN_HEIGHT - 50, &guiStage, 0.0f, guiStage.w / 2, guiStage.h / 2);
	App->renderer->Blit(GUI, 600, SCREEN_HEIGHT - 50, &guiMap, 0.0f, guiMap.w / 2, guiMap.h / 2);
	if (secondsToQuit>0) {
		App->fontManager->PrintCharacter(App->fontManager->yellowFont, 110, 35, std::to_string(secondsToQuit));
	
	}
	App->fontManager->PrintCharacter(App->fontManager->blueFont, 290, 35, std::to_string(score));
	if (minuteLap<10)   App->fontManager->PrintCharacter(App->fontManager->greenFont, 500, 35, "0");
	if (secondsLap < 10)
	{
		App->fontManager->PrintCharacter(App->fontManager->greenFont, 560, 35, "0");
		App->fontManager->PrintCharacter(App->fontManager->greenFont, 582, 35, std::to_string(secondsLap));

	}
	else App->fontManager->PrintCharacter(App->fontManager->greenFont, 560, 35, std::to_string(secondsLap));
 	App->fontManager->PrintCharacter(App->fontManager->greenFont, 522, 35, std::to_string(minuteLap));
	App->fontManager->PrintCharacter(App->fontManager->greenFont, 565, SCREEN_HEIGHT-47, "1");
	App->fontManager->PrintSpeed(App->fontManager->speedFont, 60, SCREEN_HEIGHT - 50, std::to_string(speed));
	

}

void ModuleScene::AnimationPlayer()
{
	for (int n = startPos; n < startPos + 2; n++)
	{
		if (lines[n%N].y - lines[(n+1)%N].y == 0)
		{
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				App->player->carState = &App->player->right;
	
			}
			else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				App->player->carState = &App->player->left;
			}
			else
			{
				App->player->carState = &App->player->forward;
			}
			
		}
		if (lines[n%N].y - lines[(n + 1) % N].y < 0)
		{
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				App->player->carState = &App->player->rightUp;
			}
			else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				App->player->carState = &App->player->leftUp;
			}
			else
			{
				App->player->carState = &App->player->forwardUp;
			}
		}

		if (lines[n%N].y - lines[(n + 1) % N].y > 10)
		{
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				App->player->carState = &App->player->right;
			}
			else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				App->player->carState = &App->player->left;
			}
			else
			{
				App->player->carState = &App->player->forwardDown;
			}
		}

	}
	
	App->renderer->Blit(App->player->graphics, (SCREEN_WIDTH - 2 * App->player->carState->GetCurrentFrame().w) / 2, (SCREEN_HEIGHT - 2 * App->player->carState->GetCurrentFrame().h) - 5, &(App->player->carState->GetCurrentFrame()), 1.0f,
		2 * App->player->carState->GetCurrentFrame().w, 2 * App->player->carState->GetCurrentFrame().h);

}


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
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (speed < MAX_SPEED) speed += ACCELERATION;
		
		playerX += speed;
		
		score = score + 1;
	}
	else 
	{
		if (speed > MIN_SPEED) speed -= ACCELERATION;
		playerX += speed;
	}


	int currentCurve = lines[startPos%N].curve;

	if (speed> 10)
	{
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
	}
	TimeManager();
	PrintTrack();
	PrintGUI();
	AnimationPlayer();
	if (secondsToQuit < 1)
	{
		App->fade->FadeToBlack((Module*)App->outrun_start, this, 0.0f);
	}

	return UPDATE_CONTINUE;

}



