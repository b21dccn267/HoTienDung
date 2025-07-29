#pragma once
#include "../../core/Animation.h"
#include "../../core/Object.h"
#include "../../actors/Projectile.h"
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

