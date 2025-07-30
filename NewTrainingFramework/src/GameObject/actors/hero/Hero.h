#pragma once
#include "../../core/Animation.h"
#include "../../items/weapons/Gun.h"
#include "Belongings.h"
#include <memory>

class Hero
{
public:
	std::shared_ptr<Animation> m_anim;
	std::shared_ptr<Gun> m_gun;

	std::shared_ptr<Belongings> m_belongings;

	Hero();
	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
	void FireGun();
};

