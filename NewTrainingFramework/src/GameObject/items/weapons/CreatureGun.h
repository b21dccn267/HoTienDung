#pragma once
#include "GameObject/actors/Projectile.h"
#include <memory>
#include <vector>

class AmogusGunner;
//class Projectile;
class Hero;
class Vector2;

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
	void SpawnProjectile(Vector2 startPos, Vector2 endPos);
	void DespawnProjectile(std::unique_ptr<Projectile> projectile);
	void Update(float deltaTime, std::shared_ptr<Hero> hero);
};