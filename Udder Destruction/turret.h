#ifndef _TURRET_H                 // Prevent multiple definitions if this 
#define _TURRET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "milkShot.h"
#include "constants.h"

namespace turretNS {

	const int NUM_SHOTS = 60;
	const int COLLISION_RADIUS = 20;
	const float MILK_DAMAGE = 10;
	const float COLOR_WAIT = .10f;

	const float WIDTH = 200;
	const float HEIGHT = 200;
}


class Turret : public Entity {
public:
	Turret();
	Turret(float rotOffset);
	Turret(int rotation);

	float rotOffset;

	void fire();
	void update(float frameTime);
	void draw(float frameTime);

	void damage(WEAPON);

	void explode();

	MilkShot shotBuffer[turretNS::NUM_SHOTS];

private:
	float fireTimer;
	float fireWait;
	float colorTimer;
	COLOR_ARGB filter;
};

#endif