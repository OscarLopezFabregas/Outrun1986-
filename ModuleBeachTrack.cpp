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
	rumble1 = Color(170, 170, 170, 255);
	rumble2 = Color(255, 255, 255, 255);
	sideline1 = Color(255, 255, 255, 255);
	sideline2 = Color(192,192,192,255);
	road1 = Color(170, 170, 170, 255);
	road2 = Color(192, 192, 192, 255);
	trafficline1 = Color(255, 255, 255, 255);
	trafficline2 = Color(0, 0, 0, 0);

	


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
				
		if (0<i && i<550)
		{
			if (i % 10 == 0) {
				line.id = palm_left;
				line.spriteX = -1.2;
			}
			if (i % 9 == 0) {
				line.id = palm_right;
				line.spriteX = 1.2;
			}
		
		}
		if (i == 9)
		{
			line.id = palm_right;
			line.spriteX = 1;
		}
		if (i == 11)
		{
			line.id = traffic_light;
			line.spriteX = -0.9;
		}
		if (i == 12)
		{
			line.id = start_banner;
			line.spriteX = 0;
		}
		if (i == 13)
		{
			line.id = column;
			line.spriteX = 0.9;
		}


		if (i > 50 && i < 250)
		{
			if (i % 7 == 0)
			{
				line.id = grandstand;
				line.spriteX = -2;
			}
		}
		if (300 < i && i < 500)
		{
			
			float transitionValue = (float)(sin( PI*i/300) * 2750);
			if (-0.1 < transitionValue < 0.1)
			{
			 go = true;
			}
			if (go) line.y = -transitionValue;
			if (i == 499) lastValue = line.y;
		}
		
		if (i > 499) line.y = lastValue;
		
		if (500 < i &&  i < 650) line.curve = -2.5;
		if (650 < i &&  i < 900) line.curve = 2.5;

		if (900 < i && i < 1500)
		{
			float transitionValue = (float)(sin(PI*i / 300) * 2750);
			if (-0.1 < transitionValue < 0.1) go = true;
			if (go)	line.y = transitionValue;
			if (i == 1499) lastValue = line.y;
		}
		if (i > 1499) line.y = lastValue;

		lines.push_back(line);
	}
	N = lines.size();
	return true;
}
ModuleBeachTrack::~ModuleBeachTrack()
{

}
