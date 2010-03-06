#ifndef _CATERPILLAR_H
#define _CATERPILLAR_H

#include "includes.h"

class Cater {
public:
	Cater();

	int length;
	std::vector<Vector2D> position;

	void update();
	void draw();
	void drawSection(int i);
};

#endif
