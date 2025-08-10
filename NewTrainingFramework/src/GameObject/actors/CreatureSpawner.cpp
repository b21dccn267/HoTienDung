#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include <memory>
#include <cstdlib> 
#include <ctime>


CreatureSpawner::CreatureSpawner()
{
	// may need to add more pools for different creatures, or use poly (is viable)
	m_creaturePool.reserve(50);
	m_creatureActive.reserve(50);
	//fix cannot get base dtor due to no dtor inherit policy
	//for (int i = 0; i < m_creaturePool.capacity(); i++) {
	//	auto temp = std::make_unique<Skeleton>();
	//	temp->m_id = i;
	//	m_creaturePool.emplace_back(std::move(temp));
	//}
}

// this function rolls a random number, then spawn a creature at fixed locations on the map
// for testing, creatures spawnpoint are visible, but ideally should be just beyond the view area
// what spd does:
//		- computes a spawn budget (use this to manage waves)
//		- choose a random monster (go make 2 types of mobs)
//		
void CreatureSpawner::SpawnCreature()
{
	// clean empty slots
	//m_creaturePool.erase(
	//	std::remove_if(
	//		m_creaturePool.begin(),
	//		m_creaturePool.end(),
	//		[](const std::unique_ptr<Skeleton>& ptr) { return ptr == nullptr; }
	//	),
	//	m_creaturePool.end()
	//);

	auto creature = std::make_unique<Skeleton>();
	creature->Init();
	creature->LookDown();
	//creature->m_anim->Set2DPosition(pos);

	// roll for spawn location
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	int number = std::rand();

	switch (number % 4) {
	case 0:
		creature->m_anim->Set2DPosition(Vector2(500.0f, 100.0f));
		break;
	case 1:
		creature->m_anim->Set2DPosition(Vector2(500.0f, 600.0f));
		break;
	case 2:
		creature->m_anim->Set2DPosition(Vector2(100.0f, 500.0f));
		break;
	case 3:
		creature->m_anim->Set2DPosition(Vector2(500.0f, 100.0f));
		break;
	}

	printf("spawned\n");
	//m_creaturePool.emplace_back(creature);
	m_creatureActive.emplace_back(creature);
}

// type should be Creature, current arg should be std::unique_ptr<Skeleton> creature
void CreatureSpawner::DespawnCreature()
{
	//m_creatureActive.clear();
	printf("killed creature\n");
}
