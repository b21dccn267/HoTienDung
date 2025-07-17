#include "stdafx.h"
#include "GameStateBase.h"

GameStateBase::GameStateBase(StateType type)
{
	m_type = type;
}


GameStateBase::~GameStateBase()
{
}
GameStateBase* CreateState(StateType type)
{
	switch (type) {
	case StateType::STATE_INTRO:
		return new GSIntro;
	}
		case StateType::STATE_INTRO:
			return new GSIntro;
}

}