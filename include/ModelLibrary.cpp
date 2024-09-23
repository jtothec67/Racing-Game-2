#include "ModelLibrary.h"

ModelLibrary::ModelLibrary()
{
    enemyCarTextures.reserve(10);
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m2.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m3.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m4.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m5.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m6.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m7.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m8.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m9.png"));
    enemyCarTextures.emplace_back(std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m10.png"));

    Face face;
    face.a.m_position = glm::vec3(1.0f, 0.0f, 0.0f);
    face.b.m_position = glm::vec3(0.0f, 1.0f, 0.0f);
    face.c.m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    face.a.m_texcoords = glm::vec2(1.0f, 0.0f);
    face.b.m_texcoords = glm::vec2(0.0f, 1.0f);
    face.c.m_texcoords = glm::vec2(0.0f, 0.0f);
    quadMesh->add(face);

    Face face2;
    face2.a.m_position = glm::vec3(1.0f, 0.0f, 0.0f);
    face2.b.m_position = glm::vec3(1.0f, 1.0f, 0.0f);
    face2.c.m_position = glm::vec3(0.0f, 1.0f, 0.0f);
    face2.a.m_texcoords = glm::vec2(1.0f, 0.0f);
    face2.b.m_texcoords = glm::vec2(1.0f, 1.0f);
    face2.c.m_texcoords = glm::vec2(0.0f, 1.0f);
    quadMesh->add(face2);

    // Add all models, textures, and meshes to their respective containers
    models = { carModel, trackModel, grassModel };
    textures = { playerTexture, trackAndGrassTexture, skyboxTexture, defaultTexture, unhoveredButtonTex, hoveredButtonTex };
    textures.insert(textures.end(), enemyCarTextures.begin(), enemyCarTextures.end());
    meshes = { skyboxMesh, quadMesh, textMesh };
}

void ModelLibrary::Update()
{
    // Unload models if their reference count is 1
    for (auto& model : models)
    {
        if (model.use_count() == 1)
        {
            model->Unload();
        }
    }

    // Unload textures if their reference count is 1
    for (auto& texture : textures)
    {
        if (texture.use_count() == 1)
        {
            texture->Unload();
        }
    }

    // Unload meshes if their reference count is 1
    for (auto& mesh : meshes)
    {
        if (mesh.use_count() == 1)
        {
            mesh->Unload();
        }
    }
}