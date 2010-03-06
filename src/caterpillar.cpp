#include "caterpillar.h"

Cater::Cater() {
	length = 4;
	position.push_back((feet_t) {Vector2D(3,2), O_BL});

	Vector2D velocity(0, 0);
	Vector2D curMove(0, 0);
	delta = 0;
}

void Cater::update () {
	if (Input::keyPressed(SDLK_LEFT))
		velocity = Vector2D(-1, 0);
	if (Input::keyPressed(SDLK_UP))
		velocity = Vector2D(0, 1);
	if (Input::keyPressed(SDLK_RIGHT))
		velocity = Vector2D(1, 0);
	if (Input::keyPressed(SDLK_DOWN))
		velocity = Vector2D(0, -1);

	delta += 0.125f;
	if (delta < 1)
		return;

	delta = 0;
	position.push_front((feet_t) {pos(0) + curMove, O_BL});
	if (position.size() > length)
		position.pop_back();

	char heading = World::getTile(pos(0) + velocity);
	if (heading == '.') {
		if (velocity.y == 0) { //moving horizontally
			if (World::getTile(posx(0), posy(0)+1) == '.') {
				die();
				velocity = -velocity;
			}
			else {
				velocity = Vector2D(0, 1);
			}
		}
		else if (velocity.x == 0) { // moving vertically
			char left = World::getTile(posx(0)-1, posy(0));
			char right = World::getTile(posx(0)+1, posy(0));
			if (left == '.' && right == '.') {
				die();
				velocity = -velocity;
			}
			else if (left == '.')
				velocity = Vector2D(1, 0);
			else if (right == '.')
				velocity = Vector2D(-1, 0);
			else
				velocity = Vector2D(1, 0);
		}
	}

	curMove = velocity;
}

void Cater::die () {
	D("you died.");
}

void Cater::draw () {
	Vector2D next = pos(0)+curMove;
	for (int i = 0; i < position.size(); i++) {
		drawSection(i, delta*(next - pos(i)));
		next = pos(i);
	}
}

void Cater::drawSection(int i, Vector2D offset) {
	int tex = 0;
	if (i == 0)
		tex = TextureLoader::get("media/cater-head.tga");
	else if (i == position.size()-1)
		tex = TextureLoader::get("media/cater-tail.tga");
	else
		tex = TextureLoader::get("media/cater-mid.tga");

	float x = posx(i) + offset.x;
	float y = posy(i) + offset.y;

	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x, y);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x, y+1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x+1, y+1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x+1, y);
	
	glEnd();
}

Vector2D Cater::pos(int i) {
	return position[i].pos;
}
int Cater::posx(int i) {
	return (int) position[i].pos.x;
}
int Cater::posy(int i) {
	return (int) position[i].pos.y;
}
	
