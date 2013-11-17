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

	if (input->isKeyDown(HERO_LEFT_KEY))
	{
		velocity.x = -hoboNS::SPEED;
	}
	if (input->isKeyDown(HERO_RIGHT_KEY))
	{
		velocity.x = hoboNS::SPEED;
	}
	if (input->isKeyDown(HERO_UP_KEY))
	{
		velocity.y = -hoboNS::SPEED;
	}
	if (input->isKeyDown(HERO_DOWN_KEY))
	{
		velocity.y = hoboNS::SPEED;
	}

	if (spriteData.x < 0)
	{
		setX(0);
	}
	if (spriteData.x > GAME_WIDTH - hoboNS::WIDTH)
	{
		setX(GAME_WIDTH - hoboNS::WIDTH);
	}
	if (spriteData.y < 0)
	{
		setY(0);
	}
	if (spriteData.y > GAME_HEIGHT - hoboNS::HEIGHT)
	{
		setY(GAME_HEIGHT - hoboNS::HEIGHT);
	}

	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
	velocity = D3DXVECTOR2(0, 0);
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