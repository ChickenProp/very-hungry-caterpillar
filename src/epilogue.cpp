#include "epilogue.h"
#include "includes.h"

namespace Epilogue {
	bool m_init = 0;
	std::vector<Font*> texts;
	int time = 0;
	int elapsed = 0;
	int end1 = 5000;
	int start2 = 5300;
	int end2 = 15500;
	int start3 = 16000;
	int end3 = 18000;
	int end = 18500;
}

void Epilogue::init () {
	Audio::play("media/audio/epilogue.wav");
	m_init = 1;

	time = SDL_GetTicks();

	const char *strings[] =
		{ "and after that he felt much better.",
		  "Now he wasn't hungry anymore - and",
		  "he wasn't little any more. He was a big",
		  "fat caterpillar. He started to build a",
		  "small house called a cocoon around",
		  "himself. He stayed inside for more than",
		  "two weeks. Then one day he nibbled a",
		  "hole in the cocoon and pushed his way",
		  "out, and...",
		  "He was a beautiful butterfly."
		};

	for (int i = 0; i < 10; i++) {
		texts.push_back(new Font("media/vera.ttf"));
		texts[i]->setText(strings[i]);
	}
}

void Epilogue::update () {
	if (!m_init)
		init();
}

void Epilogue::draw() {
	if (!m_init)
		return;
	glColor3f(0,0,0);
	for (int i = 0; i < 10; i++) {
		texts[i]->draw(2, 13-i, 0, 1);
	}
}
