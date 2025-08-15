#include "AmogusGunner.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/CreatureController.h"
#include "GameObject/items/weapons/CreatureGun.h"
#include <vector>
#include <memory>


AmogusGunner::AmogusGunner() : Creature()
{
	m_creatureType = 1;

	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(36);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_isDie = false;

	//m_crGun = std::make_shared<CreatureGun>();
	//m_crGun->Init();
}

void AmogusGunner::TestAllSprites()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(36);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_anim->SetCustomFrames(std::vector<int>{
		0, 1, 2, 3, 4, 5, 6, 7,
		8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 38,
	});
	m_anim->m_frameTime = 0.1f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::LookRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(36);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_anim->SetCustomFrames(std::vector<int>{24, 25, 26, 27});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::LookLeft()
{
	AmogusGunner::LookRight();
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}



void AmogusGunner::ShootAnimRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(36);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_anim->SetCustomFrames(std::vector<int>{32, 33, 34, 35});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::ShootAnimLeft()
{
	AmogusGunner::ShootAnimRight();
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void AmogusGunner::Idle()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(37);
	m_anim->SetSize(50, 50);
	m_anim->m_numFramesPerRow = 4;
	m_anim->m_numFramesPerColumn = 1;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
	//AmogusGunner::TestAllSprites();
}

void AmogusGunner::Die()
{
	Creature::Die();
}

// for gunner this function also decides firing behavior
void AmogusGunner::Move(float deltaTime, Vector2 heroPos)
{
	if (std::abs(heroPos.x - this->m_anim->m_position.x) > 100.0f) {
		Creature::Move(deltaTime, heroPos);
	}
	else {
		//printf("gunner stopped\n");
		// fire gun
		// this means the gunner moves until a certain distance, stops and then open fire
		// gunner should not move later/should only move when too far
		//m_crGun->SpawnProjectile(Vector2(m_anim->m_position.x, m_anim->m_position.y), heroPos);
	}
}