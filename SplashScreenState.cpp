#include "SplashScreenState.h"
#include <starter_app.h>
#include "StateInfo.h"
#include "input\input_manager.h"
#include <input/keyboard.h>

uint32_t makeABGR(float r, float g, float b, float a)
{
	return (int)(a * 255) << 24 | (int)(b * 255) << 16 | (int)(g * 255) << 8 | (int)(r * 255);
}



SplashScreenState::SplashScreenState():
	checker_texture_(NULL),
	logo_texture_(NULL)
{
}


SplashScreenState::~SplashScreenState()
{
}

StateBase::EStates SplashScreenState::Update(float frame_time)
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	const gef::SonyController* controller = stateInfo->input_manager_->controller_input()->GetController(0);
	if (controller)
	{
		if (controller->buttons_released())
		{
			return StateBase::EStates::MENU_STATE;
		}
	}

	if (stateInfo->input_manager_)
	{
		stateInfo->input_manager_->Update();


		// keyboard input
		gef::Keyboard* keyboard = stateInfo->input_manager_->keyboard();

		if (keyboard)
		{
			if (keyboard->IsKeyDown(gef::Keyboard::KC_SPACE))
				return StateBase::EStates::MENU_STATE;

		}

	}


	logo_Y_pos = lerp(logo_Y_pos, 240, 0.15);
	text_Y_pos = lerp(text_Y_pos, stateInfo->platform_.height() * 0.75, 0.15f);
	return StateBase::EStates::SPLASH_SCREEN_STATE;



}

void SplashScreenState::Init()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();


	// initialize logo sprite
	logo_texture_ = CreateTextureFromPNG("Backgrounds/Logo_Transparent.png", stateInfo->platform_);
	logo_sprite_.set_texture(logo_texture_);
	logo_sprite_.set_width(360 * 1.5);
	logo_sprite_.set_height(56 * 1.5);


	// initialize checker sprite
	checker_texture_ = CreateTextureFromPNG("Backgrounds/check.png", stateInfo->platform_);
	checker_sprite_.set_texture(checker_texture_);
	checker_sprite_.set_width(64);
	checker_sprite_.set_height(64);
	checker_sprite_.set_position(0, 0, 0);
	checker_sprite_.set_colour(makeABGR(0.6, 0.9, 1.0, 1.0));



	logo_Y_pos = 1.f;
	text_Y_pos = 1.f;


}

void SplashScreenState::CleanUp()
{
	delete logo_texture_;
	logo_texture_ = NULL;

	delete checker_texture_;
	checker_texture_ = NULL;

}

void SplashScreenState::Render()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	gef::Matrix44 proj_matrix2d;

	proj_matrix2d = stateInfo->platform_.OrthographicFrustum(0.0f, stateInfo->platform_.width(), 0.0f, stateInfo->platform_.height(), -1.0f, 1.0f);
	stateInfo->sprite_renderer_->set_projection_matrix(proj_matrix2d);


	 //following code renders checkers background
	static int s_frame = 0;
	stateInfo->sprite_renderer_->Begin();
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			checker_sprite_.set_position(i * 64 + (s_frame % 64) - 32, j * 64 + (s_frame % 64) - 32, 0);
			stateInfo->sprite_renderer_->DrawSprite(checker_sprite_);
		}
	}
	s_frame++;

	logo_sprite_.set_position(480, 200, 0);
	stateInfo->sprite_renderer_->DrawSprite(logo_sprite_);

	//stateInfo->sprite_renderer_->DrawSprite(logo_sprite_);
	stateInfo->sprite_renderer_->End();



	stateInfo->sprite_renderer_->Begin(false);

	DrawHUD();

	stateInfo->sprite_renderer_->End();



}

void SplashScreenState::DrawHUD()	
{

	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	if (stateInfo->font_)
	{
		stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4(stateInfo->platform_.width() *  0.50, text_Y_pos, -0.9f), 2.0f, 0xFF000000, gef::TJ_CENTRE, "PRESS ANY BUTTON");
	}

}

float SplashScreenState::lerp(float _a, float _b, float _t)
{
	return _a + (_b - _a) * _t;
}
