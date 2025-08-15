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
	int m_health;
	int m_currHealth;
	std::shared_ptr<Object> m_healthBarFrame;
	std::shared_ptr<Object> m_healthBarFill;

	float m_barPosX;
	float m_barPosY;

	HealthBar(float barPosX, float barPosY);
	void Draw();
	void UpdateHealth(int heroHealth);
};
