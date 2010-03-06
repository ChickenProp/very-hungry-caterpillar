#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "SDL.h"
#include <string>

// TODO: icon
// TODO: letterboxing

class Window {

	public:
	static bool init (const int width, const int height, std::string title);
	
	static void resize (const int width, const int height);
	
	static SDL_Surface* getSurface () { return screen; };
	
	static int getWidth () { return width; }
	static int getHeight () { return height; }
	
	static float getAspectRatio () { return float(width) / float(height); }
	
	static bool isResizable () { return resizable; }
	static void setResizable (bool resizable);
	
	static bool isFullscreen () { return fullscreen; }
	static void setFullscreen (bool b);
	static void toggleFullscreen () { setFullscreen(! fullscreen); }
	
	static void setTitle (std::string title);
	
	static int getScreenWidth () { return fullscreen_width; }
	static int getScreenHeight () { return fullscreen_height; }
	
	typedef void (*callback_type)();
	
	static void setInitCallback (callback_type callback);
	
	private:
	
	static bool reset ();
	
	static bool ready;
	
	static int width;
	static int height;
	
	static int fullscreen_width;
	static int fullscreen_height;
	
	static int old_width;
	static int old_height;
	
	static bool resizable;
	static bool fullscreen;

	static std::string title;
	
	static callback_type callback;
	
	static SDL_Surface* screen;
};

#endif

