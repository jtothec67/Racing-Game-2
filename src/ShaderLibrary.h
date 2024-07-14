#pragma once

#include "Shader.h"

struct ShaderLibrary
{
	ShaderLibrary();
	~ShaderLibrary() {}

	Shader objectShader;
	Shader uiShader;
	Shader skyboxShader;
};