#pragma once
#include "Object.h"
#include "Texture.h"
#include "../Utilities/utilities.h"

// need custom sprite order function, as many free spritesheets have funny ordering
class Animation : public Object
{
public:
	// flip both two values when changing format in shader
	int m_numFrames = 9;		// row
	int m_numActions = 7;		// column
	float m_frameTime;
	int m_currentFrame;
	int m_currentAction;
	float m_currentTime;
	
	
	Animation() : Object(), m_currentFrame(0), m_currentTime(0.0f), m_currentAction(0), m_frameTime(0.0f) {};
	Animation(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader, int frameTime, int currentAction);
	//	: Object(model, texture, shader) {};

	void Draw();
	void Update(GLfloat deltaTime);
};

