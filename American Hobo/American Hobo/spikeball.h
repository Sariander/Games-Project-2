#ifndef _SPIKEBALL_H 
#define _SPIKEBALL_H 
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace spikeballNS {
	const int   WIDTH = 40;
	const int   HEIGHT = 40;
	const int	OFFSET = 24;

	const float FIRE_DELAY = 1.5f;

	const int   TEXTURE_COLS = 0;
	const float ANIMATION_DELAY = 0.1f;
}


class Spikeball : public Entity 
{
private:

public:
	// constructor
	Spikeball();
	//void update(Entity *hero, float frameTime);

};
#endif