#ifndef _THROWER_H                 // Prevent multiple definitions if this 
#define _THROWER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "textDX.h"
#include "sword.h"
#include "hobo.h"
#include "bottle.h"

namespace throwerNS
{
	const int   WIDTH = 64;                 // image width (each frame)
	const int   HEIGHT = 64;                // image height
	const int   X = GAME_WIDTH / 2 - WIDTH / 3; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 3;
	const float ROTATION_RATE = (float)PI; // radians per second
	const float SPEED = 50;                // 100 pixels per second
	enum DIRECTION { NONE, LEFT, RIGHT };     // rotation direction
	const int   TEXTURE_COLS = 0;           // texture has 8 columns
	const float ANIMATION_DELAY = 0.25f;
	const int HEALTH_MAX = 2;
	const int ATTACK_RANGE = 50;
}

// inherits from Entity class
class Thrower : public Hobo
{

public:
	// constructor
	Thrower();

	Bottle bottle;
	DIRECTION dir;

	void update(float frameTime, Entity* hero);
	void attack(Entity* hero);
	//void damage(WEAPON);
	//void death();
	//void heal();
	void draw(float frameTime);
	void spawn(GameStates level);
	void vectorTrack(Entity &target);
	void ai(float frameTime, Entity &target);
	//void vectorTrack(Entity &target);

	//float getHealth() { return health; }
};
#endif