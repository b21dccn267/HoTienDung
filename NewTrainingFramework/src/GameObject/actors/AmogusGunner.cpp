#include "AmogusGunner.h"
#include "GameManager/ResourceManager.h"
#include "GameObject/utils/CreatureController.h"
#include <vector>


AmogusGunner::AmogusGunner() : Creature()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(33);
	m_isDie = false;
}

void AmogusGunner::Idle()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(33);

	m_anim->m_numFramesPerRow = 9;
	m_anim->m_numFramesPerColumn = 7;
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::LookRight()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(33);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_anim->SetCustomFrames(std::vector<int>{32, 33, 34, 35});
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
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(33);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_anim->SetCustomFrames(std::vector<int>{40, 41, 42, 43});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void AmogusGunner::ShootAnimLeft()
{
	AmogusGunner::ShootAnimRight();
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void AmogusGunner::Die()
{
	Creature::Die();
}

void AmogusGunner::TestAllSprites()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(33);

	m_anim->m_numFramesPerRow = 8;
	m_anim->m_numFramesPerColumn = 6;
	m_anim->SetCustomFrames(std::vector<int>{0,  1,  2,  3,  4,  5,  6,  7, 
											 8,  9, 10, 11, 12, 13, 14, 15, 
											16, 17, 18, 19, 20, 21, 22, 23, 
											24, 25, 26, 27, 28, 29, 30, 31, 
											32, 33, 34, 35, 36, 37, 38, 38,
											});
	m_anim->m_frameTime = 0.1f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}
