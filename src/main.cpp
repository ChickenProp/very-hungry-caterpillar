#include "window.h"
#include "input.h"
#include "texture_loader.h"
#include "SDL_opengl.h"

void init () {
	//Window::setFullscreen(true);
	
	Window::setInitCallback(TextureLoader::clearAll);
	
	// Try to create a window.
	if (! Window::init(800, 600, "Game Name") ) {
		exit(1);
	}
	
}

void update () {
	
}

void draw () {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT); // You may also want GL_DEPTH_BUFFER_BIT
	
	// Projection matrix
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	int height = (int) (800.0f / Window::getAspectRatio());
	int width = 800;
	glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);
	
	// Or for a perspective matrix:
	//gluPerspective(45.0f, Window::getAspectRatio(), 1, 400);
	
	// GL settings
	
	glDisable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Camera
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// [Set up camera here]
	
	// Draw
	
	
	
	SDL_GL_SwapBuffers();
}

int main (int argc, char** argv) {
	init();
	
	const int step = 20; // ms
	const int MAX_UPDATES = 1;

	int previousTime = SDL_GetTicks();
	int unused = step;

	// Update/render loop.
	while (true) {
		int i = 0;
		
		while (unused >= step && i < MAX_UPDATES) {
			i++;
			
			// Check for input.
			Input::checkEvents();

			// Update the scene.
			update();
			
			unused -= step;
		}

		// Draw the scene.
		draw();
		
		int now = SDL_GetTicks();
		
		int delay = step - unused - (now - previousTime);
		
		if (delay > 0) {
			SDL_Delay(delay);
		}
		
		now = SDL_GetTicks();
		
		unused += now - previousTime;
		
		previousTime = now;
	}

	return 0;
}

