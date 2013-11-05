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

	if (health > 0)
	{

	}
}

void Hero::attack()
{

}

void Hero::damage(WEAPON weapon)
{
	switch (weapon)
	{

	}
}

void Hero::death()
{

}

void Hero::heal()
{

}