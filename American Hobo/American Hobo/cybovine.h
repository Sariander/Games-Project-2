#ifndef _CYBOVINE_H                 // Prevent multiple definitions if this 
#define _CYBOVINE_H                 // file is included in more than one place

#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "torpedo.h"
#include "constants.h"
#include "turret.h"

namespace cybovineNS
{
	const int NUM_SHOTS = 60;
	const float EYE_DAMAGE = 50;
	const float COLOR_WAIT = .10f;
}

class Cybovine : public Entity
{
public:
	Cybovine();
    virtual void draw(float frameTime);
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
    void update(float frameTime);
	void fire();

	void damage(WEAPON);

	void explode();

	Turret turret1;
	Turret turret2;
	Turret turret3;
	Turret turret4;
	Turret turret5;
	Turret turret6;
	Turret turret7;
	Turret turret8;
	
	Turret eyeblast;

	Image base;
	float rotRate;
private:
	float bossTheta;
	float phaseTimer;
	float colorTimer;
	COLOR_ARGB filter;
	bool gameStart;
	bool alive[8];
};


#endif