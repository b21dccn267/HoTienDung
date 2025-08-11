#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include "GameObject/utils/AABB.h"
#include "GameState/GSGame.h"
#include "GameObject/utils/CreatureController.h"
#include <memory>
#include <cstdlib> 
#include <ctime>


CreatureSpawner::CreatureSpawner(std::weak_ptr<GSGame> owner)
{
	m_owner = owner;
	// may need to add more pools for different creatures, or use poly (is viable)
	m_creaturePool.reserve(50);
	//m_creatureActive.reserve(50);

	for (int i = 0; i < m_creaturePool.capacity(); i++) {
		auto temp = std::make_unique<Skeleton>();
		//temp->SkeletonInit();
		temp->m_id = i;
		m_creaturePool.emplace_back(std::move(temp));
	}
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
	//		[](const std::unique_ptr<Creature>& ptr) { return ptr == nullptr; }
	//	),
	//	m_creaturePool.end()
	//);

	auto creature = std::make_unique<Skeleton>();
	// init complete, but m_control owner is empty (not the whole pointer
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
	m_creatureActive.emplace_back(std::move(creature));
}

// type should be Creature, current arg should be std::unique_ptr<Skeleton> creature
void CreatureSpawner::DespawnCreature()
{
	m_creatureActive.clear();
	printf("killed creature\n");
}

void CreatureSpawner::Update(float deltaTime)
{
	auto owner = m_owner.lock();

	for (auto& x : m_creatureActive) {
		if (AABB::IsCollideRR(x->m_hitbox, owner->m_hero->m_hitbox)) {
			printf("isCollideWithHero\n");
		}
		x->m_control->Move(deltaTime, Vector2(owner->m_hero->m_anim->m_position.x, owner->m_hero->m_anim->m_position.y));
		x->Update2DPosition();
	}
}