#include "stdafx.h"
#include "Hero.h"
#include "Globals.h"
#include "../../GameManager/ResourceManager.h"

void Hero::Init()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(5);
	auto shader = ResourceManager::GetInstance()->GetShader(1);
	auto anim = std::make_shared<Animation>(model, texture, shader, 1.0f, 1);
	anim->Set2DPosition(Vector2(Globals::screenWidth / 2 - 100, Globals::screenHeight / 2));
	anim->SetSize(100, 100);
	m_anim = anim;
}

void Hero::Draw()
{
	m_anim->Draw();
}

void Hero::Update(GLfloat deltaTime)
{
	m_anim->Update(deltaTime);
}