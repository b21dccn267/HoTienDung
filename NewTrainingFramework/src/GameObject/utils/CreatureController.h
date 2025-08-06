#pragma once
#include "GameObject/actors/Creature.h"
#include <memory>


// this class manages enemy ai
// current goal: get hero coord, then move closer to it
// no need for A* pathfinding algo as theres no map layout (just x y manip to be closer to hero)
class CreatureController
{
public:
	std::weak_ptr<Creature> m_owner;

	CreatureController(std::weak_ptr<Creature> owner);
	void Move();
};

