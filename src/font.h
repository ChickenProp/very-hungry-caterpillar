#ifndef _FONT_H
#define _FONT_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "GL/gl.h"

typedef enum { C_TL, C_TR, C_BL, C_BR } corner_t;

class Font {
public:
	Font();
	Font(int size);
	Font(const char *face);
	Font(int size, const char *face);

	~Font();

	Font *setFace(const char *face);
	Font *setSize(int size);
	Font *setText(const char *text);
	Font *setColor(SDL_Color col);

	void draw();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);


protected:
	static int next_power_of_2(int x);
	void initialize(int size, const char *face);
	void render();

	bool isRendered;
	TTF_Font *font;
	SDL_Color color;
	char *text;
	GLuint texture;

	float texw, texh;
	float origw, origh;
	float aspect;
};

#endif
