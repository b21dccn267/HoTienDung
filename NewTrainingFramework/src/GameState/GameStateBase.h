#pragma once
#include "../Utilities/utilities.h"
#include <memory>

enum class StateType
{
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY
};

class GameStateBase
{
public:
	StateType m_type;

	GameStateBase(StateType type);
	static GameStateBase* CreateState(StateType type);

	virtual void Init() = 0;
	virtual void Pause() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void HandleKeyEvent(bool bIsPressed) = 0;
	virtual void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) = 0;
	virtual void Cleanup() = 0;
	virtual ~GameStateBase() = 0;
};

