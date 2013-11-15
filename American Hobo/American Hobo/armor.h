
#define WIN32_LEAN_AND_MEAN
#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

class Armor : public Item
{
private:
	int protection;
public:
	Armor(int prot);
};

#endif