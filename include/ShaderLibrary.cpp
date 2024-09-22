#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
{
	uiShader->uniform("u_View", glm::mat4(1.0f));
}