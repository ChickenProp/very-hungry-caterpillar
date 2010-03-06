#ifndef _CATERPILLAR_H
#define _CATERPILLAR_H

#include "includes.h"

class Cater {
public:
	Cater();

	int length;
	std::deque<Vector2D> position;
	Vector2D velocity, curMove;
	float delta;

	void update();
	void draw();
	void drawSection(int i, Vector2D offset);

	Vector2D pos(int i);
	int posx(int i);
	int posy(int i);
};

#endif
