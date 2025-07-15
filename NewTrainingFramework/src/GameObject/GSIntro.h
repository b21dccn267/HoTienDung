#pragma once
#include "GameStateBase.h"


// this class should load a 2d asset
// by having a Object class member
class GSIntro : public GameStateBase
{
public:
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void CreateState() override;

	~GSIntro() override;
};

