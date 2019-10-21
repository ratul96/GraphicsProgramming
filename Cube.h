#pragma once
#include<string>
#include<vector>
#include "GameObject.h"
class Cube:public GameObject
{
public:
	Cube();
	~Cube();
	GLuint CreateCubeVAO(unsigned int &numVertices);
	void DrawVAOTris(GLuint VAO, int numVertices);
	unsigned int LoadCubemap(std::vector<std::string> faces);
	void cubeDraw();
	unsigned int _vertices;
	
	

};
