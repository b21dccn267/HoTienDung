#pragma once
#include "Creature.h"
#include <memory>

enum class SpawnLocation
{
	SPAWN_UP,
	SPAWN_DOWN,
	SPAWN_LEFT,
	SPAWN_RIGHT
};

// use object pooling for this
class CreatureSpawner
{
public:
	std::vector<std::shared_ptr<Creature>> m_creatures;

	CreatureSpawner();
	void SpawnCreature();
};

