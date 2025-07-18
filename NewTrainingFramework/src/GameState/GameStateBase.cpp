#include "stdafx.h"
#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include <memory>


GameStateBase::GameStateBase(StateType type)
{
	m_type = type;
}

GameStateBase::~GameStateBase()
{

}

std::unique_ptr<GameStateBase> CreateState(StateType type)
{
	switch (type) {
	case StateType::STATE_INTRO:
		return std::make_unique<GSIntro>();
	case StateType::STATE_MENU:
		return std::make_unique<GSMenu>();
	case StateType::STATE_PLAY:
		return std::make_unique<GSPlay>();
	}
}