// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Globals.h"
#include <conio.h>
#include "GameStateMachine.h"
#include "GameStateBase.h"
#include "GSIntro.h"
#include <memory>

// init first state
// push into gs machine
// state inits objects and load
// 
//
// how to deal with sceneman:
//		- turn it into a state, have the other two modeled the same
//		- nuke sceneman, and now have all states doing the object init, calling resman by id directly
//		+ keep sceneman, and have states calling sm to load assets 
//
// to use 3rd option, have stack and init done after resman and sceneman calls
// game states will get its objects from sm based on id
// sm will no longer make draw update etc calls, that belongs to (current) game state

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glDepthMask(GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::getInstance()->LoadFileRM("../Resources/Config/ResourceManager.txt");

	SceneManager::getInstance()->LoadFileSM("../Resources/Config/SceneManager.txt");
	SceneManager::getInstance()->LoadObject();

	std::unique_ptr<GameStateBase> intro = std::make_unique<GSIntro>(2);
	GameStateMachine::GetInstance()->PushState(std::move(intro));

	//GameStateMachine::GetInstance()->CurrentState()
	return 0;
}

void Draw ( ESContext *esContext )
{
	//SceneManager::getInstance()->Draw();
	GameStateMachine::GetInstance()->m_stack.back()->Resume();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	//SceneManager::getInstance()->Update();
	GameStateMachine::GetInstance()->m_stack.back()->Update();
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//SceneManager::getInstance()->HandleKeyEvent(key, bIsPressed);
	GameStateMachine::GetInstance()->m_stack.back()->HandleKeyEvent();
}

void CleanUp()
{
	//glDeleteBuffers(1, &sceneManager->m_objects->model->vboId);
	//glDeleteBuffers(1, &sceneManager->m_objects->model->iboId);
	//SceneManager::getInstance()->Cleanup();
	GameStateMachine::GetInstance()->m_stack.back()->Cleanup();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );
	printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}