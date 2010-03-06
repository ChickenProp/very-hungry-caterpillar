#ifndef _INPUT_H_
#define _INPUT_H_

#include "SDL.h"

class Input {
	public:
	
	static void checkEvents ();
	
	/** Return true if key is currently being held. */
	static bool keyDown (SDLKey key) {
		return (keystate_now[key] != 0);
	}
	
	/** Return true if key was pressed down in this frame. */
	static bool keyPressed (SDLKey key) {
		return (keystate_now[key] != 0) && (keystate_old[key] == 0);
	}
	
	/** Return true if key was released in this frame. */
	static bool keyReleased (SDLKey key) {
		return (keystate_now[key] == 0) && (keystate_old[key] != 0);
	}
	
	static void warpMouse (Uint16 x, Uint16 y) { SDL_WarpMouse(x, y); }
	
	static int getMouseX () { return mouseX; }
	static int getMouseY () { return mouseY; }
	
	static bool mouseDown (int button) {
		return (mousestate_now & SDL_BUTTON(button)) != 0;
	}
	
	static bool mousePressed (int button) {
		return ((mousestate_now & ~mousestate_old) & SDL_BUTTON(button)) != 0;
	}
	
	static bool mouseReleased (int button) {
		return ((~mousestate_now & mousestate_old) & SDL_BUTTON(button)) != 0;
	}
	
	static bool hasFocus () {
		return (SDL_GetAppState() & SDL_APPINPUTFOCUS) != 0;
	}
	
	private:
	
	static Uint8* keystate_now;
	static Uint8 keystate_old[SDLK_LAST];
	
	static Uint8 mousestate_now;
	static Uint8 mousestate_old;
	
	static int mouseX;
	static int mouseY;
};

#endif

