#pragma once
#include "GameStateBase.h"
#include "StateType.h"
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

	std::vector<std::unique_ptr<GameStateBase>> m_stack;

	GameStateBase* m_pActiveState;
	GameStateBase* m_pNextState;
	std::stack m_StateStack; // must use explicit lifo 

	
	void PushState(StateType state);
	//void PushState();
	void PopState();
	void PerformStateChange(std::unique_ptr<GameStateBase> state);
private:
	GameStateMachine();
};

