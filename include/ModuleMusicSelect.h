#ifndef __MODULEMUSIC__
#define __MODULEMUSIC__


#include "Animation.h"
#include "Globals.h"
#include "Module.h"

struct SDL_Texture;

class ModuleMusicSelect:public Module
{
public:
  ModuleMusicSelect (bool start_enabled = false);
   ~ModuleMusicSelect ();

  bool Start ();
  update_status Update ();
  bool CleanUp ();

public:
  int Keyboardid = 0;

  SDL_Texture *graphics = nullptr;
  SDL_Texture *graphics2 = nullptr;

  Animation OutrunStart;
  Animation PressStart;
  Animation VolumeRadio;
  music_selected music;
  SDL_Rect Background;
  SDL_Rect Handidle;
  SDL_Rect Handright;
  SDL_Rect Handleft;
  SDL_Rect Radiodialleft;
  SDL_Rect Radiodialidle;
  SDL_Rect Radiodialright;
  SDL_Rect Magicalsound;
  SDL_Rect Passingbreeze;
  SDL_Rect Splashwave;




};

#endif // __MODULEMUISC__
