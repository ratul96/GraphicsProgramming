#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtx/quaternion.hpp>
#include "Ground.h"
Ground::Ground()
{
	_mesh = NULL;
	_material=NULL;
	_orientation = glm::vec3(0, 0, 1);
}
Ground::~Ground()
{

}
void Ground::Update(float deltaTS)
{
	// Update model matrix by first scaling, then rotating, then translating
	//_modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	// Keep a version of this without the scale - useful for camera transforms
	//_modelMatrixNS = translationMatrix * rotationMatrix;
	
	glStencilMask(0x00);
	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
	_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0, 1, 0));
	_invModelMatrix = glm::rotate(glm::mat4(1.0f), -_rotation.y, glm::vec3(0, 1, 0));

}