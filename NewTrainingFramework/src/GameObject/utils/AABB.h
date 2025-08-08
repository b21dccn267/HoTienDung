#pragma once
#include "../Utilities/utilities.h"
#include <memory>

class AABB
{
	Vector2 min;
	Vector2 max;

	void UpdateBox();
	bool IsCollide(std::shared_ptr<AABB> self, std::shared_ptr<AABB> target);
};

