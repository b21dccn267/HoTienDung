#pragma once
#include "Creature.h"


class Skeleton : public Creature
{
public:
	Skeleton();
	
	// need override from creature, as creature spawner container is of type creature
	void Idle();
	void Jump(); // unused, exists as a demo; if used, there should be jump anims for all directions
	void LookUp();
	void LookDown();
	void LookTopRight();
	void LookTopLeft();
	void LookRight();
	void LookLeft();
	void LookBottomRight();
	void LookBottomLeft();
	void Die();
};

