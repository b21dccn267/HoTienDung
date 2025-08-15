#pragma once
#include "GameObject/core/TextRenderer.h"
#include <memory>


class Timer
{
public:
	// class to store timer
	// class to display timer
	int m_time; //in seconds
	std::shared_ptr<TextRenderer> m_displayText; // check type of this, might need to be Texture instead of TextRenderer

	void Init();
	// timer functions
	void StartTimer(int startTime);
	void PauseTimer();
	void ResumeTimer();
	void UpdateTimer(); // update text texture

};

