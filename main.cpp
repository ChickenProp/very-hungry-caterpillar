#include "includes.h"

void mainloop();
bool doFrame(int);

int main (int argc, char **argv) {
	int width = 800; int height = 600;

	int flags = SDL_OPENGL | SDL_DOUBLEBUF | SDL_HWSURFACE;
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                fprintf(stderr, "Unable to initialise SDL: %s\n",
                        SDL_GetError());
        }
        atexit(SDL_Quit);

	SDL_Surface *screen;
        screen = SDL_SetVideoMode(width, height, 32, flags);
        if (screen == NULL) {
                fprintf(stderr, "Unable to set video mode: %s\n",
                        SDL_GetError());
        }
        SDL_WM_SetCaption("The Very Hungry Caterpillar", 0);


	glMatrixMode(GL_PROJECTION);
        glOrtho(0, width, 0, height, -1, 128);
        glMatrixMode(GL_MODELVIEW);
        
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mainloop();
	return 0;
}

void mainloop() {
	int t2 = SDL_GetTicks();
	int t = t2 - 20;
	while (doFrame(t2 - t)) {
		t = t2;
		t2 = SDL_GetTicks();
	}
}

bool doFrame(int t) {
	D("frame took %d ms", t);
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			return 0;
		}
	}
	return 1;
}
