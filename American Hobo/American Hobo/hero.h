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

	const int START_ATTACK_RIGHT = 13;
	const int END_ATTACK_RIGHT = 12;
	const int START_ATTACK_LEFT = 15;
	const int END_ATTACK_LEFT = 14;
	const int START_ATTACK_UP = 17;
	const int END_ATTACK_UP = 16;
	const int START_ATTACK_DOWN = 19;
	const int END_ATTACK_DOWN = 18;

	const int START_ROLL = 20;
	const int END_ROLL = 23;

	const float HIT_DURATION = 0.2f;
	const float DASH_DURATION = 0.2f;
	const float COLOR_WAIT = .2f;

	const int HEALTH_MAX = 10;

}

// inherits from Entity class
class Hero : public Entity
{
private:
	float hitTimer;
	D3DXVECTOR2 hitVector;

	float colorTimer;
	COLOR_ARGB filter;

	float dashTimer;
	D3DXVECTOR2 dashVector;

	bool returnDebounce;
	bool attackDebounce;

public:
	// constructor
	Hero();

	Sword sword;
	DIRECTION dir;
	int health;

	void update(float frameTime);
	void attack();
	void dash();
	void damage(WEAPON, D3DXVECTOR2);
	void death();
	void heal();
	void draw(float frameTime);
	
	int getHealth() { return health; }
	void setColorTimer(int val) { colorTimer = val; }
};
#endif