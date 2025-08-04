#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include <memory>

CreatureSpawner::CreatureSpawner()
{
	m_creatures.reserve(50);
}

void CreatureSpawner::SpawnCreature()
{
	//auto creature = std::make_shared<Creature>();
	auto creature = std::make_shared<Skeleton>();
	creature->LookDown();
	m_creatures.emplace_back(creature);
}
