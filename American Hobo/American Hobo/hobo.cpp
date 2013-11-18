#include "hobo.h"

//=============================================================================
// default constructor
//=============================================================================
Hobo::Hobo() : Entity()
{
	dir = RIGHT;
}

void Hobo::update(float frameTime)
{
	if (!visible)
		return;

	VECTOR2 foo = -velocity*frameTime*speed;

	incPosition(foo);
	Image::setX(getPositionX());
	Image::setY(getPositionY());
    Entity::update(frameTime);

}

void Hobo::attack()
{
	sword.swing(this, dir);
}

void Hobo::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case SWORD:

		break;
	}
	if (health <= 0)
		death();
}

void Hobo::death()
{
	active = false;
	visible = false;
	health = 0;
}

void Hobo::heal()
{
	active = true;
	visible = true;
	health = FULL_HEALTH;
}

void Hobo::ai(float frameTime, Entity &target)
{
	vectorTrack(target);
}


void Hobo::vectorTrack(Entity &target)
{
	VECTOR2 vel = getCenterPoint() - target.getCenterPoint();
	VECTOR2* temp = D3DXVec2Normalize(&vel, &vel);
	setVelocity(vel);
}