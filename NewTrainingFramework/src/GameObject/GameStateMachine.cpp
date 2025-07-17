#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine* GameStateMachine::instance = nullptr;

// game state loop
// pop old, push new, call stateChange()
GameStateMachine::GameStateMachine()
{
}

void GameStateMachine::PushState(StateType state)
{
	m_pNextState = GameStateBase::CreateState(state);
	///m_pActiveState = state->m_type;
	//Pause laij active 

	//m_stack.emplace_back(std::move(state));

}
void GameStateMachine::PopState()
{
	//checkechek
	if (m_stack.empty()) {
		return;
	}
	m_stack.back()->Exit();
	m_stack.pop_back();
	if (!m_stack.empty()) {
		m_stack.back()->Resume(); //assume init
	}
}

void GameStateMachine::PerformStateChange(std::unique_ptr<GameStateBase> state)
{
	PopState();
	PushState(std::move(state));

	//m_pActiveState = m_pNextState;
	//m_stack.emplace_back(std::move(state));

}
