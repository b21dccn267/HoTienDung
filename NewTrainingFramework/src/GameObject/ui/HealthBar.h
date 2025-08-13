#pragma once
#include <memory>

class Object;
class Vector2;

// this class is an ui element to be put in game states
class HealthBar
{
public:
	int health;
	std::shared_ptr<Object> m_healthBarBackground;
	std::shared_ptr<Object> m_healthBarHealth;

	// get Hero pos to put on top
	void Layout(Vector2 pos);
};

