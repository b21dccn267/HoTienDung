#pragma once
#include <../../Utilities/utilities.h>

class InputManager
{
public:
	InputManager(const InputManager& instance) = delete;
	static InputManager* instance;
	static InputManager* GetInstance() {
		if (!instance)
		{
			instance = new InputManager();
		}
		return instance;
	}
	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

	bool keys[256] = { false };
	GLint m_mouseX;
	GLint m_mouseY;
	bool m_mouseIsPressed;

private:
	InputManager() {};
};

