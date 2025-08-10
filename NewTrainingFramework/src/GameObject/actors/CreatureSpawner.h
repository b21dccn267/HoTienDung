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
	std::vector<std::unique_ptr<Creature>> m_creaturePool;
	std::vector<std::unique_ptr<Creature>> m_creatureActive;
	bool m_isActive; // or isDie
	CreatureSpawner();
	void SpawnCreature();
	void DespawnCreature();
};

