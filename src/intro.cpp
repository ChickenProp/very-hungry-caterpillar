#include "intro.h"

namespace Intro {
	bool m_done = 0;
	int stage = 0;
	std::vector<Font*> texts;
	int time = 0;
	int elapsed = 0;
	int end1 = 5000;
	int start2 = 5300;
	int end2 = 15500;
	int start3 = 16000;
	int end3 = 18000;
	int end = 18500;
	bool playing2 = 0;
	bool playing3 = 0;
}

void Intro::init () {
	Audio::play("media/audio/intro-1.wav");
	for (int i = 0; i < 7; i++) {
		texts.push_back(new Font("media/vera.ttf"));
	}
	time = SDL_GetTicks();
}

void Intro::update() {
	if (Input::keyPressed(SDLK_n))
	    m_done = 1;

	elapsed = SDL_GetTicks() - time;
	
	texts[0]->setText("In the light of the moon,");
	texts[1]->setText("a little egg lay on a leaf.");
	texts[2]->setText("One Sunday morning the warm");
	texts[3]->setText("sun came up and -pop- out");
	texts[4]->setText("of the egg came a tiny and very");
	texts[5]->setText("hungry caterpillar.");
	texts[6]->setText("He started to look for some food.");

	if (elapsed >= start2 && !playing2) {
		Audio::play("media/audio/intro-2.wav");
		playing2 = 1;
	}
	if (elapsed >= start3 && !playing3) {
		Audio::play("media/audio/intro-3.wav");
		playing3 = 1;
	}
	if (elapsed >= end)
		m_done = 1;
	
}
void Intro::draw() {
	if (elapsed <= end1) {
		float alpha = 1;

		if (elapsed < 500)
			alpha = (float)elapsed/500;
		if (elapsed > end1-500)
			alpha = (float)(end1-elapsed)/500;

		glColor4f(0,0,0,alpha);
		texts[0]->draw(2, 10, 0, 1);
		texts[1]->draw(2, 9, 0, 1);
	}

	else if (elapsed >= start2 && elapsed < end2) {
		int f = elapsed - start2;
		float alpha = 1;
		if (f < 500)
			alpha = (float)f/500;
		if (elapsed > end2 - 500)
			alpha = (float)(end2-elapsed)/500;

		glColor4f(0,0,0,alpha);
		texts[2]->draw(2, 10, 0, 1);
		texts[3]->draw(2, 9, 0, 1);
		texts[4]->draw(2, 8, 0, 1);
		texts[5]->draw(2, 7, 0, 1);
	}

	else if (elapsed >= start3) {
		int f = elapsed - start3;
		float alpha = 1;
		if (f < 500)
			alpha = (float) f/500;
		if (elapsed > end3-500)
			alpha = (float) (end3-elapsed)/500;

		glColor4f(0,0,0,alpha);
		texts[6]->draw(2, 8, 0, 1);
	}
}

bool Intro::done () {
	return m_done;
}
