#pragma once
#include "GameObject/actors/Projectile.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/Object.h"
#include <memory>
#include <stack>
#include <vector>

class Hero;
class Gun : public std::enable_shared_from_this<Gun>
{
public:
	std::weak_ptr<Hero> owner;

	std::shared_ptr<Object> m_self;
	std::vector<std::unique_ptr<Projectile>> m_projectilePool;
	std::stack<int> m_freeProjectiles;
	std::vector<std::unique_ptr<Projectile>> m_projectileUsed;
	bool m_isActive;
	// add active bullet here

	Gun(std::weak_ptr<Hero> owner);
	std::unique_ptr<Projectile> AcquireProjectile();
	void ReleaseProjectile(std::unique_ptr<Projectile> proj);
	void Fire();

	void Draw();
	void Update(GLfloat deltaTime);
};