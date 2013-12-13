#include "brawler.h"

Brawler::Brawler() : Hobo()
{
	dir = RIGHT;
	spriteData.width = brawlerNS::WIDTH;           
    spriteData.height = brawlerNS::HEIGHT;
    spriteData.x = brawlerNS::X;                   // location on screen
    spriteData.y = brawlerNS::Y;
    spriteData.rect.bottom = brawlerNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = brawlerNS::WIDTH;
    
	velocity = D3DXVECTOR2(0,0);
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    radius = hoboNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType =entityNS::BOX;// entityNS::CIRCLE;
    target = false;
	edge.bottom = -brawlerNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
	speed = brawlerNS::SPEED;
	health = brawlerNS::HEALTH_MAX;
}

void Brawler::update(float frameTime) {
	if (!visible)
		return;

	if(hitTimer != 0) {
		hitTimer -= frameTime;
		
		velocity.x = -10.0*hitVector.x;
		velocity.y = -10.0*hitVector.y;

		if(hitTimer < 0) {
			hitTimer = 0;
			hitVector = D3DXVECTOR2(0,0);
		}
	}


	if(hitTimer == 0) {
		if(sword.swingTimer == 0 && dir == LEFT) { //Sets animations based on direction facing
			setFrames(hoboNS::LEFT_WALK_START, hoboNS::LEFT_WALK_END);
			//setCurrentFrame(hoboNS::LEFT_WALK_START);
		} else if(sword.swingTimer == 0 && dir == RIGHT) {
			setFrames(hoboNS::RIGHT_WALK_START, hoboNS::RIGHT_WALK_END);
			//setCurrentFrame(hoboNS::RIGHT_WALK_START);
		} else if(sword.swingTimer != 0 && dir == LEFT) {
			setFrames(hoboNS::LEFT_ATTACK_START, hoboNS::LEFT_ATTACK_END);
			//setCurrentFrame(hoboNS::LEFT_ATTACK_START);
		} else if(sword.swingTimer != 0 && dir == RIGHT) {
			setFrames(hoboNS::RIGHT_ATTACK_START, hoboNS::RIGHT_ATTACK_END);
			//setCurrentFrame(hoboNS::RIGHT_ATTACK_START);
		}
	}

	VECTOR2 foo = -velocity*frameTime*speed;
	
	if(sword.swingTimer == 0) //Can only move when not attacking
		incPosition(foo);


	if(getVelocity().x > 0)
		dir = LEFT;
	else
		dir = RIGHT;

	Image::setX(getPositionX());
	Image::setY(getPositionY());
    Entity::update(frameTime);
	sword.update(this, frameTime);



}

void Brawler::spawn(GameStates level)
{
	hitTimer = 0.0;
	setVelocity(VECTOR2(0,0));
	health = brawlerNS::HEALTH_MAX;
	setDeltaV(VECTOR2(0,0));
	int seed = rand()%4;
	switch(seed)
	{
	case 0:
		setPosition(VECTOR2(-10, GAME_HEIGHT/2));
		setX(getPositionX());
		setY(getPositionY());
		break;
	case 1:
		setPosition(VECTOR2(GAME_WIDTH/2,-10));
		setX(getPositionX());
		setY(getPositionY());
		break;
	case 2:
		setPosition(VECTOR2(GAME_WIDTH + 10, GAME_HEIGHT/2));
		setX(getPositionX());
		setY(getPositionY());
		break;
	case 3:
		setPosition(VECTOR2(GAME_WIDTH/2, GAME_HEIGHT + 10));
		setX(getPositionX());
		setY(getPositionY());
		break;
	}

	setActive(true);
	setVisible(true);

}