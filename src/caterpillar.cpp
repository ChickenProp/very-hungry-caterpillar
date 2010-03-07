#include "caterpillar.h"

or_t or_fall (or_t orig) {
	switch (orig) {
	case O_BL: return O_RD;
	case O_RD: return O_TR;
	case O_TR: return O_LU;
	case O_LU: return O_BL;
	case O_BR: return O_LD;
	case O_LD: return O_TL;
	case O_TL: return O_RU;
	case O_RU: return O_BR;
	}
}

or_t or_unfall (or_t o) {
	return or_fall(or_fall(or_fall(o)));
}

or_t or_flip1 (or_t o) {
	switch (o) {
	case O_BL: return O_TL;
	case O_RD: return O_LD;
	case O_TR: return O_BR;
	case O_LU: return O_RU;
	case O_BR: return O_TR;
	case O_LD: return O_RD;
	case O_TL: return O_BL;
	case O_RU: return O_LU;
	}
}
or_t or_flip2 (or_t o) {
	switch (o) {
	case O_BL: return O_BR;
	case O_RD: return O_RU;
	case O_TR: return O_TL;
	case O_LU: return O_LD;
	case O_BR: return O_BL;
	case O_LD: return O_LU;
	case O_TL: return O_TR;
	case O_RU: return O_RD;
	}
}

char or_dir (or_t o) {
	switch (o) {
	case O_BL: case O_TL: return 'l';
	case O_BR: case O_TR: return 'r';
	case O_LD: case O_RD: return 'd';
	case O_LU: case O_RU: return 'u';
	}
}

char or_feetdir (or_t o) {
	switch (o) {
	case O_BL: case O_BR: return 'd';
	case O_TL: case O_TR: return 'u';
	case O_LD: case O_LU: return 'l';
	case O_RU: case O_RD: return 'r';
	}
}

Cater::Cater() {
	length = 4;
	position.push_back((feet_t) {Vector2D(5,1), O_BR});

	velocity = Vector2D(0, 0);
	attempt = 'x';
	delta = 0;
	falling = 0;
}

