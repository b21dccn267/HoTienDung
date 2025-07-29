#pragma once
#include "../core/Animation.h"
#include <memory>

class Creature
{
public:
	std::shared_ptr<Animation> m_anim;

	Creature();
	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
};

