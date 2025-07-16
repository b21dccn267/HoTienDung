#include "stdafx.h"
#include "GSIntro.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Object.h"
#include <memory>

GSIntro::GSIntro(int id)
{
	m_stateId = id;
}


void GSIntro::Pause()
{
}

void GSIntro::Exit()
{
}

void GSIntro::Resume()
{
}


void GSIntro::CreateState()
{
}

void GSIntro::Update()
{
}

void GSIntro::HandleKeyEvent()
{
}

void GSIntro::HandleMouseEvent()
{
}

void GSIntro::Cleanup()
{
}

// state contains assets
// state should be able to control these assets
// game state vs sceneman
// state are modular, holds certain assets, is linked to other states and call them on the stack of gsm
// sceneman manages asset loading(constructing objects) as well as displaying, updating...
// 
// new form: 
// resman does asset loading and store them based on type
// sceneman bundles them into objects
// state pick these objects
//GameStateBase GSIntro::CreateState()
//{
//	//std::unique_ptr<Model> model = std::make_unique<Model>(new Model(modelFileName));
//	return GameStateBase();
//	//std::unique_ptr<Object> object = std::make_unique<Object>(new Object(model, texture, shader, pos, rotation, scale);
//}

GSIntro::~GSIntro()
{
}
