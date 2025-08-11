#pragma once
#include "Creature.h"
#include <memory>


class GSGame;
class Skeleton;

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
	std::weak_ptr<GSGame> m_owner;

	std::vector<std::unique_ptr<Skeleton>> m_creaturePool;
	std::vector<std::unique_ptr<Skeleton>> m_creatureActive;
	bool m_isActive; // or isDie

	CreatureSpawner(std::weak_ptr<GSGame> owner);
	void Init();
	void SpawnCreature();
	void DespawnCreature();
	void Update(float deltaTime);
};

