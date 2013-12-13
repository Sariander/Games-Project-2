#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "textDX.h"
#include "sword.h"
#include "hobo.h"

namespace bossNS
{
	const int   WIDTH = 100;                 // image width (each frame)
	const int   HEIGHT = 100;                // image height
	const int   X = GAME_WIDTH / 4;			 // location on screen
	const int   Y = GAME_HEIGHT / 4;
	const float ROTATION_RATE = (float)PI; // radians per second
	const float SPEED = 10;                // 100 pixels per second
	enum DIRECTION { NONE, LEFT, RIGHT };     // rotation direction
	const int   TEXTURE_COLS = 3;           // texture has 8 columns
	const float ANIMATION_DELAY = 0.2f;
	const int HEALTH_MAX = 20;

	const int NUM_BALLS = 4;
	const int BOSS_WALK_1 = 0;
	const int BOSS_WALK_2 = 1;
	const int BOSS_WALK_3 = 2;
}

// inherits from Entity class
class Boss : public Hobo
{
private:
	float theta;

public:
	// constructor
	Boss();

	Sword sword[bossNS::NUM_BALLS];

	void update(float frameTime);
	//void attack(Entity* hero);
	//void damage(WEAPON);
	//void death();
	//void heal();
	//void draw(float frameTime);
	void spawn(GameStates level);
	//void vectorTrack(Entity &target);
	//void ai(float frameTime, Entity &target);
	//void vectorTrack(Entity &target);

	//float getHealth() { return health; }
};
#endif