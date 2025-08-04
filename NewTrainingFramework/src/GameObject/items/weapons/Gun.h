#pragma once
#include "GameObject/core/Animation.h"
#include "GameObject/core/Object.h"
#include "../../actors/Projectile.h"
#include "../../actors/hero/Hero.h"
#include <memory>

// exists inside Hero as an item
// no anim
// should extend Object
class Gun
{
public:


	//std::shared_ptr<Animation> m_anim;
	std::shared_ptr<Object> m_self;
	std::shared_ptr<Projectile> m_projectile;
	bool m_isActive;

	Gun();
	void Fire();
	//void Draw();
	void Update(GLfloat deltaTime);	
	//void Update2DPosition();
};