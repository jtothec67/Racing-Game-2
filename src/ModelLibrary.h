#pragma once

#include "OpenGLWrappedh/Model.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Font.h"

#include <vector>

struct ModelLibrary
{
	ModelLibrary();
	~ModelLibrary() {}

	Model carModel;
	Texture playerTexture;

	std::vector<Texture> enemyCarTextures;

	Model trackModel;
	Model grassModel;
	Texture trackAndGrassTexture;

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

	Font testFont;
	Mesh textMesh;
};