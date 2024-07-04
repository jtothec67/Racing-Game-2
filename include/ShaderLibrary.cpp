#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
	: objectShader("Assets/Shaders/ObjShader.vert", "Assets/Shaders/ObjShader.frag")
	, uiShader("Assets/Shaders/UIShader.vert", "Assets/Shaders/UIShader.frag")
{

}