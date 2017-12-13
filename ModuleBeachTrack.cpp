#include "Globals.h"
#include "ModuleAudio.h"
#include "Application.h"
#include"ModuleBeachTrack.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Line.h"

#include "SDL\include\SDL.h"
ModuleBeachTrack::ModuleBeachTrack(bool start_enabled) : ModuleScene(start_enabled)
{
	//Colors of Beach Track
	grass1 = Color(242, 240, 193, 255);
	grass2 = Color(222, 220, 180, 255);
	rumble1 = Color(128, 128, 128, 255);
	rumble2 = Color(225, 225, 225, 255);
	road1 = Color(192, 192, 192, 255);
	road2 = Color(150, 150, 150, 255);
	
	//Defining all the sprites
	StartBanner.x = 51;
	StartBanner.y = 45;
	StartBanner.w = 587;
	StartBanner.h = 75;

	


	pos = 0;
	playerX = 0;
}

bool ModuleBeachTrack::Start()
{
																	  
	//TODOS LOS LOAD DEBERÁN IR A MODULE SCENE, PUES ES ALLI DONDE SE PINTA TODO
	//EN ESTA CLASSE TAN SOLO SE ALMACENA LAS COORDENADAS DE CADA SPRITE DEL MAPA EN CONCRETO Y SE INTRODUCE EN EL VECTOR LINE, QUE EN DEFINITIVA, ES EL MAPA VECTORIZADO

	ModuleScene::Start();

	
	for (int i = 0; i < 40000; i++)
	{
		Line line;
		line.z = (float)i * line.segL;
		if (300 < i &&  i < 600) line.curve = -1;
		
		if (i == 13)
		{
			line.id = start_banner;
			line.spriteX = 0;
		}
		lines.push_back(line);
	}
	N = lines.size();
	return true;
}
ModuleBeachTrack::~ModuleBeachTrack()
{

}
