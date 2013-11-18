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
}