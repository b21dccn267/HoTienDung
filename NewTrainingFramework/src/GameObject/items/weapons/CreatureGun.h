#pragma once
#include "GameObject/actors/CrProjectile.h"
#include <memory>
#include <vector>

class AmogusGunner;
class Hero;
class Vector2;

class CreatureGun
{
public:
	std::vector<std::unique_ptr<CrProjectile>> m_projectilePool;
	std::vector<std::unique_ptr<CrProjectile>> m_projectileUsed;
	bool m_isOnCooldown;
	float m_cooldownTimer;
	float m_cooldown;

	CreatureGun();
	void Init();
	void SpawnProjectile(Vector2 startPos, Vector2 endPos);
	void DespawnProjectile(std::unique_ptr<CrProjectile> projectile);
	void Draw();
	void Update(float deltaTime);
};