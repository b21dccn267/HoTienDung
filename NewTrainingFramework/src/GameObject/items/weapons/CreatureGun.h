#pragma once
#include <memory>
#include <vector>

class AmogusGunner;
class Projectile;
class Hero;

class CreatureGun
{
public:
	std::shared_ptr<AmogusGunner> m_owner;
	std::vector<std::unique_ptr<Projectile>> m_projectilePool;
	std::vector<std::unique_ptr<Projectile>> m_projectileUsed;
	bool m_isOnCooldown;
	float m_cooldownTimer;
	float m_cooldown;

	CreatureGun();
	void Init();
	void SpawnProjectile(std::shared_ptr<Hero> hero);
	void DespawnProjectile(std::unique_ptr<Projectile> projectile);
	void Update(float deltaTime, std::shared_ptr<Hero> hero);
};

