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

	m_projectilePool.reserve(10);
	for (int i = 0; i < m_projectilePool.capacity(); i++) {
		auto temp = std::make_unique<CrProjectile>();
		m_projectilePool.emplace_back(std::move(temp));
	}
}

std::unique_ptr<CrProjectile> CreatureGun::SpawnProjectile(Vector2 startPos, Vector2 endPos)
{
	m_projectilePool.erase(
		std::remove_if(
			m_projectilePool.begin(),
			m_projectilePool.end(),
			[](const std::unique_ptr<CrProjectile>& ptr) { return ptr == nullptr; }
		),
		m_projectilePool.end()
	);

	for (auto& x : m_projectilePool) {
		// set projectile to hero pos
		x->SetProjectile(Vector3(startPos.x, startPos.y, 0)
					   , Vector3(endPos.x, endPos.y, 0));
		x->ProjLoop();
		return std::move(x);
	}
	printf("ran out of creature projectiles\n");
	return nullptr;
}

void CreatureGun::DespawnProjectile(std::unique_ptr<CrProjectile> projectile)
{
	m_projectilePool.emplace_back(std::move(projectile));
}

void CreatureGun::Draw()
{
	for (auto& x : m_projectileUsed) {
		x->m_anim->CustomDraw();
	}
}

void CreatureGun::Update(float deltaTime)
{
	// check condition for projectile removal
	for (auto& x : m_projectileUsed) {
		if (x && (x->m_anim->m_position.x > Globals::screenWidth || x->m_anim->m_position.x < 0)) {
			DespawnProjectile(std::move(x));
		}
	}

	m_projectileUsed.erase(
		std::remove_if(
			m_projectileUsed.begin(),
			m_projectileUsed.end(),
			[](const std::unique_ptr<CrProjectile>& ptr) { return ptr == nullptr; }
		),
		m_projectileUsed.end()
	);

	for (auto& x : m_projectileUsed) {
		if (x) {
			x->Update(deltaTime);
		}
	}
}
void CreatureGun::CrFire(Vector2 startPos, Vector2 endPos)
{
	m_projectileUsed.emplace_back(SpawnProjectile(startPos, endPos));
}