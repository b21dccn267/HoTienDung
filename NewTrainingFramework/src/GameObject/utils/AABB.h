#pragma once
#include "../Utilities/utilities.h"
#include <memory>

class AABB
{
public:
	// box collision
	Vector2 min; // bottom left
	Vector2 max; // top right

	// sphere collision 
	Vector2 center;
	float radius;

	void UpdateBox(Vector2 pos, Vector2 size);
	// rectangle check
	bool IsCollideRR(std::shared_ptr<AABB> self, std::shared_ptr<AABB> target);
	// circle vs rectangle check
	bool IsCollideCR(std::shared_ptr<AABB> self, std::shared_ptr<AABB> target);
};

