// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "../../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "GameManager/InputManager.h"
#include "GameManager/ResourceManager.h"
#include "GameManager/SceneManager.h"
#include "GameManager/SoundManager.h"
#include "GameState/GameStateBase.h"
#include "GameState/GameStateMachine.h"
#include "Globals.h"
#include <tchar.h>
#include <conio.h>
#include <memory>


int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::GetInstance()->LoadFileRM("../Resources/Config/ResourceManager.txt");

	SceneManager::GetInstance()->InitCamera();

	// soundmanager init
	SoundManager::GetInstance()->Init();

	// start with StateType::STATE_INTRO
	GameStateMachine::GetInstance()->PushState(StateType::STATE_GAME);

	return 0;
}

void Draw ( ESContext *esContext ) 
{
	GameStateMachine::GetInstance()->m_stack.top()->Draw();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	GameStateMachine::GetInstance()->m_stack.top()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	InputManager::GetInstance()->keys[key] = bIsPressed;

	GameStateMachine::GetInstance()->m_stack.top()->HandleKeyEvent(key, bIsPressed);
}

void MouseClick(ESContext* esContext, GLint x, GLint y, bool bIsPressed)
{
	GameStateMachine::GetInstance()->m_stack.top()->HandleMouseEvent(x, y, bIsPressed);
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y)
{
	printf("MouseMove\n");
}

void CleanUp()
{
	InputManager::GetInstance()->DestroyInstance();
	ResourceManager::GetInstance()->DestroyInstance();
	SceneManager::GetInstance()->DestroyInstance();
	SoundManager::GetInstance()->DestroyInstance();
	GameStateMachine::GetInstance()->DestroyInstance();
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