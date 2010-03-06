#include "world.h"
#include "caterpillar.h"

World::World() {
	player = new Cater();
	width = 20;
	height = 15;
	tiles = "...................."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		"....................";
}

char World::getTile(int x, int y) {
	return tiles[(height - y - 1)*width + x];
}

void World::update() {
	player->update();
}

void World::draw() {
	player->draw();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			drawTile(getTile(x,y), x, y);
		}
	}
}

void World::drawTile(char t, int x, int y) {
	if (t != '.')
		return;

	glColor3f(0,0,0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y+1);
	glVertex2f(x+1, y+1);
	glVertex2f(x+1, y);
	glEnd();
}
