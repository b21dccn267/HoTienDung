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

	m_projectilePool.reserve(50);
	for (int i = 0; i < m_projectilePool.capacity(); i++) {
		auto temp = std::make_unique<Projectile>();
		//temp->m_id = i;
		// should create a new projectile class here
		temp->m_anim->m_pTexture = ResourceManager::GetInstance()->GetTexture(36);
		temp->m_anim->m_numFramesPerRow = 8;
		temp->m_anim->m_numFramesPerColumn = 6;
		temp->m_anim->SetCustomFrames(std::vector<int>{36, 37, 38, 39});
		temp->m_anim->m_frameTime = 0.12f;


		m_projectilePool.emplace_back(std::move(temp));
	}
}

void CreatureGun::SpawnProjectile(Vector2 startPos, Vector2 endPos)
{
	m_projectilePool.erase(
		std::remove_if(
			m_projectilePool.begin(),
			m_projectilePool.end(),
			[](const std::unique_ptr<Projectile>& ptr) { return ptr == nullptr; }
		),
		m_projectilePool.end()
	);

	auto projectile = std::move(m_projectilePool[0]);
	projectile->SetProjectile(Vector3(startPos.x, startPos.y, 0)
							, Vector3(endPos.x, endPos.y, 0));

	m_projectileUsed.emplace_back(std::move(projectile));
	printf("spawned amogus projectile\n");
}

void CreatureGun::DespawnProjectile(std::unique_ptr<Projectile> projectile)
{
	m_projectilePool.emplace_back(std::move(projectile));
	printf("killed amogus projectile\n");
}

void CreatureGun::Update(float deltaTime, std::shared_ptr<Hero> hero)
{
	// check condition for projectile removal
	for (auto& x : m_projectileUsed)
		if (x && (x->m_position.x > Globals::screenWidth || x->m_position.x < 0))
			DespawnProjectile(std::move(x));

	m_projectileUsed.erase(
		std::remove_if(
			m_projectileUsed.begin(),
			m_projectileUsed.end(),
			[](const std::unique_ptr<Projectile>& ptr) { return ptr == nullptr; }
		),
		m_projectileUsed.end()
	);

	for (auto& x : m_projectileUsed) {
		if (x) {
			x->Update(deltaTime);
		}
	}
}