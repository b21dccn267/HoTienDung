#pragma once
#include "Model.h"
#include "Object.h"

// this class manages all objects of scene
// game state manager (primitive form)
class SceneManager
{
public:
	Object* m_objects;
	//Model m_cameras;

	int LoadFile();
	int LoadObject();
	//int LoadCamera();
	
	void Draw();	// calls objects' Draw()
	void Update();	// this one is left empty for now
};

