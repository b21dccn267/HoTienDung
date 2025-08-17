#pragma once
#include "GameObject/actors/Projectile.h"
#include "GameObject/core/Animation.h"
#include "GameObject/core/Object.h"
#include <memory>
#include <stack>
#include <vector>

class Hero;
class Gun 
{
public:
	//std::shared_ptr<Hero> m_owner;

	std::shared_ptr<Object> m_self;
	std::vector<std::unique_ptr<Projectile>> m_projectilePool;
	std::vector<std::unique_ptr<Projectile>> m_projectileUsed;
	//bool m_isActive;
	float m_fMouseX;
	float m_fMouseY;

	Gun();
	void Init();
	std::unique_ptr<Projectile> AcquireProjectile(std::shared_ptr<Hero> hero);
	void ReleaseProjectile(std::unique_ptr<Projectile> proj);
	void Fire	(std::shared_ptr<Hero> hero);

	void Draw();
	void Update(GLfloat deltaTime);
};