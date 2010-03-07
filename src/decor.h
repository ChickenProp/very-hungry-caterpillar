#ifndef _DECOR_H
#define _DECOR_H

#include "includes.h"

class Decor {
public:
	Decor(const char *sprite, int x, int y);
	Vector2D pos;
	const char *sprite;
	void draw();
};

#endif
