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

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	int roadW = ROAD_WIDTH;
	int segL = SEGMENT_LENGTH;
	float camD = (float)CAMERA_DEPTH;
	
	Line() 
	{
		x = y = z = X = Y = W = 0;
		scale = 0;
		curve = 0;
		clip = 0;
	};



	//from world to screen coordinates;
	void project(int camX, int camY, int camZ)
	{
		scale = camD / (z - camZ);
		X = (float)((1 + scale * (x - camX)) *  width / 2); //Casting required?
		Y = (float)((1 - scale * (y - camY)) * height / 2);
		W = (float)(scale * roadW * width / 2);
	}

	void DrawObject(SDL_Rect sprite, SDL_Texture* texture, float position = 999, bool middle = false);

};



#endif // !_LINE_