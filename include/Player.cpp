#include "Player.h"

#include <glm/ext.hpp>

Player::Player(Game* _game) : GameObject(_game)
{
	mShader = new Shader("Assets/Shaders/Shader.vert", "Assets/Shaders/Shader.frag");
	mModel = mGame->GetModelLibrary()->carModel;
	mTexture = mGame->GetModelLibrary()->playerTexture;

	transform.rotation.y = 90;

	transform.position.x = -50;
	transform.position.z = -50;
}

void Player::Update(float _deltaTime)
{
	transform.position.x += 0.1f;
}

void Player::Draw()
{
	int width, height;
	mGame->GetWindowSize(width, height);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.f);

	// Translate, rotate, and scale model
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(2, 2, 2));

	// Use camera position and rotation to translate and rotate view matrix, then inverse it (view moves left, objects move right)
	glm::mat4 view(1.0f);
	view = glm::translate(view, mGame->GetCamera()->transform.position);
	view = glm::rotate(view, glm::radians(mGame->GetCamera()->transform.rotation.x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians(mGame->GetCamera()->transform.rotation.y), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(mGame->GetCamera()->transform.rotation.z), glm::vec3(0, 0, 1));
	view = glm::inverse(view);

	// Upload uniforms to our shader
	GetShader()->uniform("u_Projection", projection);
	GetShader()->uniform("u_Model", model);
	GetShader()->uniform("u_View", view);
	GetShader()->uniform("u_LightPos", mGame->GetLightPos());

	// Draw using our shader and out model and texture
	GetShader()->draw(GetModel(), GetTexture());
}