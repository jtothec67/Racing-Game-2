#include "Skybox.h"

Skybox::Skybox(Game* _game) : GameObject(_game)
{
	mTag = Tag::Skybox;

	mShader = mGame->GetShaderLibrary()->skyboxShader;
	mMesh = mGame->GetModelLibrary()->skyboxMesh;
	mTexture = mGame->GetModelLibrary()->skyboxTexture;
}

void Skybox::Draw()
{
	if (!mVisible)
		return;

	mShader->drawSkybox(mMesh.get(), mTexture.get());
}