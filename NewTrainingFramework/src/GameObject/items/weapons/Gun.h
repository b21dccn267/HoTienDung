#pragma once
#include "GameObject/core/Animation.h"
#include "GameObject/core/Object.h"
#include "GameObject/actors/Projectile.h"
#include "GameObject/actors/hero/Hero.h"
#include <memory>
#include <vector>


class Gun
{
public:
	std::weak_ptr<Hero> owner;

	//std::shared_ptr<Animation> m_anim;
	std::shared_ptr<Object> m_self;
	std::vector<std::unique_ptr<Projectile>> m_projectilePool;
	bool m_isActive;
	// add active bullet here

	Gun(std::weak_ptr<Hero> owner);
	void Acquire();
	void Fire();
	//void Draw();
	void Update(GLfloat deltaTime);	
	//void Update2DPosition();
};