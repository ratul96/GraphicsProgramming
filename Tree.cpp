#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtx/quaternion.hpp>
#include "Tree.h"
Tree::Tree()
{
	_mesh = NULL;
	_material = NULL;
	_orientation = glm::vec3(0, 0, 2);
}
Tree::~Tree()
{

}
void Tree::Update(float deltaTS)
{
	
	//_modelMatrixNS = translationMatrix * rotationMatrix;
	

	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
	_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0, 1, 0));
	_modelMatrix = glm::scale(_modelMatrix, glm::vec3(scale, scale, scale));
	_invModelMatrix = glm::rotate(glm::mat4(1.0f), -_rotation.y, glm::vec3(0, 1, 0));
	

}