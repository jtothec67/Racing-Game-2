#pragma once

#include "OpenGLWrappedh/Shader.h"

#include <memory>

struct ShaderLibrary
{
	ShaderLibrary();
	~ShaderLibrary() {}

	std::shared_ptr<Shader> objectShader = std::make_shared<Shader>("Assets/Shaders/ObjShader.vert", "Assets/Shaders/ObjShader.frag");
	std::shared_ptr<Shader> uiShader = std::make_shared<Shader>("Assets/Shaders/UIShader.vert", "Assets/Shaders/UIShader.frag");
	std::shared_ptr<Shader> skyboxShader = std::make_shared<Shader>("Assets/Shaders/SkyboxShader.vert", "Assets/Shaders/SkyboxShader.frag");
	std::shared_ptr<Shader> fontShader = std::make_shared<Shader>("Assets/Shaders/FontShader.vert", "Assets/Shaders/FontShader.frag");
};