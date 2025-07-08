// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "MVPMatrix.h"
#include "Globals.h"
#include <conio.h>


Shaders myShaders;
Texture myTexture;
Model myModel;
MVPMatrix myMatrix;
//GLfloat mvpLine[16];

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	// enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	// Dynamic vertex and index
	Vertex* verticesData = nullptr;
	GLuint* indicesData = nullptr;

	// model loading
	myModel.Init("../Resources/Packs/Models/Woman1.nfg");
	myModel.SetModelParameters(); // will take verticesData and IndicesData as input, then write to
	myModel.BindBuffer();

	myTexture.Init("../Resources/Packs/Textures/Woman1.tga");
	myTexture.SetTextureParameters();

	myMatrix.Init();
	myMatrix.MatrixToArray();


	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_TRUE);

	glUseProgram(myShaders.program);
	
	glBindBuffer(GL_ARRAY_BUFFER, myModel.vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myModel.iboId);

	// take location value from vertex/fragment shader. With Position we have location = 0
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	// texture
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}
	int iTextureLoc = glGetUniformLocation(myShaders.program, "u_texture");
	glUniform1i(iTextureLoc, 0);
	// mvp matrix
	int iMatrixLoc = glGetUniformLocation(myShaders.program, "u_mvp");
	glUniformMatrix4fv(iMatrixLoc, 1, GL_TRUE, myMatrix.mvpLine);
	// ibo object
	{
		glDrawElements(GL_TRIANGLES, myModel.indexCount, GL_UNSIGNED_INT, 0);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{

}

void CleanUp()
{
	glDeleteBuffers(1, &myModel.vboId);
	glDeleteBuffers(1, &myModel.iboId);
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