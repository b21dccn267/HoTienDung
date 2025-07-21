#pragma once
#include "GameStateBase.h"
#include "Object.h"
#include "GameButton.h"
#include <memory>
#include <vector>


class GSIntro : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gsIntroObjects;
	std::vector<std::shared_ptr<GameButton>> m_gsIntroGameButtons;

	GSIntro() : GameStateBase(StateType::STATE_INTRO) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSIntro() override;	
};

