#include "cybovine.h"
#include "ship.h"
using namespace shipNS;

Cybovine::Cybovine()
{
	bossTheta = 180;
	rotRate = 0.25;
	phaseTimer = 0;
	colorTimer = 0.0f;
	filter = SETCOLOR_ARGB(0,0,0,0);
	turret1 =  Turret(0.0f);
	turret2 = Turret(90.0f);
	turret3 = Turret(180.0f);
	turret4 = Turret(270.0f);
	turret5 = Turret(45.0f);
	turret6 = Turret(135.0f);
	turret7 = Turret(225.0f);
	turret8 = Turret(315.0f);
	gameStart = true;
	for(int i = 0; i < 8; i++)
	{
		alive[i] = true;
	}

	//eyeblast = Turret();
	//eyeblast.setVisible(false);
	//eyeblast.setActive(false);
}

void Cybovine::draw(float frameTime)
{
	if(colorTimer > 0)
		colorTimer -= frameTime;
	//draw all turrets
	if(colorTimer <= 0.0f) {
		filter = SETCOLOR_ARGB(0, 0, 0, 0);
		base.draw(spriteData, filter);
	} else {
		filter = SETCOLOR_ARGB(255, 255, 30, 30);
		base.draw(spriteData, filter);
	}
	
	turret1.draw(frameTime);
	turret2.draw(frameTime);
	turret3.draw(frameTime);
	turret4.draw(frameTime);
	turret5.draw(frameTime);
	turret6.draw(frameTime);
	turret7.draw(frameTime);
	turret8.draw(frameTime);

	if(colorTimer <= 0.0f) {
		filter = SETCOLOR_ARGB(0, 0, 0, 0);
		Image::draw(spriteData, filter);
	} else {
		filter = SETCOLOR_ARGB(255, 255, 30, 30);
		Image::draw(spriteData, filter);
	}

	//eyeblast.draw(frameTime);

}

bool Cybovine::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Cybovine::update(float frameTime)
{
	if(gameStart)
	{
		audio->playCue(MOO);
		gameStart = false;
	}
	bossTheta += rotRate;
		if(bossTheta > 360)
			bossTheta = 0;
	phaseTimer++;
	if(rotRate <= 0)
	{
		if(turret1.getHealth() <= 0 && alive[0])
		{
			rotRate -= .125;
			alive[0] = false;
		}
		if(turret2.getHealth() <= 0 && alive[1])
		{
			rotRate -= .125;
			alive[1] = false;
		}
		if(turret3.getHealth() <= 0 && alive[2])
		{
			rotRate -= .125;
			alive[2] = false;
		}
		if(turret4.getHealth() <= 0 && alive[3])
		{
			rotRate -= .125;
			alive[3] = false;
		}
		if(turret5.getHealth() <= 0 && alive[4])
		{
			rotRate -= .125;
			alive[4] = false;
		}
		if(turret6.getHealth() <= 0 && alive[5])
		{
			rotRate -= .125;
			alive[5] = false;
		}
		if(turret7.getHealth() <= 0 && alive[6])
		{
			rotRate -= .125;
			alive[6] = false;
		}
		if(turret8.getHealth() <= 0 && alive[7])
		{
			rotRate -= .125;
			alive[7] = false;
		}
	}
	else
	{
		if(turret1.getHealth() <= 0 && alive[0])
		{
			rotRate += .125;
			alive[0] = false;
		}
		if(turret2.getHealth() <= 0 && alive[1])
		{
			rotRate += .125;
			alive[1] = false;
		}
		if(turret3.getHealth() <= 0 && alive[2])
		{
			rotRate += .125;
			alive[2] = false;
		}
		if(turret4.getHealth() <= 0 && alive[3])
		{
			rotRate += .125;
			alive[3] = false;
		}
		if(turret5.getHealth() <= 0 && alive[4])
		{
			rotRate += .125;
			alive[4] = false;
		}
		if(turret6.getHealth() <= 0 && alive[5])
		{
			rotRate += .125;
			alive[5] = false;
		}
		if(turret7.getHealth() <= 0 && alive[6])
		{
			rotRate += .125;
			alive[6] = false;
		}
		if(turret8.getHealth() <= 0 && alive[7])
		{
			rotRate += .125;
			alive[7] = false;
		}
	}
	if(phaseTimer > rand()%500+500)
	{
		rotRate *= -1;
		phaseTimer = 0;
	}
	setDegrees(bossTheta);
	base.setDegrees(getDegrees());
	turret1.setDegrees(getDegrees());
	turret2.setDegrees(getDegrees());
	turret3.setDegrees(getDegrees());
	turret4.setDegrees(getDegrees());
	turret5.setDegrees(getDegrees());
	turret6.setDegrees(getDegrees());
	turret7.setDegrees(getDegrees());
	turret8.setDegrees(getDegrees());
	
	turret1.update(frameTime);
	turret2.update(frameTime);
	turret3.update(frameTime);
	turret4.update(frameTime);
	turret5.update(frameTime);
	turret6.update(frameTime);
	turret7.update(frameTime);
	turret8.update(frameTime);
	fire();
}

void Cybovine::fire()
{
	//attack patterns
	turret1.fire();
	turret2.fire();
	turret3.fire();
	turret4.fire();
	turret5.fire();
	turret6.fire();
	turret7.fire();
	turret8.fire();

	if(true) {//need eyeblast fire bool
		eyeblast.setActive(true);
		eyeblast.setVisible(true);
		//need timer for eyeblast
	} else {
		eyeblast.setActive(false);
		eyeblast.setVisible(false);

	}


}

void Cybovine::damage(WEAPON weapon)
{
    switch(weapon)
    {
    case TORPEDO:
        //audio->playCue(TORPEDO_HIT);
		colorTimer = cybovineNS::COLOR_WAIT;
        health -= shipNS::TORPEDO_DAMAGE;
        break;
    }
    if (health <= 0)
        explode();
}

void Cybovine::explode()
{
	audio->playCue(MOO2);
    active = false;
	visible = false;
	base.setVisible(false);
    health = 0;
	turret1.setActive(false);
	turret2.setActive(false);
	turret3.setActive(false);
	turret4.setActive(false);
	turret5.setActive(false);
	turret6.setActive(false);
	turret7.setActive(false);
	turret8.setActive(false);
	turret1.setVisible(false);
	turret2.setVisible(false);
	turret3.setVisible(false);
	turret4.setVisible(false);
	turret5.setVisible(false);
	turret6.setVisible(false);
	turret7.setVisible(false);
	turret8.setVisible(false);
	eyeblast.setVisible(false);
}