#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"
#include "SDL_mixer.h"
#include "GL/gl.h"
#include "boost/foreach.hpp"

#define foreach BOOST_FOREACH

/* If we only need the existence of these classes (none of their members), we
   can avoid explicitly including them. */

#define D(format, ...)							\
	do {								\
		if (1)					\
			fprintf(stderr, format "\n", ##__VA_ARGS__);	\
	}								\
	while (0)

#endif
