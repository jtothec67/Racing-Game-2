#include "ModelLibrary.h"

ModelLibrary::ModelLibrary()
	: carModel("Assets/Models/F1Car/Model/formula_car.obj")
	, playerTexture("Assets/Models/F1Car/Textures/car_02_m.png")
	, trackModel("Assets/Models/Track/Models/Track_line_type_01_30m_free.obj")
	, trackAndGrassTexture("Assets/Models/Track/Texture/Track_Texture_free.png")
	, grassModel("Assets/Models/Track/Models/Lawn_plane_15m_free.obj")
	, skyboxTexture({ "Assets/UITextures/skybox/px.png", "Assets/UITextures/skybox/nx.png", "Assets/UITextures/skybox/py.png", "Assets/UITextures/skybox/ny.png", "Assets/UITextures/skybox/pz.png", "Assets/UITextures/skybox/nz.png" })
	, defaultTexture("Assets/UITextures/defaultTex.png")
	, unselectedButtonTex("Assets/UITextures/unselectedButtonTex.png")
	, selectedButtonTex("Assets/UITextures/selectedButtonSelectedTex.png")
	, testFont("Assets/Fonts/munro.ttf")
{
	skyboxMesh = Mesh("skybox");

	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m2.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m3.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m4.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m5.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m6.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m7.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m8.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m9.png"));
	enemyCarTextures.push_back(Texture("Assets/Models/F1Car/Textures/car_02_m10.png"));

	quadMesh = Mesh();

	Face face;
	face.a.m_position = glm::vec3(1.0f, 0.0f, 0.0f);
	face.b.m_position = glm::vec3(0.0f, 1.0f, 0.0f);
	face.c.m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	face.a.m_texcoords = glm::vec2(1.0f, 0.0f);
	face.b.m_texcoords = glm::vec2(0.0f, 1.0f);
	face.c.m_texcoords = glm::vec2(0.0f, 0.0f);
	quadMesh.add(face);

	Face face2;
	face2.a.m_position = glm::vec3(1.0f, 0.0f, 0.0f);
	face2.b.m_position = glm::vec3(1.0f, 1.0f, 0.0f);
	face2.c.m_position = glm::vec3(0.0f, 1.0f, 0.0f);
	face2.a.m_texcoords = glm::vec2(1.0f, 0.0f);
	face2.b.m_texcoords = glm::vec2(1.0f, 1.0f);
	face2.c.m_texcoords = glm::vec2(0.0f, 1.0f);
	quadMesh.add(face2);

	textMesh = Mesh("text");
}