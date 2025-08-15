#pragma once
#include <memory>

class Object;

class Timer
{
public:
	// class to store timer
	// class to display timer
	bool m_isActive;
	int m_time; //in seconds
	float m_updateCount;
	std::shared_ptr<Object> m_displayText; // check type of this, might need to be Texture instead of TextRenderer

	Timer();
	// timer functions
	void StartTimer(int startTime);
	void PauseTimer();
	void ResumeTimer();
	void UpdateTimer(float deltaTime); // update text texture
};

