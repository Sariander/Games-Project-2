#ifndef _HERO_H                 // Prevent multiple definitions if this 
#define _HERO_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "textDX.h"
#include "sword.h"

namespace heroNS
{
	const int   WIDTH = 64;                 // image width (each frame)
	const int   HEIGHT = 64;                // image height
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const int   TEXTURE_COLS = 3;           // texture has 8 columns

	const int STAND_RIGHT = 0;
	const int STAND_LEFT = 3;
	const int STAND_UP = 6;
	const int STAND_DOWN = 9;
	const int START_LEFT = 4;
	const int END_LEFT = 5;
	const int START_RIGHT = 1;
	const int END_RIGHT = 2;
	const int START_UP = 7;
	const int END_UP = 8;
	const int START_DOWN = 10;
	const int END_DOWN = 11;
	const float ANIMATION_DELAY = 0.2f;

}

// inherits from Entity class
class Hero : public Entity
{
private:
	

public:
	// constructor
	Hero();

	Sword sword;
	DIRECTION dir;

	void update(float frameTime);
	void attack();
	void damage(WEAPON);
	void death();
	void heal();

	float getHealth() { return health; }
};
#endif