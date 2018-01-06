#ifndef _LINE_
#define _LINE_

#include "Globals.h"
#include <vector>

class SDL_Texture;

class Line
{
public:
	float x, y, z; //3d center of line
	float X, Y, W; //screen coord
	float scale;
	float curve;
	float clip;
	float spriteX;
	int id;
	float destY;
	float destX;
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	int roadW = ROAD_WIDTH;
	int segL = SEGMENT_LENGTH;
	float camD = (float)CAMERA_DEPTH;
	
	SDL_Rect rectline; 
	
	Line() 
	{
		x = y = z = X = Y = W = 0;
		scale = 0;
		curve = 0;
		clip = 0;
		spriteX = 0.f;
		id = -1;
	};

	//from world to screen coordinates;
	void project(int camX, int camY, int camZ)
	{
		if (z < camZ) return;
		scale = camD / (z - camZ);

		X = (float)((1 + scale * (x - camX)) *  width / 2); //Casting required?
		Y = (float)((1 - scale * (y - camY)) * height / 2);
		W = (float)(scale * roadW * width / 2);
	}

	void DrawObject(SDL_Rect sprite, SDL_Texture* texture)
	{
		float spriteXToDraw = spriteX;
		int w = sprite.w;
		int h = sprite.h;
	
		
		float destW = w * W / 266;
		float destH = h * W / 266;
	
			destX = X + scale * spriteXToDraw * width / 2;
			destY = Y + 4;
			destX += destW * spriteXToDraw; //offsetX
			destY += destH * (-1);    //offsetY
	
		float clipH = destY + destH - clip;
		if (clipH<0) clipH = 0;


		destX = X + (W * spriteXToDraw);
		if (clipH >= destH) return;

		sprite.h = (int)(h - h*clipH / destH);
		int spriteScaleH = (int)(sprite.h*(destH / h));
		int spriteScaleW = (int)(sprite.w*(destW / w));
		App->renderer->Blit(texture, (int)destX - spriteScaleW / 2,
			(int)destY, &sprite, 0.f, spriteScaleW, spriteScaleH);
	}
};



#endif // !_LINE_