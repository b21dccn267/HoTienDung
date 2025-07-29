#pragma once
#include "../core/Animation.h"
#include <memory>

class Hero
{
public:
	std::shared_ptr<Animation> m_anim;

	Hero();
	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
};

