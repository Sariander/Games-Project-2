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
	
	//const float AIR_TIME = .2f;
	const float AIR_RADIUS = 300.0f;
	const float AIR_RANGE = 30.0f;
	const float FLAME_TIME = 0.8f;

	const float AIR_SPEED = 10.0f;

}

class Bottle : public Entity 
{
private:
	D3DXVECTOR2 attackVector;
	D3DXVECTOR2 posVector;
	D3DXVECTOR2 radVector;

	float radius(D3DXVECTOR2 vec);
	D3DXVECTOR2 normalize(D3DXVECTOR2 vec);

public:
	// constructor
	Bottle();

	//float throwTimer;
	float flameTimer;

	void update(Entity *hero, float frameTime);
	void toss(Entity *hero);


};
#endif