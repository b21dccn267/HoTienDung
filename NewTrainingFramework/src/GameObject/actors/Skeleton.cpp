#include "Skeleton.h"
#include "../../GameManager/ResourceManager.h"
#include <vector>

Skeleton::Skeleton() : Creature()
{
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);
}

void Skeleton::Idle()
{
	Creature::Idle();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::Jump()
{
	Creature::Jump();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23, 24, 25, 26, 27});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::LookUp()
{
	Creature::LookUp();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{12, 13, 14, 15});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::LookDown() // same as idle, fix this
{
	Creature::LookDown();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::LookTopRight()
{
	Creature::LookTopRight();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::LookTopLeft()
{
	Creature::LookTopLeft();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Skeleton::LookRight()
{
	Creature::LookRight();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::LookLeft()
{
	Creature::LookLeft();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Skeleton::LookBottomRight()
{
	Creature::LookBottomRight();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	//m_anim->SetRotation(Vector3(0, 180 * (3.14 / 180), 0));
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}

void Skeleton::LookBottomLeft()
{
	Creature::LookBottomLeft();
	m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(12);

	//m_anim->m_numFramesPerRow = 9;
	//m_anim->m_numFramesPerColumn = 7;
	//m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Skeleton::Die()
{
	Creature::Die();
	//m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(7);

	//m_anim->m_numFramesPerRow = 3;
	//m_anim->m_numFramesPerColumn = 2;
	//m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3, 4, 5});
	//m_anim->m_frameTime = 0.12f;
	//m_anim->SetRotation(Vector3(0, 0, 0));
}