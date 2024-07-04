#pragma once

#include "Model.h"
#include "Texture.h"
#include "Mesh.h"

#include <vector>

#ifndef MODELLIBRARY_H
#define MODELLIBRARY_H

struct ModelLibrary
{
	ModelLibrary();
	~ModelLibrary() {}

	Model carModel;
	Texture playerTexture;

	std::vector<Texture> enemyCarTextures;

	Mesh quadMesh;

	Texture defaultTexture;
};

#endif // MODELLIBRARY_H