#ifndef _CATERPILLAR_H
#define _CATERPILLAR_H

#include "includes.h"
#include "world.h"

typedef enum { O_BL, O_BR, O_TL, O_TR, O_LD, O_LU, O_RD, O_RU } or_t;

typedef struct {
	Vector2D pos;
	or_t cling;
} feet_t;
	

class Cater {
public:
	Cater();

	int length;
	std::deque<feet_t> position;
	Vector2D velocity, curMove;
	float delta;

	void update();
	void draw();
	void drawSection(int i, Vector2D offset);
	void die();

	Vector2D pos(int i);
	int posx(int i);
	int posy(int i);
};

#endif
