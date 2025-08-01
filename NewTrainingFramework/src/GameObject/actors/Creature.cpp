#include "Creature.h"
#include "../../Globals.h"
#include "../../GameManager/ResourceManager.h"

Creature::Creature()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(11);
	auto shader = ResourceManager::GetInstance()->GetShader(2);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23});
	m_anim = anim;
}

void Creature::Idle()
{
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::Jump()
{
	m_anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23, 24, 25, 26, 27});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::LookUp()
{
	m_anim->SetCustomFrames(std::vector<int>{12, 13, 14, 15});
	m_anim->m_frameTime = 0.12f;
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::LookDown() // same as idle, fix this
{
	m_anim->SetCustomFrames(std::vector<int>{0, 1, 2, 3});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::LookTopRight()
{
	m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::LookTopLeft()
{
	m_anim->SetCustomFrames(std::vector<int>{16, 17, 18, 19});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Creature::LookRight()
{
	m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::LookLeft()
{
	m_anim->SetCustomFrames(std::vector<int>{8, 9, 10, 11});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Creature::LookBottomRight()
{
	m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	m_anim->SetRotation(Vector3(0, 180 * (3.14 / 180), 0));
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 0, 0));
}

void Creature::LookBottomLeft()
{
	m_anim->SetCustomFrames(std::vector<int>{4, 5, 6, 7});
	m_anim->m_frameTime = 0.12f;
	m_anim->SetRotation(Vector3(0, 3.14, 0));
}

void Creature::Draw()
{
	m_anim->CustomDraw();
}

void Creature::Update(GLfloat deltaTime)
{
	m_anim->CustomUpdate(deltaTime);
}

void Creature::Update2DPosition()
{
	m_anim->Set2DPosition(Vector2(m_anim->m_position.x, m_anim->m_position.y));
}
