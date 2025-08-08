#pragma once
#include "../Utilities/utilities.h"
#include <GameObject/core/Object.h>
#include <GameObject/core/Texture.h>
#include <vector>

// need custom sprite order function, as many free spritesheets have funny ordering
class Animation : public Object
{
public:
	// flip both two values when changing format in shader
	int m_numFramesPerRow;
	int m_numFramesPerColumn;
	float m_frameTime;
	float m_currentTime;w

	// custom frame anim variables
	// the stuff is still divided by rows and columns
	// but index number should be from left to right, from top to bottom, start at 0
	int m_frameCount;
	int m_frameX;	// row
	int m_frameY;	// column
	std::vector<int> m_frameOrder;
	
	Animation() : Object(), m_currentTime(0.0f), m_frameTime(0.0f) {};
	Animation(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader, int frameTime, int currentAction);

	void FrameNumberToCoord(int number);
	void SetCustomFrames(std::vector<int> order);
	void SetCustomFrames(std::vector<int> order, bool isLooped);
	void CustomUpdate(GLfloat deltaTime);
	void CustomDraw();
};

