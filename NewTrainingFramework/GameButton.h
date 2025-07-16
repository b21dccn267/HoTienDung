#pragma once
#include "Object.h"
#include <memory>


class GameButton : public Object
{
public:
	GameButton() : Object(), m_pBtnClick(nullptr), m_isHolding(false) {}
	GameButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader); // refactor containers accordingly
	~GameButton();
	void SetOnClick(void* (pBtnClick)());
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool IsHolding();


private:
	void (*m_pBtnClick)();
	bool m_IsHolding();
};

