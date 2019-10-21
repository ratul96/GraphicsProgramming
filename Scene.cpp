
#include "Scene.h"

#include <iostream>
#include <SDL/SDL.h>



Scene::Scene()
{
	_cameraAngleX = 0.3f, _cameraAngleY = 1.5f;

	// Set up the viewing matrix
	// This represents the camera's orientation and position
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5f) );

	
	// Set up a projection matrix
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	 cubeMapTexture=0;




	// Set up your scene here
	unsigned int lastTime = SDL_GetTicks();
	
	// Position of the light, in world-space
	//_lightPosition = glm::vec3(1.2f, 2.0f, 1.2f);
	
	
	
	
	//GLfloat ambientColor[] = { 0.2f,0.2f,0.2f,1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	// Create a game object
	// This needs a material and a mesh
	_model = new GameObject();
	_tree = new Tree();
	_tree2 = new Tree();
	_tree3 = new Tree();
	_tree4 = new Tree();
	_ground = new Ground();
	_ground2 = new Ground();
	_cube = new Cube();

	// Create the material for the game object
	Material *modelMaterial = new Material();
	Material *groundMaterial = new Material();
	Material *groundMaterial2 = new Material();
	Material *treeMaterial = new Material();
	Material *treeMaterial2 = new Material();
	Material *treeMaterial3 = new Material();
	Material *treeMaterial4 = new Material();
	Material *cubeMaterial = new Material();
	// Shaders are now in files
	modelMaterial->LoadShaders("Vertshader2.txt","FragShader2.txt");
	groundMaterial->LoadShaders("Vertshader2.txt", "FragShader2.txt");
	groundMaterial2->LoadShaders("Vertshader2.txt", "FragShader2.txt");
	treeMaterial->LoadShaders("Vertshader2.txt", "FragShader2.txt");			/*All the materials using the shaders*/
	treeMaterial2->LoadShaders("Vertshader2.txt", "FragShader2.txt");
	treeMaterial3->LoadShaders("Vertshader2.txt", "FragShader2.txt");
	treeMaterial4->LoadShaders("Vertshader2.txt", "FragShader2.txt");
	cubeMaterial->LoadShaders("Vertshader3.txt", "FragShader3.txt");
	_cube->SetMaterial(cubeMaterial);
	cubeMapTexture = _cube->LoadCubemap(cubeFaces);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

	//Set Textures
	modelMaterial->SetTexture("silver.bmp");
	groundMaterial->SetTexture("road.bmp");
	groundMaterial2->SetTexture("road.bmp");
	treeMaterial->SetTexture("green.bmp");
	treeMaterial2->SetTexture("green.bmp");
	treeMaterial3->SetTexture("green.bmp");
	treeMaterial4->SetTexture("green.bmp");

	//Set cubeMap textures
	cubeFaces.push_back("silver.bmp");
	cubeFaces.push_back("silver.bmp");
	cubeFaces.push_back("silver.bmp");
	cubeFaces.push_back("silver.bmp");
	cubeFaces.push_back("silver.bmp");
	cubeFaces.push_back("silver.bmp");
	
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	

	// Tell the game object to use this material
	

	// The mesh is the geometry for the object
	Mesh *modelMesh = new Mesh();
	Mesh *groundMesh = new Mesh();
	Mesh *groundMesh2 = new Mesh();
	Mesh *treeMesh = new Mesh();
	Mesh *treeMesh2 = new Mesh();
	Mesh *treeMesh3 = new Mesh();
	Mesh *treeMesh4 = new Mesh();
	
	// Load from OBJ file. This must have triangulated geometry
	modelMesh->LoadOBJ("Car.obj");
	groundMesh->LoadOBJ("roundabout.obj");
	groundMesh2->LoadOBJ("roundabout.obj");
	treeMesh->LoadOBJ("Tree.obj");
	treeMesh2->LoadOBJ("Tree.obj");
	treeMesh3->LoadOBJ("Tree.obj");
	treeMesh4->LoadOBJ("Tree.obj");
	/*treeMesh4->FrameBuffer();*/

	// Tell the game object to use this mesh
	_model->SetMesh(modelMesh);
	_model->SetPosition(0.0f, -2.0f, -1.5f);
	

	
	
	_ground->SetMesh(groundMesh);
	_ground->SetPosition(0.0f, -2.1f, -5.0f);

	
	_ground2->SetMesh(groundMesh);
	_ground2->SetPosition(1.0f, -2.1f, -30.0f);
	
	_tree->SetMesh(treeMesh);
	_tree->SetPosition(3.0f, -2.0f, -5.5f);
	
	_tree2->SetMesh(treeMesh2);
	_tree2->SetPosition(0.0f, -1.0f, -11.5f);

	_tree3->SetMesh(treeMesh3);
	_tree3->SetPosition(-3.0f, -1.0f, -9.5f);

	_tree4->SetMesh(treeMesh4);
	_tree4->SetPosition(-6.0f, -1.0f, -7.5f);
	
	
		
		
		/*modelMaterial->SetLightPosition(_lightPosition);
		groundMaterial->SetLightPosition(_lightPosition);
		groundMaterial2->SetLightPosition(_lightPosition);*/
		
		
	
	
	_model->SetMaterial(modelMaterial);
	
	 
	_ground->SetMaterial(groundMaterial);
	_ground2->SetMaterial(groundMaterial2);
	
	_tree->SetMaterial(treeMaterial);
	_tree2->SetMaterial(treeMaterial2);
	_tree3->SetMaterial(treeMaterial3);
	_tree4->SetMaterial(treeMaterial4);
	
	
	//Initialize VAO and VBO for cubemap
	
	
	
}
bool Scene::isColliding(glm::vec3 a, glm::vec3 b)
{
	collideX = false;
	collideY = false;
	collideZ = false;
	if (a.x < b.x)
	{
		if (a.x + 1 > b.x - 0.9)
		{
			collideX = true;
		}
	}
	else
	{
		if (b.x + 1 > a.x - 0.9)
		{
			collideX = true;
		}
	}
	if (a.y < b.y)
	{
		if (a.y + 1 > b.y - 0.9)
		{
			collideY = true;
		}
	}
	else
	{
		if (b.y + 1 > a.y - 0.9)
		{
			collideY = true;
		}
	}
	if (a.z < b.z)
	{
		if (a.z + 1 > b.z - 0.9)
		{
			collideZ = true;
		}
	}
	else
	{
		if (b.z + 1 > a.z - 0.9)
		{
			collideZ = true;
		}
	}
	if (collideX&&collideY&&collideZ)
	{
		return true;
	}
	return false;
}
void Scene::Collide()
{
	bool colliding = false;
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		if (isColliding(_model->GetPosition(), obstacles.at(i)->GetPosition()))
		{
			colliding = true;
			_model->SetPosition(0.0f, -2.0f, -3.5f);
		}
	}
	
	
	if (!colliding)
	{
		_model->GetPosition();
	}
}



