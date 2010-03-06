#include "texture_loader.h"

#include <map>

#include "SDL_image.h"

static std::map<std::string, GLuint> textures;

void TextureLoader::clearAll () {
	textures.clear();
}

GLuint TextureLoader::get (std::string file) {
	std::map<std::string, GLuint>::iterator iter = textures.find(file);
	
	if (iter != textures.end()) {
		return iter->second;
	}
	
	// Need to load from disk
	
	SDL_Surface* temp = IMG_Load(file.c_str());
	
	if (!temp) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		textures[file] = 0;
		return 0;
	}
	
	GLuint textureID = create(temp);
	
	SDL_FreeSurface(temp);
	
	textures[file] = textureID;
	
	return textureID;
}

GLuint TextureLoader::create (SDL_Surface* surface, GLuint oldTexture) {
	if (!surface) { return 0; }
  
	GLenum texture_format;
	GLint colors = surface->format->BytesPerPixel;
	
	if (colors == 4) {
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (colors == 3) {
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		printf("Image is not truecolour");
		return 0;
	}
	
	GLuint textureID;
	
	if (oldTexture) {
		textureID = oldTexture;
	} else {
		glGenTextures(1, &textureID);
	}
	
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	if (! oldTexture) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, colors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	return textureID;
}

