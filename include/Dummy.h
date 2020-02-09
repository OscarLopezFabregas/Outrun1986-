#ifndef __DUMMY_H__
#define __DUMMY_H__

#include "Module.h"
#include "Globals.h"

class ModuleDummy:public Module
{
  bool Init ()
  {
    LOG ("Dummy Init!");
    return true;
  }

  bool CleanUp ()
  {
    LOG ("Dummy CleanUp!");
    return true;
  }
};

#endif
