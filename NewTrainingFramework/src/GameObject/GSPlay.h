#pragma once
#include "GameStateBase.h"

class GSPlay : public GameStateBase
{
public:
	void Pause() override;
	void Exit() override;
	void Resume() override;
	//GameStateBase CreateState() override;
};

