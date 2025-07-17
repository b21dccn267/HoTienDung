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
#include "StateType.h"
#include <memory>

// sceneman now only bundles assets into objects for gs to copy
// and do camera/matrix calc (by giving camera obj function access via singleton calls)
// gsm stack must be strict lifo
// how to do stack ops:
//		- no more init in main, have init calls based on enum
//		- gsm class members will store init stuff to be put in

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::getInstance()->LoadFileRM("../Resources/Config/ResourceManager.txt");

	SceneManager::getInstance()->LoadFileSM("../Resources/Config/SceneManager.txt");

	std::unique_ptr<GameStateBase> intro = std::make_unique<GSIntro>(StateType::STATE_INTRO);
	intro->Init();
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
	///PerformStateChange()
	//SceneManager::getInstance()->Update();
	GameStateMachine::GetInstance()->m_stack.back()->Update();
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//SceneManager::getInstance()->HandleKeyEvent(key, bIsPressed);
	GameStateMachine::GetInstance()->m_stack.back()->HandleKeyEvent();
}

void MouseClick(ESContext* esContext, GLint x, GLint y, bool bIsPressed)
{
	printf("MouseClick\n");
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y)
{
	printf("MouseMove\n");
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
	esRegisterMouseFunc(&esContext, MouseClick);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);

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