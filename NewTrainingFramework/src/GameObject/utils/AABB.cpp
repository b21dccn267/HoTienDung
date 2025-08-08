#include "AABB.h"

void AABB::UpdateBox()
{
	min.x;
}

bool AABB::IsCollide(std::shared_ptr<AABB> self, std::shared_ptr<AABB> target)
{
	return (self->min.x < target->max.x && self->max.x > target->min.x) 
		&& (self->min.y < target->max.y && self->max.y > target->min.y);
}
