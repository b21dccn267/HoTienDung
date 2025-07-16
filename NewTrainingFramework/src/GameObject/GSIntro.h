#pragma once
#include "GameStateBase.h"


// this class should load a 2d asset
// by having an Object class member
class GSIntro : public GameStateBase
{
public:


	GSIntro(int id = 1);
	void Pause() override;
	void Exit() override;
	void Resume() override;
	//GameStateBase CreateState() override;
	virtual void CreateState() override;
	virtual void Update() override;
	virtual void HandleKeyEvent() override;
	virtual void HandleMouseEvent() override;
	virtual void Cleanup() override;

	~GSIntro() override;
};

