#pragma once
#include "Creature.h"
#include <memory>



class Skeleton;
class Hero;
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
	//std::shared_ptr<GSGame> m_owner;

	std::vector<std::unique_ptr<Skeleton>> m_creaturePool;
	std::vector<std::unique_ptr<Skeleton>> m_creatureActive;
	bool m_isActive; // or isDie
	
	CreatureSpawner();
	void Init();
	void SpawnCreature();
	void DespawnCreature(std::unique_ptr<Skeleton> creature);
	void Update(float deltaTime, std::shared_ptr<Hero> hero);
};

