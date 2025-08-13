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
	std::vector<std::unique_ptr<Creature>> m_creaturePool;
	std::vector<std::unique_ptr<Creature>> m_creatureActive;
	bool m_isOnCooldown;
	float m_cooldownTimer;
	float m_cooldown;
	
	CreatureSpawner();
	void Init();
	void SpawnCreature();
	void DespawnCreature(std::unique_ptr<Creature> creature);
	void Update(float deltaTime, std::shared_ptr<Hero> hero);
};

