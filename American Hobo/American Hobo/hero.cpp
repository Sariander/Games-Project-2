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

	if (input->isKeyDown(HERO_LEFT_KEY) && !input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_DOWN_KEY) && !sword.getVisible())//Single Direction Movement
	{
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);

		velocity.x = -heroNS::SPEED;
		dir = LEFT;
	}
	if (input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_DOWN_KEY) && !sword.getVisible())
	{
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);

		velocity.x = heroNS::SPEED;
		dir = RIGHT;
	}
	if (input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_LEFT_KEY) && !sword.getVisible())
	{
		setFrames(heroNS::START_UP, heroNS::END_UP);
		velocity.y = -heroNS::SPEED;
		dir = UP;
	}
	if (input->isKeyDown(HERO_DOWN_KEY) && !input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_LEFT_KEY) && !sword.getVisible())
	{
		setFrames(heroNS::START_DOWN, heroNS::END_DOWN);
		velocity.y = heroNS::SPEED;
		dir = DOWN;
	}

	if (input->isKeyDown(HERO_LEFT_KEY) && input->isKeyDown(HERO_UP_KEY) && !sword.getVisible()) {
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);

		velocity.x = -.707*heroNS::SPEED;
		velocity.y = -.707*heroNS::SPEED;
		dir = LEFT;
	}

	if (input->isKeyDown(HERO_LEFT_KEY) && input->isKeyDown(HERO_DOWN_KEY) && !sword.getVisible()) {
		setFrames(heroNS::START_LEFT, heroNS::END_LEFT);

		velocity.x = -.707*heroNS::SPEED;
		velocity.y = .707*heroNS::SPEED;
		dir = LEFT;
	}

	if (input->isKeyDown(HERO_RIGHT_KEY) && input->isKeyDown(HERO_UP_KEY) && !sword.getVisible()) {
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);

		velocity.x = .707*heroNS::SPEED;
		velocity.y = -.707*heroNS::SPEED;
		dir = RIGHT;
	}

	if (input->isKeyDown(HERO_RIGHT_KEY) && input->isKeyDown(HERO_DOWN_KEY) && !sword.getVisible()) {
		setFrames(heroNS::START_RIGHT, heroNS::END_RIGHT);

		velocity.x = .707*heroNS::SPEED;
		velocity.y = .707*heroNS::SPEED;
		dir = RIGHT;
	}

	if(sword.getVisible()) {
		if(dir == RIGHT || dir == UP) {
			setFrames(heroNS::STAND_RIGHT,heroNS::STAND_RIGHT);
			setCurrentFrame(heroNS::STAND_RIGHT);
		} else if(dir == LEFT || dir == DOWN) {
			setFrames(heroNS::STAND_LEFT,heroNS::STAND_LEFT);
			setCurrentFrame(heroNS::STAND_LEFT);
		}
	}
	
	if(!input->isKeyDown(HERO_RIGHT_KEY) && !input->isKeyDown(HERO_LEFT_KEY) && !input->isKeyDown(HERO_UP_KEY) && !input->isKeyDown(HERO_DOWN_KEY)) {
		if(dir == RIGHT) {
			setFrames(heroNS::STAND_RIGHT,heroNS::STAND_RIGHT);
			setCurrentFrame(heroNS::STAND_RIGHT);
		} 
		else if (dir == UP){
			setFrames(heroNS::STAND_UP, heroNS::STAND_UP);
			setCurrentFrame(heroNS::STAND_UP);
		}
		else if(dir == LEFT) {
			setFrames(heroNS::STAND_LEFT,heroNS::STAND_LEFT);
			setCurrentFrame(heroNS::STAND_LEFT);
		}
		else if (dir == DOWN) {
			setFrames(heroNS::STAND_DOWN, heroNS::STAND_DOWN);
			setCurrentFrame(heroNS::STAND_DOWN);
		}
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