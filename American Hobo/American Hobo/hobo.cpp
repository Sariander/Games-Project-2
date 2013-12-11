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
    endFrame = 0;              // last frame of ship animation
    currentFrame = startFrame;
    radius = hoboNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType =entityNS::BOX;// entityNS::CIRCLE;
    target = false;
	edge.bottom = -hoboNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
	speed = hoboNS::SPEED;
	
	targetDist = GAME_HEIGHT/2;

	hitTimer = 0;
	hitVector = D3DXVECTOR2(0,0);

	health = hoboNS::HEALTH_MAX;
}

void Hobo::update(float frameTime)
{
	if (!visible)
		return;


	if(hitTimer != 0) {
		hitTimer -= frameTime;
		
		velocity.x = -30.0*hitVector.x;
		velocity.y = -30.0*hitVector.y;

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

void Hobo::draw(float frameTime)
{
	if (colorTimer > 0)
	{
		colorTimer -= frameTime;
	}
	if (colorTimer <= 0.0f) {
		filter = SETCOLOR_ARGB(0, 0, 0, 0);
		Image::draw(spriteData, filter);
	}
	else {
		filter = SETCOLOR_ARGB(255, 255, 30, 30);
		Image::draw(spriteData, filter);
	}
}


void Hobo::attack()
{
	sword.swing(this, dir);
}

bool Hobo::damage(WEAPON weapon, D3DXVECTOR2 vector)
{
	if(hitTimer == 0) {
		hitTimer = hoboNS::HIT_DURATION;
		hitVector = vector;
		colorTimer = hoboNS::COLOR_WAIT;
		switch (weapon)
		{
		case SWORD:
			health--;
			break;
		}
		if (health <= 0) {
			death();
			return true;
		}
	}
	return false;
}

void Hobo::death()
{
	active = false;
	visible = false;
	velocity.x = 0;
	velocity.y = 0;
	health = 0;
	audio->playCue(DEATH_SOUND);
}

void Hobo::heal()
{
	active = true;
	visible = true;
	health = FULL_HEALTH;
}

void Hobo::ai(float frameTime, Entity &target)
{
	if(active) {
		vectorTrack(target);
		if(targetDist < 30)
			attack();
	}
}


void Hobo::vectorTrack(Entity &target)
{
	float tempX = getCenterX() - target.getCenterX();
	if(tempX < 0)
		tempX = -tempX;
	float tempY = getCenterY() - target.getCenterY();
	if(tempY < 0)
		tempY = -tempY;

	targetDist = sqrtf(tempY*tempY + tempX*tempX);


	VECTOR2 vel = getCenterPoint() - target.getCenterPoint();
	VECTOR2* temp = D3DXVec2Normalize(&vel, &vel);
	setVelocity(vel);
}

void Hobo::spawn(GameStates level)
{
	hitTimer = 0.0;
	setVelocity(VECTOR2(0,0));
	health = hoboNS::HEALTH_MAX;
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
