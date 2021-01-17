#pragma once
#include "StateBase.h"
#include <graphics/sprite.h>
#include <load_texture.h>
#include <maths/math_utils.h>
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
	float LinearInterpolation(float x, float t, float b, float c, float d);
	float LinearTime(float time, float begin, float change, float duration);
	float easeOutQuad(float x, float t, float b, float c, float d);

	gef::Texture* checker_texture_;
	gef::Sprite checker_sprite_;

	gef::Texture* logo_Background_texture_;
	gef::Sprite logo_Background_sprite_;

	gef::Texture* blackBackground_texture;
	gef::Sprite blackBackground_sprite_;

	gef::Texture* logo_Background_Shadow_texture_;
	gef::Sprite logo_Background_Shadow_sprite_;

	gef::Texture* logo_texture_;
	gef::Sprite logo_sprite_;

	float logo_Y_pos;
	float text_Y_pos;
	float rotationIncrement;

	float logoWidth, logoHeight;
	bool isLogoExpanded;
	float logoExpansionLerpRate;
	float logoMaxExpansionDimention;
	float TextYPos;
	float TextYfinalPos;

	float counter, percent;

	float fps, duration, iterations, startPosition, endPosition,
		distance, timeIncrement, time, position;
	float Temp;


	bool startTransition, isTransitionEnded;
	float blackBackgroundAlpha;
	float sliderPosition;
	
};

