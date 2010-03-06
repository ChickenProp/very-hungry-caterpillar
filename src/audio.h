#ifndef AUDIO_H
#define AUDIO_H

#include <string>

namespace Audio {
	void init ();
	int play (std::string file, int count = 1);
};

#endif

