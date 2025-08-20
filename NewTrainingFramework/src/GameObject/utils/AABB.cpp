#include "AABB.h"

void AABB::UpdateBox(Vector2 pos, Vector2 size)
{
	min.x = pos.x - size.x / 2 / 3; min.y = pos.y + size.y / 2 / 3;
	max.x = pos.x + size.x / 2 / 3; max.y = pos.y - size.y / 2 / 3;

	center = pos;
}

bool AABB::IsCollideRR(std::shared_ptr<AABB> self, std::shared_ptr<AABB> target)
{
	return (self->min.x < target->max.x && self->max.x > target->min.x) 
		&& (self->min.y > target->max.y && self->max.y < target->min.y);
}

bool AABB::IsCollideCR(std::shared_ptr<AABB> self, std::shared_ptr<AABB> target)
{
	return true;
}
