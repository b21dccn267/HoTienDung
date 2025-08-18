#include "CreatureGun.h"
#include "Globals.h"
#include "GameObject/actors/Projectile.h"
#include "GameObject/actors/hero/Hero.h"
#include <GameManager/ResourceManager.h>


CreatureGun::CreatureGun()
{

}

void CreatureGun::Init()
{
	m_isOnCooldown = false;
	m_cooldownTimer = 0.0f;
	m_cooldown = 5.0f;

	//m_projectilePool.reserve(3);
	//for (int i = 0; i < m_projectilePool.capacity(); i++) {
	//	auto temp = std::make_unique<CrProjectile>();

	//	m_projectilePool.emplace_back(std::move(temp));
	//}

	// no obj pool version
	m_projectileUsed.reserve(3);
	for (int i = 0; i < m_projectileUsed.capacity(); i++) {
		auto temp = std::make_unique<CrProjectile>();
		temp->ProjLoop();
		m_projectileUsed.emplace_back(std::move(temp));
	}
	m_projectileCount = 3;
}

void CreatureGun::SpawnProjectile(Vector2 startPos, Vector2 endPos)
{
	//m_projectilePool.erase(
	//	std::remove_if(
	//		m_projectilePool.begin(),
	//		m_projectilePool.end(),
	//		[](const std::unique_ptr<CrProjectile>& ptr) { return ptr == nullptr; }
	//	),
	//	m_projectilePool.end()
	//);

	//auto& projectile = std::move(m_projectilePool[0]);
	//projectile->SetProjectile(Vector3(startPos.x, startPos.y, 0)
	//						, Vector3(endPos.x, endPos.y, 0));

	//m_projectileUsed.emplace_back(std::move(projectile));
	
	if (m_projectileCount > 0) {
		if (m_projectileUsed[m_projectileCount - 1]->m_isActive == false) {
			m_projectileUsed[m_projectileCount - 1]->m_isActive = true;
			m_projectileUsed[m_projectileCount - 1]->SetProjectile(Vector3(startPos.x, startPos.y, 0), Vector3(endPos.x, endPos.y, 0));
		}
	}
}

void CreatureGun::DespawnProjectile(std::unique_ptr<CrProjectile> projectile)
{
	//m_projectilePool.emplace_back(std::move(projectile));
}

void CreatureGun::Draw()
{
	for (auto& x : m_projectileUsed) {
		if(x->m_isActive)
			x->m_anim->CustomDraw();
	}
}

void CreatureGun::Update(float deltaTime)
{
	// check condition for projectile removal
	for (auto& x : m_projectileUsed)
		if (x && (x->m_position.x > Globals::screenWidth || x->m_position.x < 0))
			//DespawnProjectile(std::move(x));
			x->m_isActive = false;

	//m_projectileUsed.erase(
	//	std::remove_if(
	//		m_projectileUsed.begin(),
	//		m_projectileUsed.end(),
	//		[](const std::unique_ptr<CrProjectile>& ptr) { return ptr == nullptr; }
	//	),
	//	m_projectileUsed.end()
	//);

	for (auto& x : m_projectileUsed) {
		if (x->m_isActive) {
			x->Update(deltaTime);
		}
	}
}