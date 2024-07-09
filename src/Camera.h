#pragma once

#include <GameObject.h>

class Camera : public GameObject
{
public:
	Camera(Game* _game, float _FOV, float _nearClip, float _farClip);
	~Camera() {}

	float GetFOV() { return mFOV; }
	void SetFOV(float _FOV) { mFOV = _FOV; }

	float GetNearClip() { return mNearClip; }
	void SetNearClip(float _nearClip) { mNearClip = _nearClip; }

	float GetFarClip() { return mFarClip; }
	void SetFarClip(float _farClip) { mFarClip = _farClip; }

private:
	float mFOV;
	float mNearClip;
	float mFarClip;
};