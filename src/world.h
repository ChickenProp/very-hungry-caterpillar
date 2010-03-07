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
	static void setTile(int x, int y, char c);
	static char getTile(Vector2D p);
	static void load(int level);
	static void addDecor(int x, int y, char c);
	static void setPlayer(int x, int y);
	static bool done();

	static bool m_done;
	static bool fadeLevel;
	static float fade;
	static Cater *player;
	static Font *topText1;
	static Font *topText2;	
	static Font *winText;
	static std::vector<Fruit*> fruit;
	static std::vector<Decor*> decor;
	static int width;
	static int height;
	static int level;
	static char *tiles;
};

#endif
