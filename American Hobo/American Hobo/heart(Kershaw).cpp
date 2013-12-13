#include "heart.h"

Heart::Heart()
{
	spriteData.width = heartNS::WIDTH;           
    spriteData.height = heartNS::HEIGHT;

	startFrame = 0;              // first frame of ship animation
    endFrame = 0;              // last frame of ship animation
	currentFrame = 0;
}

void Heart::change_frame(int frame)
{
	currentFrame = frame;
}