#include "Cube.h"
#include<SDL/SDL.h>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include<iostream>
Cube::Cube()
{
	_vertices = 36;
}
Cube::~Cube()
{

}
GLuint Cube::CreateCubeVAO(unsigned int &numVertices)
{
	GLuint VAO = 0;
	// Creates one VAO
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);

	float vertices[] = {
		-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
	};

	numVertices = 36;


	
	GLuint buffer = 0;

	glGenBuffers(1, &buffer);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, vertices, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);




	
	glVertexAttrib4f(1, 0.0f, 0.0f, 1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	glDisableVertexAttribArray(0);

	return VAO;
	
}
void Cube::DrawVAOTris(GLuint VAO, int numVertices)
{
	glBindVertexArray(VAO);
	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	// Unbind VAO
	glBindVertexArray(0);
}

unsigned int Cube::LoadCubemap(std::vector<std::string> faces)
{
	unsigned int cubeTexture;
	glGenTextures(1, &cubeTexture);
	;

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		SDL_Surface *cubeImage = SDL_LoadBMP(faces.at(i).c_str());
		if (!cubeImage)
		{
			std::cerr << "Warning:Couldn't Load CubeMap image at " << faces.at(i) << std::endl;
			return 0;
			SDL_FreeSurface(cubeImage);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, cubeImage->w, cubeImage->h, 0, GL_RGB, GL_UNSIGNED_BYTE, cubeImage->pixels);
			SDL_FreeSurface(cubeImage);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);

	return cubeTexture;





}
void Cube::cubeDraw()
{
	GLuint cubeVAO=CreateCubeVAO(_vertices);
	/*glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), (glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec3(0.0f, 0.0f, 1.0f));*/
	DrawVAOTris(cubeVAO, _vertices);

}