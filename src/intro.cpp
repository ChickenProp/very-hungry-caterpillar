#include "intro.h"

namespace Intro {
	bool m_done = 0;
	int stage = 0;
	std::vector<Font*> texts;
}

void Intro::init () {
	Audio::play("media/audio/intro-1.wav");
	for (int i = 0; i < 2; i++) {
		texts.push_back(new Font("media/vera.ttf"));
	}
}

void Intro::update() {
	if (Input::keyPressed(SDLK_n))
	    m_done = 1;
	
	texts[0]->setText("In the light of the moon,");
	texts[1]->setText("a little egg lay on a leaf.");
}
void Intro::draw() {
	glColor3f(0,0,0);
	texts[0]->draw(2, 10, 0, 1);
	texts[1]->draw(2, 9, 0, 1);
}

bool Intro::done () {
	return m_done;
}
