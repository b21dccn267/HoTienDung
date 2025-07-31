#include "stdafx.h"
#include "Creature.h"
#include "Globals.h"
#include "../../GameManager/ResourceManager.h"

Creature::Creature()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(20);
	auto shader = ResourceManager::GetInstance()->GetShader(1);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	anim->SetCustomFrames(std::vector<int>{20, 21, 22, 23});
	m_anim = anim;
}

void Creature::Draw()
{
	m_anim->Draw();
}

void Creature::Update(GLfloat deltaTime)
{
	m_anim->Update(deltaTime);
}

void Creature::Update2DPosition()
{
	m_anim->Set2DPosition(Vector2(m_anim->m_position.x, m_anim->m_position.y));
}
