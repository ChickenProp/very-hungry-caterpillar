#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include "SDL.h"
#include "SDL_opengl.h"

class TextureLoader {
	public:
	
	static GLuint get (std::string);
	
	static GLuint create (SDL_Surface* surface, GLuint texture = 0);
	
	static void clearAll ();
};

#endif

