#pragma once

#include "OpenGLWrappedh/Model.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Mesh.h"

#include <vector>

struct ModelLibrary
{
	ModelLibrary();
	~ModelLibrary() {}

	Model carModel;
	Texture playerTexture;

	std::vector<Texture> enemyCarTextures;

	Mesh skyboxMesh;
	Texture skyboxTexture;

	Mesh quadMesh;

	Texture defaultTexture;

	Texture playButTex;
	Texture playButHoverTex;

	Texture quitButTex;
	Texture quitButHoverTex;

	Texture htpButTex;
	Texture htpButHoverTex;
};