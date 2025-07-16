#pragma once


class GameStateBase
{
public:
	int m_stateId = -1;

	GameStateBase() {};
	virtual void Pause() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
	//virtual GameStateBase CreateState() = 0;
	virtual void CreateState() = 0;
	virtual void Update() = 0;
	virtual void HandleKeyEvent() = 0;
	virtual void HandleMouseEvent() = 0;
	virtual void Cleanup() = 0;
	virtual ~GameStateBase() = 0;
};

