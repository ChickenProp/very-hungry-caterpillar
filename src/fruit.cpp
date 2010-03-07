#include "fruit.h"

Fruit::Fruit(const char *f, int mx, int my) {
	sprite = f;
	pos = Vector2D(mx, my);
}

void Fruit::draw() {
	int tex = TextureLoader::get(sprite);
	glBindTexture(GL_TEXTURE_2D, tex);
	float x = pos.x;
	float y = pos.y;
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex2f(x, y);
	glTexCoord2f(1,1);
	glVertex2f(x, y-1);
	glTexCoord2f(0,1);
	glVertex2f(x-1, y-1);
	glTexCoord2f(0,0);
	glVertex2f(x-1, y);
	glEnd();
}
       
