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
	mShader->drawSkybox(*mMesh, *mTexture);
}