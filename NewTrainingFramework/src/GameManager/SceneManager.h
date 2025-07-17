#pragma once
#include "Model.h"
#include "Object.h"
#include "Camera.h"
#include <vector>
#include <memory>

// this class manages all objects of scene
// Camera obj == MVPMatrix for now
class SceneManager
{
public:
	SceneManager(const SceneManager& instance) = delete;
	static SceneManager* instance;
	static SceneManager* getInstance() {
		if (!instance)
		{
			instance = new SceneManager();
		}
		return instance;
	}

	std::vector<std::shared_ptr<Object>> m_objects;
	Camera* camera;

	int LoadFileSM(const char* fileName);
	
	void Draw(std::shared_ptr<Object> object);
	void Draw();
	void Update();	// this one is left empty for now
	void Cleanup();
	void HandleKeyEvent(unsigned char key, bool isPressed);
private:
	SceneManager() {}; // private constructor
};

