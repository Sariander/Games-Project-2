#ifndef _BOTTLE_H 
#define _BOTTLE_H 
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bottleNS
{
	const int   WIDTH = 20;
	const int   HEIGHT = 20;
	const float FIRE_DELAY = 1.5f;

	const int   TEXTURE_COLS = 3;  
	const int   START_THROW_FRAME = 0;
	const int   END_THROW_FRAME = 3;
	const int	START_FIRE_FRAME = 4;
	const int	END_FIRE_FRAME = 5;

	const float ANIMATION_DELAY = 0.1f;
	const int	SPEED = 100;

	const float SWING_TIME = .2f;
	const float SWING_RANGE = 30;

}

class Bottle : public Entity 
{
private:

public:
	// constructor
	Bottle();
	float throwTimer;

	void update(Entity *hero, float frameTime);
	void toss(Entity *hero, D3DXVECTOR2 vec);
};
#endif