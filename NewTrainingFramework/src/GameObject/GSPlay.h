#pragma once
#include "GameStateBase.h"

class GSPlay : public GameStateBase
{
public:


	GSPlay(int id = 1);
	void Pause() override;
	void Exit() override;
	void Resume() override;
	//GameStateBase CreateState() override;
	virtual void CreateState() override;
	virtual void Update() override;
	virtual void HandleKeyEvent() override;
	virtual void HandleMouseEvent() override;
	virtual void Cleanup() override;

	~GSPlay() override;
};

