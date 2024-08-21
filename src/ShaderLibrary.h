#pragma once

#include "OpenGLWrappedh/Shader.h"

struct ShaderLibrary
{
	ShaderLibrary();
	~ShaderLibrary() {}

	Shader objectShader;
	Shader uiShader;
	Shader skyboxShader;
	Shader fontShader;
};