#ifndef _HOBO_H                 // Prevent multiple definitions if this 
#define _HOBO_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "textDX.h"
#include "sword.h"
#include <cmath>

namespace hoboNS
{
	const int   WIDTH = 64;                 // image width (each frame)
	const int   HEIGHT = 64;                // image height
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI; // radians per second
	const float SPEED = 25;                // 100 pixels per second
	enum DIRECTION { NONE, LEFT, RIGHT };     // rotation direction
	const int   TEXTURE_COLS = 2;           // texture has 8 columns
	const float ANIMATION_DELAY = 0.5f;

	const int RIGHT_WALK_START = 0;
	const int RIGHT_WALK_END = 1;
	const int LEFT_WALK_START = 2;
	const int LEFT_WALK_END = 3;

	const int RIGHT_ATTACK_START = 4;
	const int RIGHT_ATTACK_END = 5;
	const int LEFT_ATTACK_START = 6;
	const int LEFT_ATTACK_END = 7;

	const float COLOR_WAIT = .2f;
	const float HIT_DURATION = 0.1f;

	const int HEALTH_MAX = 4;
}

// inherits from Entity class
class Hobo : public Entity
{
protected:
	bool collision;                 
    bool target;  
	int directionX;
	int directionY;

	int health;
	float targetDist;

	float speed;

	float colorTimer;
	COLOR_ARGB filter;

	float hitTimer;
	D3DXVECTOR2 hitVector;

public:
	// constructor
	Hobo();

	Sword sword;
	DIRECTION dir;

	void update(float frameTime);
	void attack();
	bool damage(WEAPON, D3DXVECTOR2);
	void death();
	void heal();
	void spawn(GameStates level);

	void draw(float frameTime);


	void ai(float frameTime, Entity &target);
	void vectorTrack(Entity &target);

	float getHealth() { return health; }
};
#endif