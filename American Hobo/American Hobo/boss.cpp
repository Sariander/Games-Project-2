#include "boss.h"

Boss::Boss() : Hobo()
{
	dir = RIGHT;
	spriteData.width = bossNS::WIDTH;
	spriteData.height = bossNS::HEIGHT;
	spriteData.x = bossNS::X;                   // location on screen
	spriteData.y = bossNS::Y;
	spriteData.rect.bottom = bossNS::HEIGHT / 2;    // rectangle to select parts of an image
	spriteData.rect.right = bossNS::WIDTH;

	velocity = D3DXVECTOR2(0, 0);
	startFrame = 0;              // first frame of ship animation
	endFrame = 0;              // last frame of ship animation
	currentFrame = startFrame;
	radius = hoboNS::WIDTH / 2.0;                 // collision radius
	collision = false;
	collisionType = entityNS::BOX;// entityNS::CIRCLE;
	target = false;
	edge.bottom = -bossNS::HEIGHT / 2;
	spriteData.scale = 1;
	active = true;
	speed = bossNS::SPEED;
	health = bossNS::HEALTH_MAX;
	theta = 0.0f;
}

void Boss::update(float frameTime) {
	if (!visible)
		return;

	if (hitTimer != 0) {
		hitTimer -= frameTime;

		velocity.x = -10.0*hitVector.x;
		velocity.y = -10.0*hitVector.y;

		if (hitTimer < 0) {
			hitTimer = 0;
			hitVector = D3DXVECTOR2(0, 0);
		}
	}

	Image::setX(getPositionX());
	Image::setY(getPositionY());
	Entity::update(frameTime);

	//Rotational update

	theta = theta + 30*frameTime;

	if(theta > 360)
		theta = theta - 360.0f;

	float conRad = PI/180;
	float newX; 
	float newY;


	for (int i = 0; i < bossNS::NUM_BALLS; ++i)
	{
		newX = 80*cos(theta*conRad - PI/2) + getCenterX();
		newY = 80*sin(theta*conRad - PI/2) + getCenterY();
		//sword[i].setCenterX(newX);
		//sword[i].setCenterY(newY);
		spikeball[i].setCenterX(newX);
		spikeball[i].setCenterY(newY);
		theta = theta + 90.0f;
		if(theta > 360)
			theta = theta - 360.0f;
	}


	for (int i = 0; i < bossNS::NUM_BALLS; ++i)
	{
		//sword[i].update(this, frameTime);
		spikeball[i].update(frameTime);
	}
}

void Boss::spawn(GameStates level)
{
	hitTimer = 0.0;
	setVelocity(VECTOR2(0, 0));
	health = bossNS::HEALTH_MAX;
	setDeltaV(VECTOR2(0, 0));
	setPosition(VECTOR2(GAME_WIDTH / 2, 20));
	setX(getPositionX());
	setY(getPositionY());

	setActive(true);
	setVisible(true);
	for (int i = 0; i < bossNS::NUM_BALLS; ++i)
	{
		//sword[i].setActive(true);
		//sword[i].setVisible(true);
		spikeball[i].setActive(true);
		spikeball[i].setVisible(true);
	}

}