
#include "GameObject.h"
#include "Ground.h"
#include "Tree.h"
#include "Cube.h"
// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

#include <string>
#include <vector>

// The scene contains objects, the camera and light
// It is responsible for coordinating these things
class Scene
{
public:

	
	// Currently the scene is set up in the constructor
	// This means the object(s) are loaded, given materials and positions as well as the camera and light
	Scene();
	~Scene();

	// Use these to adjust the camera's orientation
	// Camera is currently set up to rotate about the world-space origin NOT the camera's origin
	void ChangeCameraAngleX( float value ) { _cameraAngleX += value; }
	void ChangeCameraAngleY( float value ) { _cameraAngleY += value; }
	void SetTurn(float value) { _model->SetTurn(value); }

	void SetSpeed(float value) { _model->SetSpeed(value); }
	bool isColliding(glm::vec3 a, glm::vec3 b);
	void Collide();
	

	// Calls update on all objects in the scene
	void Update( float deltaTs );

	// Draws the scene from the camera's point of view
	void Draw();
	std::vector<Tree*> obstacles;
	bool collideX, collideY, collideZ;
	std::vector<std::string>cubeFaces;
	unsigned int cubeMapTexture;
	


protected:

	// Currently one object, this could be a list of objects!
	GameObject *_model;
	Ground  *_ground;
	Ground  *_ground2;
	Tree *_tree;
	Tree *_tree2;
	Tree *_tree3;
	Tree *_tree4;
	Cube *_cube;

		
	// This matrix represents the camera's position and orientation
	glm::mat4 _viewMatrix;
	
	glm::mat4 _cubeViewMatrix;

	
	// This matrix is like the camera's lens
	glm::mat4 _projMatrix;

	

	// Current rotation information about the camera
	float _cameraAngleX, _cameraAngleY;

	// Position of the single point-light in the scene
	glm::vec3 _lightPosition= { -1.2f, -4.0f, 6.2f };
	glm::vec3 _lightColor = { 0.8f,0.8f,0.8f };
	


};
