#include "world.h"
#include "caterpillar.h"
#include "fruit.h"
#include "decor.h"

Cater *World::player = NULL;
char *World::tiles = NULL;
Font *World::topText1 = NULL;
Font *World::topText2 = NULL;
Font *World::winText = NULL;
int World::width = 20;
int World::height = 14;
int World::level = 1;
std::vector<Fruit*> World::fruit;
std::vector<Decor*> World::decor;
bool World::fadeLevel = 0;
float World::fade = 0;
bool World::m_done = 0;

World::World() {
	topText1 = new Font("media/vera.ttf");
	topText2 = new Font("media/vera.ttf");
	winText = new Font("media/vera.ttf");
	player = new Cater();
	load(level);
}

bool World::done() {
	return m_done;
}

void chomp(char *str) {
	int l = strlen(str);
	if (l != 0 && str[l-1] == '\n')
		str[l-1] = 0;
}

void World::load(int l) {
	fruit.clear();
	decor.clear();
	fade = 0;
	char *level = (char *)malloc(20*sizeof(char));
	snprintf(level, 20, "media/level%02d.lvl", l);

	char *wavfile = (char *)malloc(50 * sizeof(char));
	snprintf(wavfile, 50, "media/audio/level%02d-intro.wav", l);
	Audio::play(wavfile, 1);
	free(wavfile);

	FILE *stream = fopen(level, "r");
	if (stream == NULL) {
		m_done = 1;
		free(level);
		return;
	}
	char *buffer = (char *) malloc(80 * sizeof(char));

	buffer[0] = ' ';
	fgets(buffer+1, 79, stream);
	chomp(buffer);
	topText1->setText(buffer);

	fgets(buffer, 80, stream);
	chomp(buffer);
	topText2->setText(buffer);

	fgets(buffer, 80, stream);
	chomp(buffer);
	winText->setText(buffer);
	fadeLevel = (strlen(buffer) != 0);

	char *fruitfile = (char *) malloc(50 * sizeof(char));
	fgets(buffer, 80, stream);
	chomp(buffer);
	snprintf(fruitfile, 50, "media/%s.tga", buffer);

	char *data = (char *) malloc(width * height * sizeof(char));
	memset(data, ' ', width*height*sizeof(char));
	char *p = data;

	for (int i = 0; i < height; i++) {
		fgets(buffer, 80, stream);
		int len = strlen(buffer);
		if (len > width)
			len = width;
		memcpy(p, buffer, len);
		p += width;
	}

	if (tiles)
		free(tiles);
	tiles = data;

	free(level);
	free(buffer);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			char c = getTile(x,y);
			switch (c) {
			case ' ': case '.':
				continue;
			case 'f':
				fruit.push_back(new Fruit(fruitfile, x, y));
				break;
			case '*':
				setPlayer(x,y); break;
			case '^': case 'v':
				addDecor(x,y,c); break;
			default:
				break;
			}
			setTile(x, y, ' ');
		}
	}

	// I have no idea why, but this makes things break.
	//free(fruitfile);
}

void World::addDecor (int x, int y, char c) {
	const char *f = NULL;
	switch (c) {
	case '^': f = "media/arrow-lu.tga"; break;
	case 'v': f = "media/arrow-rd.tga"; break;
	}

	decor.push_back(new Decor(f, x, y));
}


void World::setPlayer(int x, int y) {
	player->setPos(x,y);
}


char World::getTile(int x, int y) {
	return tiles[(height - y - 1)*width + x];
}

char World::getTile(Vector2D p) {
	return getTile((int)p.x, (int)p.y);
}

void World::setTile(int x, int y, char c) {
	tiles[(height - y - 1)*width + x] = c;
}

void World::update() {
	if (Input::keyPressed(SDLK_n))
		load(++level);

	player->update(fade == 0);

	for (int i = 0; i < fruit.size(); i++) {
		if (player->pos(0) == fruit[i]->pos) {
			if (fruit.size() == 1)
				player->length++;
			fruit.erase(fruit.begin()+i);
			Audio::play("media/audio/eat.wav");
			break;
		}
	}
	if (fruit.size() == 0) {
		if (fadeLevel && fade == 0) {
			char *file = (char*) malloc(50 * sizeof(char));
			snprintf(file, 50,
			         "media/audio/level%02d-win.wav", level);
			Audio::play(file);
			free(file);
		}

		if (!fadeLevel || fade >= 1.5)
			load(++level);
		else
			fade += 0.01;
	}
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

	glColor3f(0,0,0);
	topText1->draw(0, 16, 0, 1);
	topText2->draw(1, 15, 0, 1);

	if (fade > 0) {
		glColor4f(1,1,1,fade);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(width, 0);
		glVertex2f(width, height);
		glVertex2f(0, height);
		glEnd();

		glColor3f(0, 0, 0);
		winText->draw(1, 15, 0, 1);
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
