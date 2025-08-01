
#include "Gun.h"
#include "../../../GameManager/ResourceManager.h"

Gun::Gun()
{
	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(6);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_self = std::make_shared<Object>(model, texture, shader);

	m_isActive = false;
}

void Gun::Fire()
{
	if (m_isActive == true) {
		printf("gun is firing\n");
		return;
	}
	m_isActive = true;
	// spawns projectile
	m_projectile = std::make_shared<Projectile>();
}

void Gun::Update(GLfloat deltaTime)
{
	m_projectile->Update(deltaTime);
}