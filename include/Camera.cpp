#include <Camera.h>

Camera::Camera(Game* _game, float _FOV, float _nearClip, float _farClip) : GameObject(_game)
{
	mFOV = _FOV;
	mNearClip = _nearClip;
	mFarClip = _farClip;
}