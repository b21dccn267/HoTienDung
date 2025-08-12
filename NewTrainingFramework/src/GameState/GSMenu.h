#pragma once
#include "GameButton.h"
#include "GameObject/core/Object.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>


class GSMenu : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gsMenuObjects;
	std::vector<std::shared_ptr<GameButton>> m_gsMenuGameButtons;

	GSMenu();
	void Init() override;
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;

	~GSMenu() override;

private:
	bool m_isSoundOn;  // Trạng thái sound on/off
	std::shared_ptr<Object> m_soundBg;  // Reference đến background object để có thể thay đổi texture
	void ToggleSound();  // Method để toggle sound state
};