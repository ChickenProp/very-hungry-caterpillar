#include "audio.h"
#include "SDL_mixer.h"
#include <map>

namespace Audio {
	std::map<std::string, Mix_Chunk*> chunks;
	
	Mix_Chunk* getChunk (std::string file);
};

Mix_Chunk* Audio::getChunk (std::string file) {
	std::map<std::string, Mix_Chunk*>::iterator iter = chunks.find(file);
	
	if (iter != chunks.end()) {
		return iter->second;
	}
	
	// Need to load from disk
	
	Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
	
	chunks[file] = chunk;
	
	return chunk;
}

void Audio::init () {
	int rate = 22050;
	Uint16 format = AUDIO_S16;
	int channels = 2;
	int chunksize = 256;
	if (Mix_OpenAudio(rate, format, channels, chunksize) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		return;
	}

	atexit(Mix_CloseAudio);
	
	Mix_Music* music = Mix_LoadMUS("audio/music.ogg");
	
	Mix_PlayMusic(music, -1);
}

int Audio::play (std::string file, int count) {
	Mix_Chunk* chunk = getChunk(file);
	
	if (! chunk) { return -1; }
	
	return Mix_PlayChannel(-1, chunk, count - 1);
}


