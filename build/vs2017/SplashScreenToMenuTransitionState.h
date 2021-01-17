#pragma once
#include "StateBase.h"
#include <graphics/sprite.h>
#include <load_texture.h>
#include <maths/math_utils.h>

class SplashScreenToMenuTransitionState :
	public StateBase
{
public:
	SplashScreenToMenuTransitionState();
	~SplashScreenToMenuTransitionState();
	virtual StateBase::EStates Update(float frame_time);
	virtual void Init();
	virtual void CleanUp();
	virtual void Render();
	void DrawHUD();

private:

	gef::Texture* blackBackground_texture;
	gef::Sprite blackBackground_sprite_;





};

