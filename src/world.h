#ifndef _WORLD_H
#define _WORLD_H

#include "includes.h"

class World {
public:
	World();
	void update();
	void draw();
	void drawTile(char t, int x, int y);
	char getTile(int x, int y);

	Cater *player;
	Font *font;
	std::vector<Fruit*> fruit;
	int width;
	int height;
	const char *tiles;
};

#endif
