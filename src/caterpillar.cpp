#include "caterpillar.h"

Cater::Cater() {
	length = 1;
	position.push_back(Vector2D(3,2));
}

void Cater::draw () {
	drawSection(0);
}

void Cater::drawSection(int i) {
	int tex = 0;
	if (i == 0)
		tex = TextureLoader::get("media/cater-head.tga");
	else if (i == length)
		tex = TextureLoader::get("media/cater-tail.tga");
	else
		tex = TextureLoader::get("media/cater-mid.tga");

	int x = (int) position[0].x;
	int y = (int) position[0].y;

	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x, y);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x, y-1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x+1, y-1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x+1, y);
	
	glEnd();
}
