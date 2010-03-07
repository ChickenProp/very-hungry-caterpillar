#include "window.h"
#include "input.h"
#include "texture_loader.h"
#include "SDL_opengl.h"

#include "world.h"
#include "intro.h"
#include "epilogue.h"

bool initWorld = 0;
bool initEpi = 0;

void init () {
	//Window::setFullscreen(true);
	
	Window::setInitCallback(TextureLoader::clearAll);
	
	// Try to create a window.
	if (! Window::init(640, 480, "The Very Hungry Caterpillar") ) {
		exit(1);
	}

	Intro::init();
	
}

void update () {
	if (!Intro::done())
		Intro::update();
	else {
		if (!initWorld) {
			new World;
			initWorld = 1;
		}
		if (!World::done())
			World::update();
		else
			Epilogue::update();
			
	}
//	else
//		Epilogue::update();
}

void draw () {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT); // You may also want GL_DEPTH_BUFFER_BIT
	
	// Projection matrix
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0, 20, 0, 16, -1, 1);
	
	// Or for a perspective matrix:
	//gluPerspective(45.0f, Window::getAspectRatio(), 1, 400);
	
	// GL settings
	
	glDisable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Camera
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	// [Set up camera here]
	//glOrtho(0, 20, 0, 16, -1, 1);

	// Draw
	
	if (!Intro::done())
		Intro::draw();
	else if (initWorld && !World::done())
		World::draw();
	else if (World::done())
		Epilogue::draw();
	
	SDL_GL_SwapBuffers();
}

int main (int argc, char** argv) {
	Audio::init();
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

