#include "GameManager/ResourceManager.h"
#include "GameObject/actors/hero/Hero.h"
#include "Gun.h"
#include <Globals.h>
#include <memory>


Gun::Gun(std::weak_ptr<Hero> owner)
{
	this->m_owner = owner;

	auto model = ResourceManager::GetInstance()->GetModel(0);
	auto texture = ResourceManager::GetInstance()->GetTexture(6);
	auto shader = ResourceManager::GetInstance()->GetShader(0);
	m_self = std::make_shared<Object>(model, texture, shader);

	m_isActive = false;

	m_projectilePool.reserve(50);
	for (int i = 0; i < m_projectilePool.capacity(); i++) {
		auto temp = std::make_unique<Projectile>(weak_from_this());
		temp->m_id = i;
		temp->m_isActive = false;
		m_projectilePool.emplace_back(std::move(temp));
	}
}

std::unique_ptr<Projectile> Gun::AcquireProjectile()
{
	for (auto& x : m_projectilePool) {
		return std::move(x);
	}
	printf("ran out of projectiles\n");
	return nullptr;
}

void Gun::ReleaseProjectile(std::unique_ptr<Projectile> proj)
{
	proj->SetProjectile();
	m_projectilePool[proj->m_id] = std::move(proj);
}

// have this function grab a bullet here
void Gun::Fire()
{
	m_projectileUsed.emplace_back(AcquireProjectile());
}

void Gun::Draw()
{
	for (auto& x : m_projectileUsed)
		//if(x)
		x->Draw();
}

void Gun::Update(GLfloat deltaTime)
{
	for (auto& x : m_projectileUsed)
		if (x && x->m_position.x > Globals::screenWidth / 2 + 600.0f)
			ReleaseProjectile(std::move(x));

	m_projectileUsed.erase(
		std::remove_if(
			m_projectileUsed.begin(),
			m_projectileUsed.end(),
			[](const std::unique_ptr<Projectile>& ptr) { return ptr == nullptr; }
		),
		m_projectileUsed.end()
	);
	
	//m_projectilePool.erase(
	//	std::remove_if(
	//		m_projectilePool.begin(),
	//		m_projectilePool.end(),
	//		[](const std::unique_ptr<Projectile>& ptr) { return ptr == nullptr; }
	//	),
	//	m_projectilePool.end()
	//);

	for (auto& x : m_projectileUsed)
		if (x) {
			auto owner = m_owner.lock();
			x->Update(deltaTime, owner->m_anim->m_position.x, owner->m_anim->m_position.y);
		}
}