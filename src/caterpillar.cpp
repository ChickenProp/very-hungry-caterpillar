#include "caterpillar.h"

Cater::Cater() {
	length = 1;
	position.push_back(Vector2D(3,2));

	Vector2D velocity(0, 0);
}

void Cater::update () {
	if (Input::keyPressed(SDLK_LEFT)) {
		length++;
		position.push_front(Vector2D(posx(0)-1, posy(0)));
	}
	if (Input::keyPressed(SDLK_UP)) {
		length++;
		position.push_front(Vector2D(posx(0), posy(0)+1));
	}
	if (Input::keyPressed(SDLK_RIGHT)) {
		length++;
		position.push_front(Vector2D(posx(0)+1, posy(0)));
	}
	if (Input::keyPressed(SDLK_DOWN)) {
		length++;
		position.push_front(Vector2D(posx(0), posy(0)-1));
	}
}

void Cater::draw () {
	for (int i = 0; i <= length; i++)
		drawSection(i);
}

void Cater::drawSection(int i) {
	int tex = 0;
	if (i == 0)
		tex = TextureLoader::get("media/cater-head.tga");
	else if (i == length-1)
		tex = TextureLoader::get("media/cater-tail.tga");
	else
		tex = TextureLoader::get("media/cater-mid.tga");

	int x = (int) position[i].x;
	int y = (int) position[i].y;

	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x, y);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x, y-1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x-1, y-1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x-1, y);
	
	glEnd();
}

Vector2D Cater::pos(int i) {
	return position[i];
}
int Cater::posx(int i) {
	return (int) position[i].x;
}
int Cater::posy(int i) {
	return (int) position[i].y;
}
	
