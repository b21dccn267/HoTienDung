#include "CreatureSpawner.h"
#include "Creature.h"
#include "Skeleton.h"
#include "AmogusGunner.h"
#include "GameObject/utils/AABB.h"
#include "GameObject/utils/CreatureController.h"
#include "GameObject/actors/hero/Hero.h"
#include <memory>
#include <cstdlib> 
#include <ctime>
#include "GameObject/actors/hero/CrHero.h"
#include "GameManager/InputManager.h"

CreatureSpawner::CreatureSpawner()
{
	m_isOnCooldown = false;
	m_cooldownTimer = 0.0f;
	m_cooldown = 2.0f;

	m_creaturePool.reserve(50);


	for (int i = 0; i < m_creaturePool.capacity(); i++) {
		if (i < m_creaturePool.capacity() / 2)
		//if(false)
		{
			auto temp = std::make_unique<Skeleton>();
			temp->m_hitbox->UpdateBox(Vector2(0, 0), Vector2(0, 0));
			m_creaturePool.emplace_back(std::move(temp));
		}
		else {
			auto temp = std::make_unique<AmogusGunner>();
			temp->Init();
			temp->m_hitbox->UpdateBox(Vector2(0, 0), Vector2(0, 0));
			temp->LookRight();
			m_creaturePool.emplace_back(std::move(temp));
		}
	}
}
	
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
	auto creature = std::move(m_creaturePool[number % m_creaturePool.size()]);
	creature->m_health = 10;
	creature->Idle();



	switch (number % 7) {
	case 0:
		creature->m_anim->Set2DPosition(Vector2(-10.0f, 150.0f));
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
		creature->m_anim->Set2DPosition(Vector2(1000.0f, 600.0f));
		break;
	case 5:
		creature->m_anim->Set2DPosition(Vector2(420.0f, 800.0f));
		break;
	case 6:
		creature->m_anim->Set2DPosition(Vector2(960.0f, 150.0f));
		break;
	}

	printf("spawned creature %d\n", creature->m_creatureType);
	m_creatureActive.emplace_back(std::move(creature));
}

void CreatureSpawner::DespawnCreature(std::unique_ptr<Creature> creature)
{
	m_creaturePool.emplace_back(std::move(creature));
	printf("killed creature\n");
}

void CreatureSpawner::Update(float deltaTime, std::shared_ptr<Hero> hero, std::shared_ptr<CrHero> hero2, bool isGladiatorModeOn)
{
	// check conditions for removal
	for (auto& x : m_creatureActive) {
		if (x->m_health == 0 && x->m_anim->m_frameCount == 5) {
			DespawnCreature(std::move(x));
		}
	}
	// remove empty slots
	m_creatureActive.erase(
		std::remove_if(
			m_creatureActive.begin(),
			m_creatureActive.end(),
			[](const std::unique_ptr<Creature>& ptr) { return ptr == nullptr; }
		),
		m_creatureActive.end()
	);

	// pvp events only check
	// fix: has to have a way to turn pvp mode off after a hit
	if (isGladiatorModeOn) {
		// if hero 2 hits hero1
		if (AABB::IsCollideRR(hero->m_hitbox, hero2->m_sword->m_hitbox)) {
			hero->m_health -= hero2->m_attack;
			InputManager::GetInstance()->m_isInGladiatorMode = false;
		}
		// if hero1 hits hero2
		for (auto& projectile : hero->m_gun->m_projectileUsed) {
			if (AABB::IsCollideRR(hero2->m_hitbox, projectile->m_hitbox)) {
				hero2->m_health -= hero->m_attack;
				InputManager::GetInstance()->m_isInGladiatorMode = false;
				break;
			}
		}
	}

	// check all active creature events
	for (auto& x : m_creatureActive) {
		if (x->m_health > 0) {
			// if collide with hero
			if (AABB::IsCollideRR(x->m_hitbox, hero->m_hitbox)) {
				printf("isCollideWithHero\n");
				hero->m_health--;
				x->m_health = 0;
				x->Die();

			}
			// if collide with hero2
			if (AABB::IsCollideRR(x->m_hitbox, hero2->m_hitbox)) {
				printf("isCollideWithHero2\n");
				hero2->m_health--;
				x->m_health = 0;
				x->Die();
			}
			// if collide with hero projectile
			for (auto& projectile : hero->m_gun->m_projectileUsed) {
				if (AABB::IsCollideRR(x->m_hitbox, projectile->m_hitbox)) {
					printf("isCollideWithProjectile\n");
					x->m_health = 0;
					x->Die();
					break;
				}
			}
			// if collide with hero2 projectile
			if (AABB::IsCollideRR(x->m_hitbox, hero2->m_sword->m_hitbox)) {
				printf("isCollideWithSword\n");
				x->m_health = 0;
				x->Die();
			}


			// there should be a creature projectile check here
		}
		
		
		// creature updates
		x->Move(deltaTime, Vector2(hero->m_anim->m_position.x, hero->m_anim->m_position.y));
		if (x->m_health > 0) {
			x->Update2DPosition();
		}
		x->Update(deltaTime);
	}

	// spawn cooldown
	if (m_isOnCooldown == true) {
		m_cooldownTimer += deltaTime;
		if (m_cooldownTimer > m_cooldown) {
			m_isOnCooldown = false;
			m_cooldownTimer = 0.0f;
		}
	}
}