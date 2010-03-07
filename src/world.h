#ifndef _WORLD_H
#define _WORLD_H

#include "includes.h"

class World {
public:
	World();
	static void update();
	static void draw();
	static void drawTile(char t, int x, int y);
	static char getTile(int x, int y);
	static char getTile(Vector2D p);
	static void load(int level);

	static Cater *player;
	static Font *font;
	static std::vector<Fruit*> fruit;
	static std::vector<Decor*> decor;
	static int width;
	static int height;
	static const char *tiles;
};

#endif
