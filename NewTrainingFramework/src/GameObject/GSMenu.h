#pragma once
#include "GameStateBase.h"

class GSMenu : public GameStateBase
{
public:
	void Pause() override;
	void Exit() override;
	void Resume() override;
	//GameStateBase CreateState() override;
};

