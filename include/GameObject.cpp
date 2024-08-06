#include "GameObject.h"
#include "Game.h"

glm::vec3 Transform::GetForward()
{
	glm::vec3 forward;
	forward.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	forward.y = sin(glm::radians(rotation.x));
	forward.z = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));

	return glm::normalize(forward);
}

glm::vec3 Transform::GetRight()
{
	glm::vec3 right;
	right.x = sin(glm::radians(rotation.y - 90)) * cos(glm::radians(rotation.x));
	right.y = sin(glm::radians(rotation.x));
	right.z = cos(glm::radians(rotation.y - 90)) * cos(glm::radians(rotation.x));

	return glm::normalize(right);
}

glm::vec3 Transform::GetUp()
{
	glm::vec3 up;
	up.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x + 90));
	up.y = sin(glm::radians(rotation.x + 90));
	up.z = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x + 90));

	return glm::normalize(up);
}