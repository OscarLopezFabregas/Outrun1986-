#ifndef __MODULEFONTMANAGER_H__
#define __MODULEFONTMANAGER_H__

#include "Module.h"

struct SDL_Texture;

class ModuleFontManager:public Module
{
public:

  ModuleFontManager (bool start_enabled = true);
   ~ModuleFontManager ();

  bool Start ();
  bool CleanUp ();

  SDL_Rect FindCharacter (char characterToFind, SDL_Texture * font);
  SDL_Rect FindNumber (char characterToFind);
  void PrintCharacter (SDL_Texture * font, int positionX, int positionY,
		       std::string textToPrint);
  void PrintSpeed (SDL_Texture * font, int positionX, int positionY,
		   std::string textToPrint);

  SDL_Texture *yellowFont;
  SDL_Texture *greenFont;
  SDL_Texture *blueFont;
  SDL_Texture *speedFont;



};






#endif // __MODULEFONTMANAGER_H__
