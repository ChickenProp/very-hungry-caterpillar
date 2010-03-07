#ifndef _FRUIT_H
#define _FRUIT_H

#include "includes.h"

class Fruit {
public:
	Fruit(const char *sprite, int x, int y);
	Vector2D pos;
	const char *sprite;
	void draw();
};

#endif
