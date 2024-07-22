#include "Skybox.h"

#include <iostream>

#include <glm/ext.hpp>

Skybox::Skybox(Game* _game) : GameObject(_game)
{
	mTag = Tag::Skybox;

	mShader = &(mGame->GetShaderLibrary()->skyboxShader);
	mMesh = &(mGame->GetModelLibrary()->skyboxMesh);
	mTexture = &(mGame->GetModelLibrary()->skyboxTexture);
}

void Skybox::Draw()
{
	// Change depth function so depth test passes when values are equal to depth buffer's content
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	mShader->drawSkybox(*mMesh, *mTexture);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}