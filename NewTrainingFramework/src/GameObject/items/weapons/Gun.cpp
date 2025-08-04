#include "Gun.h"
#include "GameManager/ResourceManager.h"
#include <memory>

Gun::Gun(std::weak_ptr<Hero> owner)
{
	this->owner = owner;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(6);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_self = std::make_shared<Object>(model, texture, shader);

	m_isActive = false;

	m_projectilePool.reserve(50);
	for (int i = 0; i < m_projectilePool.size(); i++) {
		auto temp = std::make_unique<Projectile>();
		temp->m_isActive = false;
		m_projectilePool.emplace_back(std::move(temp));
	}
}

// have this function grab a bullet here
void Gun::Fire()
{
	if (m_isActive == true) {
		printf("gun is firing\n");
		return;
	}
	m_isActive = true;


}

void Gun::Update(GLfloat deltaTime)
{
	//m_projectile->Update(deltaTime);
}