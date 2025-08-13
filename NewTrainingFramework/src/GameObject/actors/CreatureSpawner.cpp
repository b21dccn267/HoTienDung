#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include "AmogusGunner.h"
#include "GameObject/utils/AABB.h"
#include "GameState/GSGame.h"
#include "GameObject/utils/CreatureController.h"
#include <memory>
#include <cstdlib> 
#include <ctime>


CreatureSpawner::CreatureSpawner()
{
	m_isOnCooldown = false;
	m_cooldownTimer = 0.0f;
	m_cooldown = 2.0f;

	//m_owner = owner;
	// may need to add more pools for different creatures, or use poly (is viable)
	m_creaturePool.reserve(100);
	//m_creatureActive.reserve(50);

	for (int i = 0; i < m_creaturePool.capacity(); i++) {
		if (i < m_creaturePool.capacity() / 2) {
			auto temp = std::make_unique<Skeleton>();
			m_creaturePool.emplace_back(std::move(temp));
		}
		else {
			auto temp = std::make_unique<AmogusGunner>();
			m_creaturePool.emplace_back(std::move(temp));
		}
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
	// roll
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	int number;

	// clean empty slots
	m_creaturePool.erase(
		std::remove_if(
			m_creaturePool.begin(),
			m_creaturePool.end(),
			[](const std::unique_ptr<Creature>& ptr) { return ptr == nullptr; }
		),
		m_creaturePool.end()
	);

	number = std::rand();
	//auto creature = std::move(m_creaturePool[0]);
	auto creature = std::move(m_creaturePool[number % m_creaturePool.size()]);
	creature->Init();
	creature->LookDown();
	//creature->m_anim->Set2DPosition(pos);



	switch (number % 7) {
	case 0:
		creature->m_anim->Set2DPosition(Vector2(10.0f, -10.0f));
		break;
	case 1:
		creature->m_anim->Set2DPosition(Vector2(300.0f, -10.0f));
		break;
	case 2:
		creature->m_anim->Set2DPosition(Vector2(-100.0f, 500.0f));
		break;
	case 3:
		creature->m_anim->Set2DPosition(Vector2(150.0f, 750.0f));
		break;
	case 4:
		creature->m_anim->Set2DPosition(Vector2(700.0f, 800.0f));
		break;
	case 5:
		creature->m_anim->Set2DPosition(Vector2(420.0f, 800.0f));
		break;
	case 6:
		creature->m_anim->Set2DPosition(Vector2(720.0f, -10.0f));
		break;
	}

	printf("spawned\n");
	//m_creaturePool.emplace_back(creature);
	m_creatureActive.emplace_back(std::move(creature));
}

// type should be Creature, current arg should be std::unique_ptr<Skeleton> creature
void CreatureSpawner::DespawnCreature(std::unique_ptr<Creature> creature)
{
	//m_creatureActive.clear();
	m_creaturePool.emplace_back(std::move(creature));
	printf("killed creature\n");
}

void CreatureSpawner::Update(float deltaTime, std::shared_ptr<Hero> hero)
{
	//auto owner = m_owner.lock();

	for (auto& x : m_creatureActive) {
		if (x->health == 0) {
			DespawnCreature(std::move(x));
		}
	}

	m_creatureActive.erase(
		std::remove_if(
			m_creatureActive.begin(),
			m_creatureActive.end(),
			[](const std::unique_ptr<Creature>& ptr) { return ptr == nullptr; }
		),
		m_creatureActive.end()
	);

	for (auto& x : m_creatureActive) {
		if (AABB::IsCollideRR(x->m_hitbox, hero->m_hitbox)) {
			printf("isCollideWithHero\n");
			hero->m_health--;
			x->health = 0;
		}
		for (auto& projectile : hero->m_gun->m_projectileUsed) {
			if (AABB::IsCollideRR(x->m_hitbox, projectile->m_hitbox)) {
				printf("isCollideWithProjectile\n");
				x->health = 0;
				break;
			}
		}
		
		
		x->Move(deltaTime, Vector2(hero->m_anim->m_position.x, hero->m_anim->m_position.y));
		x->Update2DPosition();
		x->Update(deltaTime);
	}

	if (m_isOnCooldown == true) {
		m_cooldownTimer += deltaTime;
		if (m_cooldownTimer > m_cooldown) {
			m_isOnCooldown = false;
			m_cooldownTimer = 0.0f;
		}
	}
}