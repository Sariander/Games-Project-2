#include "hero.h"

//=============================================================================
// default constructor
//=============================================================================
Hero::Hero() : Entity()
{
	dir = RIGHT;
}

void Hero::update(float frameTime)
{
	if (!visible)
		return;

	if (input->isKeyDown(HERO_LEFT_KEY) && !input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_DOWN_KEY))//Single Direction Movement
	{
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);

		velocity.x = -heroNS::SPEED;
		dir = LEFT;
	}
	if (input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_DOWN_KEY))
	{
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);

		velocity.x = heroNS::SPEED;
		dir = RIGHT;
	}
	if (input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_LEFT_KEY))
	{
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);
		velocity.y = -heroNS::SPEED;
		dir = UP;
	}
	if (input->isKeyDown(HERO_DOWN_KEY) && !input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_LEFT_KEY))
	{
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);
		velocity.y = heroNS::SPEED;
		dir = DOWN;
	}

	if (input->isKeyDown(HERO_LEFT_KEY) && input->isKeyDown(HERO_UP_KEY)) {
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);

		velocity.x = -.707*heroNS::SPEED;
		velocity.y = -.707*heroNS::SPEED;
		dir = LEFT;
	}

	if (input->isKeyDown(HERO_LEFT_KEY) && input->isKeyDown(HERO_DOWN_KEY)) {
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);

		velocity.x = -.707*heroNS::SPEED;
		velocity.y = .707*heroNS::SPEED;
		dir = LEFT;
	}

	if (input->isKeyDown(HERO_RIGHT_KEY) && input->isKeyDown(HERO_UP_KEY)) {
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);

		velocity.x = .707*heroNS::SPEED;
		velocity.y = -.707*heroNS::SPEED;
		dir = RIGHT;
	}

	if (input->isKeyDown(HERO_RIGHT_KEY) && input->isKeyDown(HERO_DOWN_KEY)) {
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);

		velocity.x = .707*heroNS::SPEED;
		velocity.y = .707*heroNS::SPEED;
		dir = RIGHT;
	}


	if (input->isKeyDown(HERO_ATTACK_KEY))
	{
		attack();
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

	Entity::update(frameTime);
	sword.update(this, frameTime);
}

void Hero::attack()
{
	sword.swing(this,dir);
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