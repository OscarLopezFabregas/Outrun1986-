#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__


#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "Module.h"

struct SDL_Texture;

class ModulePlayer:public Module
{
public:
  ModulePlayer (bool start_enabled = true);
   ~ModulePlayer ();

  bool Start ();
  update_status Update ();
  bool CleanUp ();

  void const DetectCollision (const SDL_Rect r);
public:

    SDL_Texture * graphics = nullptr;
  SDL_Rect collider;

  Animation *carState = nullptr;

  Animation idle;
  Animation idleUp;
  Animation idleLeft;
  Animation idleRight;
  Animation idleUpLeft;
  Animation idleUpRight;
  Animation forward;
  Animation forwardDown;
  Animation forwardUp;
  Animation left;
  Animation right;
  Animation rightUp;
  Animation leftUp;


  Animation idlepilot;
  Animation idlegirl;
  float playerX = 0;
  float playerZ = 0;
  int crash = 0;
  int speed = 0;

  //Animation backward;
  //Animation forward;
  iPoint position;

};

#endif // __MODULEPLAYER_H__
