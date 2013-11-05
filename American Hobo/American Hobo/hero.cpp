#include "hero.h"

//=============================================================================
// default constructor
//=============================================================================
Hero::Hero() : Entity()
{

}

void Hero::update(float frameTime)
{
	if (!visible)
		return;

	if (input->isKeyDown(HERO_LEFT_KEY))
	{
		velocity.x = -heroNS::SPEED;
	}
	if (input->isKeyDown(HERO_RIGHT_KEY))
	{
		velocity.x = heroNS::SPEED;
	}
	if (input->isKeyDown(HERO_UP_KEY))
	{
		velocity.y = -heroNS::SPEED;
	}
	if (input->isKeyDown(HERO_DOWN_KEY))
	{
		velocity.y = heroNS::SPEED;
	}

	if (spriteData.x < 0)
	{
		setX(0);
	}
	if (spriteData.x > GAME_WIDTH - heroNS::WIDTH)
	{
		setX(GAME_WIDTH - heroNS::WIDTH);
	}
	if (spriteData.y < 0)
	{
		setY(0);
	}
	if (spriteData.y > GAME_HEIGHT - heroNS::HEIGHT)
	{
		setY(GAME_HEIGHT - heroNS::HEIGHT);
	}
	
	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;	
	velocity = D3DXVECTOR2(0, 0);
}

void Hero::attack()
{

}

void Hero::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case SWORD:
		
		break;
	}
	if (health <= 0)
		death();
}

void Hero::death()
{
	active = false;
	visible = false;
	health = 0;
}

void Hero::heal()
{
	active = true;
	visible = true;
	health = FULL_HEALTH;
}