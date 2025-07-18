#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine* GameStateMachine::instance = nullptr;

// game state loop
// pop old, push new, call stateChange()
// when push, next state
GameStateMachine::GameStateMachine()
{
}

void GameStateMachine::PushState(StateType state)
{
	m_pNextState = GameStateBase::CreateState(state);
	///m_pActiveState = state->m_type;
	//Pause laij active 
	m_pNextState->Init();
	if (!m_stack.empty()) {
		m_stack.top()->Pause();
	}

	m_stack.push(m_pNextState);

}
void GameStateMachine::PopState()
{
	if (m_stack.empty()) {
		return;
	}
	m_stack.top()->Exit();
	m_stack.pop();
	if (!m_stack.empty()) {
		m_stack.top()->Resume();
	}
}

void GameStateMachine::PerformStateChange(StateType state)
{
	PopState();
	PushState(std::move(state));

	//m_pActiveState = m_pNextState;
	//m_stack.emplace_back(std::move(state));

}
