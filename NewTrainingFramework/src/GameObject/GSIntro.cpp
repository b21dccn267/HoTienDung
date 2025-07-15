#include "stdafx.h"
#include "GSIntro.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Object.h"
#include <memory>

void GSIntro::Pause()
{
}

void GSIntro::Exit()
{
}

void GSIntro::Resume()
{
}

// state is created by:
// 
void GSIntro::CreateState()
{
	//std::unique_ptr<Model> model = std::make_unique<Model>(new Model(modelFileName));

	//std::unique_ptr<Object> object = std::make_unique<Object>(new Object(model, texture, shader, pos, rotation, scale);
}

GSIntro::~GSIntro()
{
}
