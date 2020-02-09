
#ifndef __MODULESEGAINTRO__
#define __MODULESEGAINTRO__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


class ModuleSegaIntro:public Module
{
public:
  ModuleSegaIntro (bool start_enabled = false);
   ~ModuleSegaIntro ();

  bool Start ();
  update_status Update ();
  bool CleanUp ();

public:

    SDL_Texture * graphics = nullptr;
  Animation sega;



};

#endif // __MODULESEGAINTRO__
