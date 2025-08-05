#pragma once
#include "GameObject/core/Model.h"
#include "GameObject/core/Object.h"
#include "GameObject/core/Camera.h"
#include <vector>
#include <memory>

// this class bundles assets into objects for game states
// as well as enabling Camera access for gs draw
class SceneManager
{
public:
	SceneManager(const SceneManager& instance) = delete;
	static SceneManager* instance;
	static SceneManager* GetInstance() {
		if (!instance)
		{
			instance = new SceneManager();
		}
		return instance;
	}

	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

	std::shared_ptr<Camera> camera;

	void InitCamera();

private:
	SceneManager() {};
};

