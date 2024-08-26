#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
	: objectShader("Assets/Shaders/ObjShader.vert", "Assets/Shaders/ObjShader.frag")
	, uiShader("Assets/Shaders/UIShader.vert", "Assets/Shaders/UIShader.frag")
	, skyboxShader("Assets/Shaders/SkyboxShader.vert", "Assets/Shaders/SkyboxShader.frag")
	, fontShader("Assets/Shaders/FontShader.vert", "Assets/Shaders/FontShader.frag")
{
	uiShader.uniform("u_View", glm::mat4(1.0f));
}