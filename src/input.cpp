#include "input.h"
#include "window.h"
//#include "screen.h"

#include <string.h> // For memcpy

// static members
Uint8* Input::keystate_now = 0;

Uint8 Input::keystate_old[SDLK_LAST];

Uint8 Input::mousestate_now = 0;
Uint8 Input::mousestate_old = 0;

int Input::mouseX = 0;
int Input::mouseY = 0;

void Input::checkEvents () {
	memcpy(keystate_old, SDL_GetKeyState(NULL), SDLK_LAST);
	
	mousestate_old = mousestate_now;
	
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_VIDEORESIZE:
				Window::resize(event.resize.w, event.resize.h);
			break;
			case SDL_QUIT:
				exit(0);
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						exit(0);
					break;
					case SDLK_f:
						Window::toggleFullscreen();
					break;
					default: break;
				}
			// NO BREAK! Should fall through to default.
			default:
				//ScreenManager::handleInput(event);
				
				
			break;
		}
	}
	
	keystate_now = SDL_GetKeyState(NULL);
	mousestate_now = SDL_GetMouseState(&mouseX, &mouseY);
}

