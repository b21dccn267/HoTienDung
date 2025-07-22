#pragma once
#include "GameStateBase.h"
#include <vector>
#include <memory>
#include <stack>


// this class manages game states
class GameStateMachine
{
public:
	GameStateMachine(const GameStateMachine& instance) = delete;
	static GameStateMachine* instance;
	static GameStateMachine* GetInstance()
	{
		if (!instance) {
			instance = new GameStateMachine();
		}
		return instance;
	}

	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

	std::stack<GameStateBase*> m_stack;

	GameStateBase* m_pActiveState;
	GameStateBase* m_pNextState;

	
	void PushState(StateType state);
	void PopState();
	void PerformStateChange(StateType state);
private:
	GameStateMachine() {};
};

