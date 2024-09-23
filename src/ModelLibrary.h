#pragma once

#include "OpenGLWrappedh/Model.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Font.h"

#include <vector>
#include <memory>

struct ModelLibrary
{
    ModelLibrary();
    ~ModelLibrary() {}

    void Update();

    std::shared_ptr<Model> carModel = std::make_shared<Model>("Assets/Models/F1Car/Model/formula_car.obj");
    std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>("Assets/Models/F1Car/Textures/car_02_m.png");

    std::vector<std::shared_ptr<Texture>> enemyCarTextures;

    std::shared_ptr<Model> trackModel = std::make_shared<Model>("Assets/Models/Track/Models/Track_line_type_01_30m_free.obj");
    std::shared_ptr<Model> grassModel = std::make_shared<Model>("Assets/Models/Track/Models/Lawn_plane_15m_free.obj");
    std::shared_ptr<Texture> trackAndGrassTexture = std::make_shared<Texture>("Assets/Models/Track/Texture/Track_Texture_free.png");

    std::shared_ptr<Mesh> skyboxMesh = std::make_shared<Mesh>("skybox");
    std::shared_ptr<Texture> skyboxTexture = std::make_shared<Texture>(std::vector<std::string>{
        "Assets/UITextures/skybox/px.png", "Assets/UITextures/skybox/nx.png",
        "Assets/UITextures/skybox/py.png", "Assets/UITextures/skybox/ny.png",
        "Assets/UITextures/skybox/pz.png", "Assets/UITextures/skybox/nz.png"
    });

    std::shared_ptr<Mesh> quadMesh = std::make_shared<Mesh>();

    std::shared_ptr<Texture> defaultTexture = std::make_shared<Texture>("Assets/UITextures/defaultTex.png");

    std::shared_ptr<Texture> unhoveredButtonTex = std::make_shared<Texture>("Assets/UITextures/unselectedButtonTex.png");
    std::shared_ptr<Texture> hoveredButtonTex = std::make_shared<Texture>("Assets/UITextures/selectedButtonSelectedTex.png");

    std::shared_ptr<Font> testFont = std::make_shared<Font>("Assets/Fonts/munro.ttf");
    std::shared_ptr<Mesh> textMesh = std::make_shared<Mesh>("text");

    // Containers to store all models, textures, and meshes
    std::vector<std::shared_ptr<Model>> models;
    std::vector<std::shared_ptr<Texture>> textures;
    std::vector<std::shared_ptr<Mesh>> meshes;
};