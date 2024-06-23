#pragma once

#include "Model.h"
#include "Texture.h"
#include "Mesh.h"

#include <vector>

#ifndef MODELLIBRARY_H
#define MODELLIBRARY_H

class ModelLibrary
{
public:
	ModelLibrary();
	~ModelLibrary();

	Model* carModel;
	Texture* playerTexture;

	std::vector<Texture*> enemyCarTextures;

	Mesh* quadMesh;
};

#endif // MODELLIBRARY_H