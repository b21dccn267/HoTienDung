#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include <memory>

CreatureSpawner::CreatureSpawner()
{
	m_creatures.reserve(50);
}

void CreatureSpawner::SpawnCreature(Vector2 pos)
{
	auto creature = std::make_shared<Skeleton>();
	creature->Init();
	creature->LookDown();
	creature->m_anim->Set2DPosition(pos);

	m_creatures.emplace_back(creature);
}
