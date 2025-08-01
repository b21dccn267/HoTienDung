#pragma once
#include "Object.h"
#include "Texture.h"
#include "../../../../Utilities/utilities.h"
#include <vector>

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

	// custom frame anim variables
	// the stuff is still divided by rows and columns
	// but index number should be from left to right, from top to bottom, start at 0
	int m_frameCount;
	int m_frameX;	// row
	int m_frameY;	// column
	std::vector<int> m_frameOrder;
	bool m_isFlipX;
	bool m_isFlipY;
	
	Animation() : Object(), m_currentFrame(0), m_currentTime(0.0f), m_currentAction(0), m_frameTime(0.0f) {};
	Animation(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader, int frameTime, int currentAction);
	//	: Object(model, texture, shader) {};
	void FrameNumberToCoord(int number);
	void FrameAt(int number);
	void SetCustomFrames(std::vector<int> order);
	void SetCustomFrames(std::vector<int> order, bool isLooped);
	void CustomUpdate(GLfloat deltaTime);
	void CustomDraw();
	void Draw();
	void Update(GLfloat deltaTime);
};

