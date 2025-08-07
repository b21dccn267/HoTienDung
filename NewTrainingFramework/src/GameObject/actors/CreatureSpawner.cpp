#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include <memory>
#include <cstdlib> 
#include <ctime>


CreatureSpawner::CreatureSpawner()
{
	m_creatures.reserve(50);
}

// this function rolls a random number, then spawn a creature at fixed locations on the map
// for testing, creatures spawnpoint are visible, but ideally should be just beyond the view area
// what spd does:
//		- computes a spawn budget (use this to manage waves)
//		- choose a random monster (go make 2 types of mobs)
//		
void CreatureSpawner::SpawnCreature()
{
	auto creature = std::make_shared<Skeleton>();
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
	m_creatures.emplace_back(creature);
}
