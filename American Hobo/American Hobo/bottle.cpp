#include "bottle.h"

//=============================================================================
// default constructor
//=============================================================================
Bottle::Bottle() : Entity()
{
	active = false;                                 // torpedo starts inactive
	spriteData.width = bottleNS::WIDTH;     // size of 1 image
	spriteData.height = bottleNS::HEIGHT;
	spriteData.rect.bottom = bottleNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bottleNS::WIDTH;
	cols = bottleNS::TEXTURE_COLS;
	frameDelay = bottleNS::ANIMATION_DELAY;
	startFrame = bottleNS::START_THROW_FRAME;       // first frame of ship animation
	endFrame = bottleNS::END_THROW_FRAME;         // last frame of ship animation
	currentFrame = startFrame;
	visible = false; 
	throwTimer = 0;
	flameTimer = 0;
	attackVector = D3DXVECTOR2(0.0,0.0);
	radVector = D3DXVECTOR2(0.0,0.0);
	posVector = D3DXVECTOR2(0.0,0.0);
}

//=============================================================================
// update
// typically called once per frame
//=============================================================================
void Bottle::update(Entity *holder, float frameTime)
{
	if(!visible) {
		/*velocity.x = holder->getVelocity().x;
		velocity.y = holder->getVelocity().y;*/

		spriteData.x += velocity.x * frameTime;
		spriteData.y += velocity.y * frameTime;

		velocity = D3DXVECTOR2(0, 0);
		return;
	}
	
	

	//if(attackVector == D3DXVECTOR2(0.0, 0.0) && flameTimer == 0) {
	//	D3DXVECTOR2 radiusVec;
	//	velocity = normalize(attackVector)*bottleNS::AIR_SPEED;
	//}

	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
	

	radVector = getPosition() - posVector;

	//handled in void explode()
	/*if(radius(radVector) < bottleNS::AIR_RADIUS) {
		flameTimer = bottleNS::FLAME_TIME;
		velocity = D3DXVECTOR2(0.0,0.0);
	}*/

	
	if((flameTimer -= frameTime) <= 0 && attackVector == D3DXVECTOR2(0.0, 0.0)) {
		visible = false;
		active = false;
		flameTimer = 0;
	}

	Entity::update(frameTime);
}

//=============================================================================
// toss
// 
//=============================================================================
void Bottle::toss(Entity *target)
{
	setFrames(bottleNS::START_THROW_FRAME,bottleNS::END_THROW_FRAME);
	setCurrentFrame(bottleNS::START_THROW_FRAME);

	
	posVector = target->getPosition();
	attackVector = target->getPosition() - D3DXVECTOR2(spriteData.x,spriteData.y);//get direction to fly;
	radVector = attackVector;
	velocity = velocity = normalize(attackVector)*bottleNS::AIR_SPEED;
	visible = true;
	active = true;
}

void Bottle::explode()
{
	flameTimer = bottleNS::FLAME_TIME;
	velocity = D3DXVECTOR2(0.0,0.0);


}

float Bottle::radius(D3DXVECTOR2 vec) {
	return sqrtf(vec.x*vec.x + vec.y*vec.y);

}

D3DXVECTOR2 Bottle::normalize(D3DXVECTOR2 vec) {
	return vec/radius(vec);
}

bool Bottle::isActive()
{
	return active;
}