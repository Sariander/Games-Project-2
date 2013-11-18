
#define WIN32_LEAN_AND_MEAN
#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item
{
private:
	int damage;
	//int strScale;
public:
	Weapon(int dmg);
};

#endif