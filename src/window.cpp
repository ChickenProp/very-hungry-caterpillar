#include "SDL.h"
#include "SDL_opengl.h"

#include "window.h"

SDL_Surface* Window::screen = 0;

int Window::width = 800;
int Window::height = 600;

int Window::fullscreen_width;
int Window::fullscreen_height;

int Window::old_width;
int Window::old_height;

bool Window::ready = false;
bool Window::resizable = false;
bool Window::fullscreen = false;

std::string Window::title;

Window::callback_type Window::callback = 0;

// functions

bool Window::init(const int width, const int height, std::string title) {
	
	Window::width = width;
	Window::height = height;
	
	old_width = width;
	old_height = height;

	// Check if we can initialise SDL video.
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Unable to initalise SDL: %s\n", SDL_GetError());
		return false;
	}    
	atexit(SDL_Quit);
	
	ready = true;

	setTitle(title);
	
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	
	fullscreen_width = videoInfo->current_w;
	fullscreen_height = videoInfo->current_h;
	
	if (fullscreen_width <= 0 || fullscreen_height <= 0) {
		// This shouldn't happen, but apparently it did once
		fullscreen_width = width;
		fullscreen_height = height;
	}
	
	if (fullscreen) {
		Window::width = fullscreen_width;
		Window::height = fullscreen_height;
	}
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  

	return reset();

}

bool Window::reset () {
	Uint32 flags = SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL | SDL_ANYFORMAT;
	
	if (resizable) { flags |= SDL_RESIZABLE; }
	if (fullscreen) { flags |= SDL_FULLSCREEN; }
	
	screen = SDL_SetVideoMode(width, height, 32, flags);
	
	if (screen == NULL) {
		fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
		return false;
	}
	
	glViewport(0, 0, width, height);
	
	if (callback) {
		callback();
	}
	
	return true;
}

void Window::setInitCallback (callback_type callback) {
	Window::callback = callback;
}

void Window::setTitle (std::string title) {
	Window::title = title;
	
	if (! ready) { return; }
	
	SDL_WM_SetCaption(title.c_str(), title.c_str());
}

void Window::setFullscreen (bool b) {
	if (fullscreen == b) { return; }
	
	fullscreen = b;
	
	if (! ready) { return; }
	
	if (fullscreen) {
		old_width = width;
		old_height = height;
		
		width = fullscreen_width;
		height = fullscreen_height;
	} else {
		width = old_width;
		height = old_height;
	}
	
	reset();
}

void Window::setResizable (bool b) {
	resizable = b;
	
	if (! ready || fullscreen) { return; }
	
	reset();
}

void Window::resize (const int w, const int h) {
	width = w;
	height = h;
	
	if (! ready) { return; }
	
	reset();
}

