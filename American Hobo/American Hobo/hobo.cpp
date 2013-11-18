#include "hobo.h"

//=============================================================================
// default constructor
//=============================================================================
Hobo::Hobo() : Entity()
{
	dir = RIGHT;
	spriteData.width = hoboNS::WIDTH;           
    spriteData.height = hoboNS::HEIGHT;
    spriteData.x = hoboNS::X;                   // location on screen
    spriteData.y = hoboNS::Y;
    spriteData.rect.bottom = hoboNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = hoboNS::WIDTH;
    
	velocity = D3DXVECTOR2(0,0);
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    radius = hoboNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType =entityNS::BOX;// entityNS::CIRCLE;
    target = false;
	edge.bottom = -hoboNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
	speed = 50;
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
	if(active)
		vectorTrack(target);
}


void Hobo::vectorTrack(Entity &target)
{
	VECTOR2 vel = getCenterPoint() - target.getCenterPoint();
	VECTOR2* temp = D3DXVec2Normalize(&vel, &vel);
	setVelocity(vel);
}