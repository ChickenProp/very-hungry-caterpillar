#include "font.h"

Font::Font () {
	/* Cast to avoid gcc warning. */
	initialize(32, (char *) "/usr/share/fonts/corefonts/impact.ttf");
}

Font::Font (const char *face) {
	initialize(32, face);
}

Font::Font (int size, const char *face) {
	initialize(size, face);
}

void Font::draw (float x, float y, float w, float h) {
	if (!isRendered)
		render();
	if (!isRendered)
		return;

	if (w == 0 && h == 0) {
		w = origw;
		h = origh;
	}
	else if (w == 0)
		w = h * aspect;
	else if (h == 0)
		h = w / aspect;

	GLint origtex = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &origtex);

	glBindTexture(GL_TEXTURE_2D, texture);

	//glColor3f(0,0,0);

	glBegin(GL_QUADS);

/* Front faces wind counterclockwise by default. */
	glTexCoord2f(0,0);
	glVertex2f(x,y);
	glTexCoord2f(0,texh);
	glVertex2f(x,y-h);
	glTexCoord2f(texw,texh);
	glVertex2f(x+w,y-h);
	glTexCoord2f(texw,0);
	glVertex2f(x+w,y);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, origtex);
}

void Font::initialize (int size, const char *face) {
	if (!TTF_WasInit()) {
		if (TTF_Init()==-1) {
			fprintf(stderr, "There was an error with TTF: %s\n",
			        TTF_GetError());
			font = NULL;
			return;
		}
		atexit(TTF_Quit);
	}

	font = TTF_OpenFont(face, size);
	color = (SDL_Color) {255, 255, 255};
	text = NULL;
}

Font *Font::setText (const char *t) {
	int len = strlen(t) + 1;
	char *mem = (char *) malloc(len*sizeof(char));
	strncpy(mem, t, len);
	if (text != NULL)
		free(text);
	text = mem;
	isRendered = 0;
	return this;
}

void Font::render () {
	GLint origtex = 0;

	// Passing an empty string to RenderText_Blended seems to make it return
	// NULL and crash the rest of the function.
	if (!font || !text || strlen(text) == 0)
		return;

	glGenTextures(1, &texture);

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &origtex);
	
	SDL_Surface *temp = TTF_RenderText_Blended(font, text, color);
	SDL_Surface *real
		= SDL_CreateRGBSurface(0, next_power_of_2(temp->w),
		                       next_power_of_2(temp->h), 32, 
	                       0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

	origw = (float) temp->w;
	origh = (float) temp->h;
	texw = origw / real->w;
	texh = origh / real->h;
	aspect = origw / origh;

	SDL_SetAlpha(temp, 0, 255);
	SDL_BlitSurface(temp, 0, real, 0);

	glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, real->w, real->h, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, real->pixels );
        SDL_FreeSurface(temp);
        SDL_FreeSurface(real);

	isRendered = 1;

	glBindTexture(GL_TEXTURE_2D, origtex);
}

int Font::next_power_of_2 (int x) {
	/* This won't happen. */
	if (x <= 0)
		return 0;

	int i = 1;
	x--;
	while (x) {
		i *= 2;
		x /= 2;
	}
	return i;
}

/*
#include <cstdio>

int main () {
	printf("above: %d\n", Font::next_power_of_2(163));
	return 0;
}
*/
