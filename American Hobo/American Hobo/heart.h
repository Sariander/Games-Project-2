#ifndef _HEART_H                 // Prevent multiple definitions if this 
#define _HEART_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{
	const int   WIDTH = 27;                 // image width (each frame)
	const int   HEIGHT = 26;                // image height
	const int   TEXTURE_COLS = 3;           
}

class Heart : public Entity
{

public:
	Heart();
	void change_frame(int frame);

};



#endif