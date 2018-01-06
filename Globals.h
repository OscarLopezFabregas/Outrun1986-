#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum music_selected
{
	LEFT,
	IDLE,
	RIGHT,
};

struct Color {
	int r;
	int g;
	int b;
	int a;
	Color() { r = 0; g = 0; b = 0; a = 0; }
	Color(int red, int green, int blue, int alpha) {
		r = red, g = green, b = blue, a = alpha;
	}
};



// Deletes a buffer
#define RELEASE( x ) \
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
	 }

// Configuration -----------
#define SCREEN_WIDTH 648
#define SCREEN_HEIGHT 480
#define SCREEN_SIZE 1
#define FULLSCREEN false
#define	PI 3.14159265359
#define FONT "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.:Ç"
#define FONT2 "0123456789eABCDEFGHIJKLMNOPQRSTUVWXYZ.!Ç"
#define NUMBERMASK "0123456789"
#define SEGMENT_LENGTH 200
#define CAMERA_DEPTH 0.84
#define ROAD_WIDTH 2000;
#define FPS 60
#define ACCELERATION 6
#define MAX_SPEED 298
#define MIN_SPEED 0
#define VSYNC true
#define TITLE "Outrun 1986"

#endif //__GLOBALS_H__