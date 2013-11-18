#ifndef _HOBO_H                 // Prevent multiple definitions if this 
#define _HOBO_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "textDX.h"
#include "sword.h"

namespace hoboNS
{
	const int   WIDTH = 64;                 // image width (each frame)
	const int   HEIGHT = 64;                // image height
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI; // radians per second
	const float SPEED = 20;                // 100 pixels per second
	enum DIRECTION { NONE, LEFT, RIGHT };     // rotation direction
	const int   TEXTURE_COLS = 0;           // texture has 8 columns
}

// inherits from Entity class
class Hobo : public Entity
{
protected:
	bool collision;                 
    bool target;  
	int directionX;
	int directionY;
	float speed;

public:
	// constructor
	Hobo();

	Sword sword;
	DIRECTION dir;

	void update(float frameTime);
	void attack();
	void damage(WEAPON);
	void death();
	void heal();

	void ai(float frameTime, Entity &target);
	void vectorTrack(Entity &target);

	float getHealth() { return health; }
};
#endif