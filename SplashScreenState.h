#pragma once
#include "StateBase.h"
#include <graphics/sprite.h>
#include <load_texture.h>
class SplashScreenState :
	public StateBase
{
public:
	SplashScreenState();
	~SplashScreenState();


	virtual StateBase::EStates Update(float frame_time);
	virtual void Init();
	virtual void CleanUp();
	virtual void Render();
	void DrawHUD();

private:

	float lerp(float _a, float _b, float _t);

	gef::Texture* checker_texture_;
	gef::Sprite checker_sprite_;

	gef::Texture* logo_texture_;
	gef::Sprite logo_sprite_;

	float logo_Y_pos;
	float text_Y_pos;


};