Scene::~Scene()
{
	
}

void Scene::Update( float deltaTs )
{
	// Update the game object (this is currently hard-coded to rotate)
	_model->Update( deltaTs );
	_ground->Update(deltaTs);
	_ground2->Update(deltaTs);
	_tree->Update(deltaTs);
	_tree2->Update(deltaTs);
	_tree3->Update(deltaTs);
	_tree4->Update(deltaTs);
	
	obstacles.push_back(_tree);
	obstacles.push_back(_tree2);
	obstacles.push_back(_tree3);
	obstacles.push_back(_tree4);


	

	// This updates the camera's position and orientation
	_viewMatrix = glm::rotate( glm::rotate( glm::translate( glm::mat4(1.0f), glm::vec3(0,0,-8.0f) ), _cameraAngleX, glm::vec3(1,0,0) ), _cameraAngleY, glm::vec3(0,1,0) );
	_viewMatrix = _model->_modelMatrix;
	_viewMatrix = _ground->_modelMatrix;
	////moving the camera up and down
	_viewMatrix = glm::translate(_viewMatrix, glm::vec3(0, 1, 3));
	_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleX, glm::vec3(1, 0, 0));
	_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleY, glm::vec3(0, 1, 0));
	_cubeViewMatrix = glm::mat4(glm::mat3(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))));


	Collide();
	
	
	
}

void Scene::Draw()
{
	// Draw that model, giving it the camera's position and projection

	_cube->cubeDraw();
	_cube->CubeMaterialApply(_cubeViewMatrix, _projMatrix);
	
	_model->Draw(_viewMatrix,_projMatrix);

	
	_ground->Draw(_viewMatrix, _projMatrix);
	_ground2->Draw(_viewMatrix, _projMatrix);
	_tree->Draw(_viewMatrix, _projMatrix);
	_tree2->Draw(_viewMatrix, _projMatrix);
	

	
	_tree3->Draw(_viewMatrix, _projMatrix);
	_tree4->Draw(_viewMatrix, _projMatrix);

	
	
}



