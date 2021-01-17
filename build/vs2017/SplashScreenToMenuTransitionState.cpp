#include "SplashScreenToMenuTransitionState.h"

SplashScreenToMenuTransitionState::SplashScreenToMenuTransitionState() :
	blackBackground_texture(NULL)
{
}

SplashScreenToMenuTransitionState::~SplashScreenToMenuTransitionState()
{
}

StateBase::EStates SplashScreenToMenuTransitionState::Update(float frame_time)
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	//Once the animation is over go to the menu state
	return StateBase::MENU_STATE;
}

void SplashScreenToMenuTransitionState::Init()
{
}

void SplashScreenToMenuTransitionState::CleanUp()
{
	delete blackBackground_texture;
	blackBackground_texture = NULL;
}

void SplashScreenToMenuTransitionState::Render()
{
}

void SplashScreenToMenuTransitionState::DrawHUD()
{
}
