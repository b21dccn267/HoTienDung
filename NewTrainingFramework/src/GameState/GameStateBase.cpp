#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPause.h"
#include "GSSettings.h"
#include "GSGameOver.h"
#include "GSPlay.h"
#include <memory>


GameStateBase::GameStateBase(StateType type)
{
	m_type = type;
}

GameStateBase::~GameStateBase()
{

}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType type)
{
	switch (type) {
	case StateType::STATE_INTRO:
		return std::make_shared<GSIntro>();
	case StateType::STATE_MENU:
		return std::make_shared<GSMenu>();
	case StateType::STATE_PLAY:
		return std::make_shared<GSPlay>();
	case StateType::STATE_SETTINGS:
		return std::make_shared<GSSettings>();
	case StateType::STATE_PAUSE: 
		return std::make_shared<GSPause>();
	case StateType::STATE_GAMEOVER:
		return std::make_shared<GSGameOver>();
	}
}
