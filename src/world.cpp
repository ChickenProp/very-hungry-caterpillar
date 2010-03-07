#include "world.h"
#include "caterpillar.h"
#include "fruit.h"
#include "decor.h"

Cater *World::player = NULL;
const char *World::tiles = NULL;
Font *World::font = NULL;
int World::width = 20;
int World::height = 15;
std::vector<Fruit*> World::fruit;
std::vector<Decor*> World::decor;

World::World() {
	player = new Cater();
	tiles = "...................."
		".                  ."
		".                  ."
		".                  ."
		". ....        .... ."
		".                  ."
		".       ....       ."
		".                  ."
		".                  ."
		".                  ."
		".                  ."
		".       ....       ."
		".                  ."
		".                  ."
		"....................";
	font = new Font("media/vera.ttf");
	font->setText(" On Monday he ate through one apple.");
	fruit.push_back(new Fruit("media/apple.tga", 5,12));
	decor.push_back(new Decor("media/arrow-lu.tga", 2,2));
	load(1);
}

char World::getTile(int x, int y) {
	return tiles[(height - y - 1)*width + x];
}

char World::getTile(Vector2D p) {
	return getTile((int)p.x, (int)p.y);
}

void World::update() {
	player->update();
}

void World::draw() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			drawTile(getTile(x,y), x, y);
		}
	}

	foreach (Fruit *f, fruit) {
		f->draw();
	}
	foreach (Decor *d, decor) {
		d->draw();
	}

	player->draw();

	font->draw(0, 16, 0, 1);

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
