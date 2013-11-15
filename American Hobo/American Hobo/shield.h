
#define WIN32_LEAN_AND_MEAN
#ifndef SHIELD_H
#define SHIELD_H

#include "item.h"

class Shield : public Item
{
private:
	int dmgReduction;
public:
	Shield(int reduc);
};

#endif