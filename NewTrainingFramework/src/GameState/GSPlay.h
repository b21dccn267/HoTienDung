#pragma once
#include "GameStateBase.h"
#include "../GameObject/core/Object.h"
#include "../GameObject/core/Animation.h"
#include "GameButton.h"
#include "../GameManager/SoundManager.h"
#include <memory>
#include <vector>


class GSPlay : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gsPlayObjects;
	std::vector<std::shared_ptr<Animation>> m_gsPlayAnimations;
	std::vector<std::shared_ptr<GameButton>> m_gsPlayButtons;

	//SoundManager m_soundManager;

	GSPlay() : GameStateBase(StateType::STATE_PLAY) {}
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSPlay() override;

private:
	static void OnPauseButtonClick();  // <-- Thêm callback function
};


