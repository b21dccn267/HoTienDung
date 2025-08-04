#pragma once
#include "Creature.h"
#include <memory>

// use object pooling for this
class CreatureSpawner
{
public:
	std::vector<std::shared_ptr<Creature>> m_creatures;

	CreatureSpawner();
	void SpawnCreature();
};

