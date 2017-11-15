#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

struct Line
{
public:
	Line() { x = y = z = 0; };
	~Line();
	float x, y, z; //3d center of line
	float X, Y, W; //screen coord
	float scale;
	//from world to screen coordinates;
	void project(int camX, int camY, int camZ);
};




class ModuleScene : public Module
{
public:
	ModuleScene( bool start_enabled = false);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	

public:
	
	SDL_Texture* graphics = nullptr;
	int lanes = 3;
	int roadW = 2000;
	int segL = 200; //segment length
    float camD = 0.84; //camera depth
	

	
	std::vector<Line> lines;
	
};

#endif // __MODULESCENEKEN_H__