void Cater::update () {
/*  Where does the player want to go?
    This needs to be called every frame, because keyPressed is frame-dependant.
*/
	if (Input::keyPressed(SDLK_LEFT))
		attempt = 'l';
	if (Input::keyPressed(SDLK_UP))
		attempt = 'u';
	if (Input::keyPressed(SDLK_RIGHT))
		attempt = 'r';
	if (Input::keyPressed(SDLK_DOWN))
		attempt = 'd';



	delta += 0.125f;
	if (delta < 1)
		return;

	delta = 0;
	position.push_front((feet_t) {pos(0) + velocity, cling(0)});
	if (position.size() > length)
		position.pop_back();

/*  In what direction am I currently travelling? */
	char vel = vec2char(velocity);
	bool velU = velocity.y > 0;
	bool velD = velocity.y < 0;
	bool velL = velocity.x < 0;
	bool velR = velocity.x > 0;

	bool attU = attempt == 'u';
	bool attD = attempt == 'd';
	bool attL = attempt == 'l';
	bool attR = attempt == 'r';


/*  What is the terrain around me? */

	char top = World::getTile(posx(0), posy(0) + 1);
	char bot = World::getTile(posx(0), posy(0) - 1);
	char lft = World::getTile(posx(0)-1, posy(0));
	char rgt = World::getTile(posx(0)+1, posy(0));
	char tl = World::getTile(posx(0) - 1, posy(0) + 1);
	char bl = World::getTile(posx(0) - 1, posy(0) - 1);
	char br = World::getTile(posx(0) + 1, posy(0) - 1);
	char tr = World::getTile(posx(0) + 1, posy(0) + 1);


/* Where are my feet? */
	or_t feet = cling(0);

	char heading = (velR ? rgt
	                : velL ? lft
	                : velU ? top
	                : velD ? bot
	                : ' ');
	char heading_attempt = (attR ? rgt
	                        : attL ? lft
	                        : attU ? top
	                        : attD ? bot
	                        : ' ');
	char underfoot = (feet == O_BL || feet == O_BR ? bot
	                  : feet == O_TL || feet == O_TR ? top
	                  : feet == O_LD || feet == O_LU ? lft
	                  : feet == O_RD || feet == O_RU ? rgt
	                  : ' ');
	char overhead = (feet == O_BL || feet == O_BR ? top
	                  : feet == O_TL || feet == O_TR ? bot
	                  : feet == O_LD || feet == O_LU ? rgt
	                  : feet == O_RD || feet == O_RU ? lft
	                  : ' ');
	char heading_feet = (feet == O_BL || feet == O_LD ? bl
	                     : feet == O_BR || feet == O_RD ? br
	                     : feet == O_TL || feet == O_LU ? tl
	                     : feet == O_TR || feet == O_RU ? tr
	                     : ' ');
	char overhead_front = (feet == O_BL || feet == O_RU ? tl
	                       : feet == O_BR || feet == O_LU ? tr
	                       : feet == O_TL || feet == O_RD ? bl
	                       : feet == O_TR || feet == O_LD ? br
	                       : ' ');
	char overhead_back = (feet == O_BL || feet == O_LD ? tr
	                      : feet == O_BR || feet == O_RD ? tl
	                      : feet == O_TL || feet == O_LU ? br
	                      : feet == O_TR || feet == O_RU ? bl
	                      : ' ');

/* What am I doing now? */
	or_t nfeet = feet; // new cling; default don't change
	char nvel = 'x'; // new vel; default don't change

	if (falling) {
		if (bot == ' ')
		    goto fin;

		falling = 0;

		if (attempt == 'l') {
			nfeet = O_BL;
			nvel = 'l';
			goto fin;
		}
		else {
			nfeet = O_BR;
			nvel = 'r';
			goto fin;
		}
	}

	if (attempt == vel) {
		if (underfoot == '.' && heading == ' ')
			goto fin;
		if (heading_feet == '.' && heading == ' ')
			goto fin;

		if (heading == ' ') {
			if (vel == 'd') {
				falling = 1;
				goto fin;
			}
			// There must be something behind my feet? I think?
			nfeet = or_fall(feet);
			nvel = or_dir(nfeet);
			goto fin;
		}

	}

	if (char2vec(attempt) == - velocity) {
		// If I just came from there, I can probably go back.
		nvel = attempt;
		nfeet = or_flip2(feet);
		goto fin;
	}

	if (attempt == or_feetdir(feet)) {
		if (underfoot == ' ') {
			nfeet = or_fall(feet);
			nvel = or_dir(nfeet);
			goto fin;
		}
	}

	if (attempt == or_feetdir(or_flip1(feet))) {
		if (overhead == '.') {
			nfeet = or_flip1(feet);
			goto fin;
		}
		if (overhead_front == '.') {
			nfeet = or_unfall(feet);
			nvel = or_dir(nfeet);
			goto fin;
		}
		if (overhead_back == '.') {
			nfeet = or_flip1(or_unfall(feet));
			nvel = or_dir(nfeet);
			goto fin;
		}
	}

/* In theory, if we get here, we couldn't go in the direction we wanted.
 Can I assume we don't want to go there any more? */

/* There's an exception: if we wanted to go down, we might still be able to. */
	if (attempt == 'd' && bot == ' ' && underfoot == '.') {
		nvel = 'd';
		nfeet = or_unfall(feet);
		falling = 1;
		goto fin;
	}

	if (vel == 'x' && (attL || attR)) {
		nvel = attempt;
		nfeet = attL ? O_BL : O_BR;
		goto fin;
	}

	attempt = 'x';
	if (underfoot == ' ') {
		nfeet = or_fall(feet);
		nvel = or_dir(nfeet);
		goto fin;
	}
	
	if (heading == ' ') {
		goto fin;
	}

	if (overhead == ' ') {
		nfeet = or_unfall(feet);
		nvel = or_dir(nfeet);
		goto fin;
	}

	fin:
	
	cling(0, nfeet);

	if (nvel != 'x')
		velocity = char2vec(nvel);
}

Vector2D Cater::char2vec (char d) {
	switch (d) {
	case 'l': return Vector2D(-1, 0); break;
	case 'r': return Vector2D(1, 0); break;
	case 'u': return Vector2D(0, 1); break;
	case 'd': return Vector2D(0, -1); break;
	default: return Vector2D(0, 0); break;
	}
}

char Cater::vec2char (Vector2D v) {
	return (v.x < 0 ? 'l' :
	        v.x > 0 ? 'r' : 
	        v.y < 0 ? 'd' :
	        v.y > 0 ? 'u' :
	        'x');
}


void Cater::die () {
	D("you died.");
}

void Cater::draw () {
	Vector2D next = pos(0)+velocity;
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

	float x = posx(i) + offset.x;
	float y = posy(i) + offset.y;

	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1,1,1);
	
	glPushMatrix();
	glTranslatef(x+0.5, y+0.5, 0);

	int deg = 0;
	int sx = 1;
	int sy = 1;

	switch (cling(i)) {
	case O_BR: sx = -1;
	case O_BL: break;
	case O_TR: sx = -1;
	case O_TL: sy = -1; break;
	case O_LD: sx = -1;
	case O_LU: deg = -90; break;
	case O_RU: sx = -1;
	case O_RD: deg = 90; break;
	}

	glRotatef(deg, 0, 0, 1);
	glScalef(sx, sy, 1);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.5, -0.5);
	
	glEnd();

	glPopMatrix();
}

or_t Cater::cling(int i) {
	return position[i].cling;
}
void Cater::cling(int i, or_t n) {
	position[i].cling = n;
}
Vector2D Cater::pos(int i) {
	return position[i].pos;
}
int Cater::posx(int i) {
	return (int) position[i].pos.x;
}
int Cater::posy(int i) {
	return (int) position[i].pos.y;
}
	
