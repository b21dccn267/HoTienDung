#pragma once
#include "GameObject/core/Object.h"
#include "GameStateBase.h"
#include <memory>
#include <vector>


// class which loads models based on key event
// for debugging texture
class GSDebug : public GameStateBase
{
public:
	std::vector<std::shared_ptr<Object>> m_gsDebugObjects;

	GSDebug() : GameStateBase(StateType::STATE_DEBUG) {}
	void Init() override;
	void SwapObject(int id);
	void Pause() override;
	void Exit() override;
	void Resume() override;
	void Draw() override;
	void Update(float deltaTime) override;
	void HandleKeyEvent(unsigned char key, bool bIsPressed) override;
	void HandleMouseEvent(GLint x, GLint y, bool bIsPressed) override;
	void Cleanup() override;


	~GSDebug() override;
};

