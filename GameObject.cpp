
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtx/quaternion.hpp>
#include "GameObject.h"

GameObject::GameObject()
{
	// Initialise everything here
	_mesh = NULL;
	_material = NULL;
	_orientation = glm::vec3(0, 0, -1);
	_speed = 0.0f;
	_turnRate = 0.0f;
}

GameObject::~GameObject()
{
	// Do any clean up here
}

void GameObject::Update( float deltaTs )
{
	// Put any update code here
	// Change the _position and _rotation to move the model


	_orientation.y += _turnRate*deltaTs;
	
	glm::vec3 upDirection(0, 1, 0);
	glm::vec3 rightDirection(1, 0, 0);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), _orientation.y, glm::vec3(0, 1, 0));

	// Scale matrix for the vehicle
	glm::mat4 scaleMatrix;  





	glm::mat4 fwd = rotationMatrix;
	fwd = glm::translate(fwd, glm::vec3(0.0f, 0.0f, _speed));
	glm::vec4 amount = fwd*glm::vec4(0, 0, 0, 1);
	_position += glm::vec3(amount);
	_speed = 0;
	
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1), _position);

	// Update model matrix by first scaling, then rotating, then translating
	_modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	// Keep a version of this without the scale - useful for camera transforms
	_modelMatrixNS = translationMatrix * rotationMatrix;
	
}

void GameObject::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if( _mesh != NULL )
	{
		if( _material != NULL )
		{
			
			
			_modelMatrix = glm::translate(glm::mat4(1.0f), _position );
			_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0,1,0) );
			_invModelMatrix = glm::rotate(glm::mat4(1.0f), -_rotation.y, glm::vec3(0,1,0) );

			// Give all the matrices to the material
			// This makes sure they are sent to the shader
			_material->SetMatrices(_modelMatrix, _invModelMatrix, viewMatrix, projMatrix);
			// This activates the shader
			_material->Apply();
		}

		// Sends the mesh data down the pipeline
		_mesh->Draw();

	}
	
}
void GameObject::CubeMaterialApply(glm::mat4 viewMatrix,glm::mat4 projMatrix)
{
	
	_material->Apply();
	_material->SetCubeMatrices(viewMatrix, projMatrix);

}
