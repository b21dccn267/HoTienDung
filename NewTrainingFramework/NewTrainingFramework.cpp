// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "Globals.h"
#include <conio.h>

//#include <iostream>
//#include <vector>


//GLuint vboId, iboId;
//GLuint textureId;
Shaders myShaders;
Texture myTexture;
Model myModel;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	// Dynamic vertex and index
	Vertex* verticesData = nullptr;
	GLuint* indicesData = nullptr;

	//triangle data (heap)
	/*Vertex verticesData[3];

	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;

	verticesData[0].uv.x = 0.5f;  verticesData[0].uv.y = 1.0f;
	verticesData[1].uv.x = 0.0f;  verticesData[1].uv.y = 0.0f;
	verticesData[2].uv.x = 1.0f;  verticesData[2].uv.y = 0.0f;
	*/
	//GLuint indicesData[3] = { 0, 1, 2 };

	// read from nfg file for Vertex and Index 
	//FILE* f = fopen("../Resources/Packs/Models/Woman1.nfg", "r");
	//char line[200];

	//fgets(line, sizeof line, f);
	//size_t total = strtoul(strchr(line, ':') + 1, nullptr, 10);		// string to size_t the locate chars after ':'

	////Vertex* buffer = new Vertex[total];
	//size_t count = 0;
	//
	////temp fix
	//Vertex verticesData[512];

	//while (count < total && fgets(line, sizeof line, f)) {
	//	float fX = 0, fY = 0, fZ = 0, fUx = 0, fUy = 0;
	//	sscanf_s(line, "%*[^p]pos:[%f ,%f ,%f]; %*[^u]uv:[%f ,%f];", &fX, &fY, &fZ, &fUx, &fUy);
	//	
	//	verticesData[count].pos.x = fX;
	//	verticesData[count].pos.y = fY;
	//	verticesData[count].pos.z = fZ;
	//	verticesData[count].uv.x = fUx;
	//	verticesData[count].uv.y = fUy;

	//	count++;
	//}

	//count = 0;
	//fgets(line, sizeof line, f);
	//total = strtoul(strchr(line, ':') + 1, nullptr, 10);
	//GLuint indicesData[2154];
	//while (count < total && fgets(line, sizeof line, f)) {
	//	int iX, iY, iZ;
	//	sscanf_s(line, "%*d. %d,%d,%d", &iX, &iY, &iZ);
	//	
	//	indicesData[count] = iX; count++;
	//	indicesData[count] = iY; count++;
	//	indicesData[count] = iZ; count++;
	//}

	//fclose(f);


	// model loading
	myModel.Init("../Resources/Packs/Models/Woman1.nfg");
	myModel.SetModelParameters(); // will take verticesData and IndicesData as input, then write to
	myModel.BindBuffer();

	myTexture.Init("../Resources/Packs/Textures/Woman1.tga");
	myTexture.SetTextureParameters();
		

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

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