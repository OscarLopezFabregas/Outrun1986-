#ifndef _LINE_H__
#define _LINE_H__

#include "Globals.h"
#include "Application.h"

#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleBeachTrack.h"
#include "ModuleRender.h"
#include <vector>



class SDL_Texture;

class Line
{
public:
  float x, y, z;		//3d center of line
  float X, Y, W;		//screen coord
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
  float camD = (float) CAMERA_DEPTH;

  SDL_Rect rectline;
  SDL_Rect hitbox;

    Line ()
  {
    x = y = z = X = Y = W = 0;
    scale = 0;
    curve = 0;
    clip = 0;
    spriteX = 0.f;
    id = -1;
  };

  //from world to screen coordinates;
  void const project (int const camX, int const camY, int const camZ)
  {
    if (z < camZ)
      return;
    scale = camD / (z - camZ);

    X = (float) ((1 + scale * (x - camX)) * width / 2);	//Casting required?
    Y = (float) ((1 - scale * (y - camY)) * height / 2);
    W = (float) (scale * roadW * width / 2);
  }

  void DrawObject (SDL_Rect sprite, SDL_Texture * texture)
  {
    float spriteXToDraw = spriteX;
    int w = sprite.w;
    int h = sprite.h;


    float destW = w * W / 266;
    float destH = h * W / 266;

    destX = X + scale * spriteXToDraw * width / 2;
    destY = Y + 4;
    destX += destW * spriteXToDraw;	//offsetX
    destY += destH * (-1);	//offsetY

    float clipH = destY + destH - clip;
    if (clipH < 0)
      clipH = 0;


    destX = X + (W * spriteXToDraw);
    if (clipH >= destH)
      return;


    sprite.h = (int) (h - h * clipH / destH);
    int spriteScaleH = (int) (sprite.h * (destH / h));
    int spriteScaleW = (int) (sprite.w * (destW / w));
    App->renderer->Blit (texture, (int) destX - spriteScaleW / 2,
			 (int) destY, &sprite, 0.f, spriteScaleW,
			 spriteScaleH);



    if (id == App->beach_track->palm_left
	|| id == App->beach_track->grandstand
	|| id == App->beach_track->bushleft)
      {
	hitbox.x = (int) destX - spriteScaleW;
	hitbox.y = (int) destY;
	hitbox.w = spriteScaleW;
	hitbox.h = spriteScaleH;
	App->player->DetectCollision (hitbox);
      }

    if (id == App->beach_track->palm_right
	|| id == App->beach_track->bushright)
      {
	hitbox.x = (int) destX + 50;
	hitbox.y = (int) destY;
	hitbox.w = spriteScaleW;
	hitbox.h = spriteScaleH;
	App->player->DetectCollision (hitbox);
      }

    if (id == App->beach_track->boathouse)
      {
	hitbox.x = (int) destX - spriteScaleW / 2;
	hitbox.y = (int) destY;
	hitbox.w = spriteScaleW;
	hitbox.h = spriteScaleH;
	App->player->DetectCollision (hitbox);
      }
  }
};



#endif // !_LINE_
