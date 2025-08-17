#pragma once
#include "GameObject/core/Object.h"
#include <memory>

// new weapon for hero
// spawns an object with hitbox representing sword hit 
// is literally the whip, only shit either left or right
class Sword
{
	std::shared_ptr<Object> m_self;
	bool m_isActive;

	Sword();
	void UseSword();
	void Draw();
	void Update(float deltaTime);
};

