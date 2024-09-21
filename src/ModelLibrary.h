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

	Texture unhoveredButtonTex;
	Texture hoveredButtonTex;

	Font testFont;
	Mesh textMesh;
};