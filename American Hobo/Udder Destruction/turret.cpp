
#include "turret.h"
#include "ship.h"
using namespace shipNS;

Turret::Turret() {
	fireWait = .15f;
	fireTimer = 0.0f;
	rotOffset = 0.0f;
	filter = SETCOLOR_ARGB(0,0,0,0);

	colorTimer = 0.0f;
	radius = turretNS::COLLISION_RADIUS;
}

Turret::Turret(float rotOffset) : Entity() {
	fireWait = .25f;
	fireTimer = 0.0f;
	colorTimer = 0.0f;
	filter = SETCOLOR_ARGB(0,0,0,0);
	radius = turretNS::COLLISION_RADIUS;
}

Turret::Turret(int rotation) {
	fireTimer = 0.0f;
	rotOffset = 0.0f;
	colorTimer = 0.0f;
	filter = SETCOLOR_ARGB(0,0,0,0);
	setDegrees(rotation);
}

void Turret::fire() {
	if(health > 0 && visible)
	{
		if(fireTimer <= 0.0f) {
			for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
				if(shotBuffer[i].ready) {
					shotBuffer[i].fire(this, rotOffset);
					fireTimer = fireWait;
					break;
				}
			}
		}
	}
	return;
}

void Turret::update(float frameTime) {
	fireTimer -= frameTime;

	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		shotBuffer[i].update(frameTime);
	}

	setCenterX((float)cos(getRadians() + (rotOffset - 90 )*PI/180)*55 + GAME_WIDTH/2);
	setCenterY((float)sin(getRadians() + (rotOffset - 90)*PI/180)*55 + GAME_HEIGHT/2);


	Entity::update(frameTime);

	return;
}

void Turret::draw(float frameTime) {
	if(colorTimer > 0)
		colorTimer -= frameTime;

	for(int i = 0; i < turretNS::NUM_SHOTS; i++) {
		shotBuffer[i].draw();
	}
	if(colorTimer <= 0.0f) {
		filter = SETCOLOR_ARGB(0, 0, 0, 0);
		Image::draw(spriteData, filter);
	} else {
		filter = SETCOLOR_ARGB(255, 255, 30, 30);
		Image::draw(spriteData, filter);
	}
		
}

void Turret::damage(WEAPON weapon)
{
    switch(weapon)
    {
    case TORPEDO:
		colorTimer = turretNS::COLOR_WAIT;
        health -= shipNS::TORPEDO_DAMAGE;
        break;
    }
    if (health <= 0)
        explode();
}

void Turret::explode()
{
    active = false;
	visible = false;
    health = 0;
}