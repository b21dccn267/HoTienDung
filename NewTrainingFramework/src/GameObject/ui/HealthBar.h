#pragma once
#include <memory>

class Object;
class Vector2;
class Hero;

// this class is an ui element to be put in game states
class HealthBar
{
public:
	// create cap value here (min, max);
	// impl it in code logic
	int health;
	std::shared_ptr<Object> m_healthBarBackground;
	std::shared_ptr<Object> m_healthBarHealth;


	// get Hero pos to put on top
	void Layout(Vector2 pos);
	// 
	void UpdateHealth(std::shared_ptr<Hero> hero); // alternatively add in param instead of object
	
};

