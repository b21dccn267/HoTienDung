#pragma once
#include "Model.h"
#include "Object.h"
#include "Camera.h"
#include <vector>

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

	std::vector<Object*> m_objects;
	Camera* camera;

	int LoadFileSM(const char* fileName);
	int LoadObject();
	
	void Draw();	// calls objects' Draw()
	void Update();	// this one is left empty for now
	void Cleanup();
	void HandleKeyEvent(unsigned char key, bool isPressed);
private:
	SceneManager() {}; // private constructor
};

