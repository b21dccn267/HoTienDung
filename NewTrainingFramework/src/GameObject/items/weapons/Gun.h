#pragma once
#include "../../core/Animation.h"
#include <memory>

// exists inside Hero as an item
class Gun
{
public:
	std::shared_ptr<Animation> m_anim;

	Gun();
	void Draw();
	void Update(GLfloat deltaTime);
	void Update2DPosition();
};

