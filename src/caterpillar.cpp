#include "caterpillar.h"

Cater::Cater() {
	length = 4;
	position.push_back(Vector2D(3,2));

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

	delta += 0.25f;
	if (delta >= 1) {
		delta = 0;
		curMove = velocity;
		position.push_front(pos(0) + velocity);
		if (position.size() > length)
			position.pop_back();
	}

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

	float x = ((int) position[i].x) + offset.x;
	float y = ((int) position[i].y) + offset.y;

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
	
