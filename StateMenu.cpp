#include "StateMenu.h"
#include "StateInfo.h"
#include <input/input_manager.h>
#include <starter_app.h>

//#include "load_texture.h"



StateMenu::StateMenu() :
	background_(NULL),
	Yellow_Button_Text(NULL)
{
	menu_options_space = 28.f;
	playbutton_space = 60.f;
	menu_button_space = 40.f;
}


StateMenu::~StateMenu()
{
}

StateBase::EStates StateMenu::Update(float frame_time)
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	const gef::SonyController* controller = stateInfo->input_manager_->controller_input()->GetController(0);


	// I'm lerping the x position variable to create the effect of a moving word 
	xp = lerp(xp, stateInfo->platform_.width() *0.25f, 0.15f);
	if (controller)
	{
		// I increase the menu choice whenever the down button is pressed
		if (controller->buttons_released()  & gef_SONY_CTRL_DOWN)
		{
			menuChoice++;
		}
		// I decrease the menu choice whenever the up button is pressed
		if (controller->buttons_released()  & gef_SONY_CTRL_UP)
		{
			menuChoice--;
		}

		if (controller->buttons_released()  & gef_SONY_CTRL_CROSS)
		{

			// I set up a switch to check whether the state machine needs to go to the lvl1 stato or option's menu state
			switch (menuChoice)
			{
			//case 0: return StateBase::EStates::LEVEL1_STATE;
			//	break;
			case 1: return StateBase::EStates::OPTIONS_STATE;
				break;
			default:
				break;
			}


			// this if statements clamp the values menuChoice can have
			if (menuChoice > 1)
				menuChoice = 0;
			if (menuChoice < 0)
				menuChoice = 1;



		}

		// 
		return StateBase::EStates::MENU_STATE;
	}

}

void StateMenu::CleanUp()
{
	delete background_;
	background_ = NULL;

	delete Yellow_Button_Text;
	Yellow_Button_Text = NULL;

}

void StateMenu::Render()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	stateInfo->sprite_renderer_->Begin();


	//render background
	stateInfo->sprite_renderer_->DrawSprite(background_sprite);

	// with this switch statement I'm changing the button sprite based on what the player is choosing
	switch (menuChoice)
	{
	case 0: Play_yellow_button_sprite.set_position(gef::Vector4(stateInfo->platform_.width() * 0.25f, stateInfo->platform_.height()*0.5f - menu_button_space * 2, -0.99f));
		break;
	case 1:  Play_yellow_button_sprite.set_position(gef::Vector4(stateInfo->platform_.width() * 0.25f, (stateInfo->platform_.height()*0.5f - menu_button_space * 2) + (menu_options_space * 3), -0.99f));
		break;
	default:
		break;
	}

	stateInfo->sprite_renderer_->DrawSprite(Play_yellow_button_sprite);

	// The following part of the code is for rendering the Play and Options text 
	stateInfo->font_->RenderText(
		stateInfo->sprite_renderer_,
		gef::Vector4(xp, (stateInfo->platform_.height()*0.5f - playbutton_space) - (menu_options_space * 2), -0.99f),
		2.0,
		font_color,
		gef::TJ_CENTRE,
		"PLAY");

		
	stateInfo->font_->RenderText(
		stateInfo->sprite_renderer_,
		gef::Vector4(xp, (stateInfo->platform_.height()*0.5f - playbutton_space) + menu_options_space, -0.99f),
		2.0f,
		font_color,
		gef::TJ_CENTRE,
		"OPTIONS");



	stateInfo->sprite_renderer_->End();


}

void StateMenu::Init()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	// initalize background texture nd sprite settings
	background_ = CreateTextureFromPNG("TempSpriteAssetFolder/trialsRising Background900x506.png", stateInfo->platform_);
	background_sprite.set_texture(background_);
	background_sprite.set_position(gef::Vector4(stateInfo->platform_.width() * 0.5, stateInfo->platform_.height() * 0.5, -0.99f));
	background_sprite.set_height(stateInfo->platform_.height());
	background_sprite.set_width(stateInfo->platform_.width());

	// initalize yellow button texture and sprite settings
	Yellow_Button_Text = CreateTextureFromPNG("UIMenuSprites/yellow_button01.png", stateInfo->platform_);
	Play_yellow_button_sprite.set_texture(Yellow_Button_Text);
	Play_yellow_button_sprite.set_height(40 + (40 * 0.5));
	Play_yellow_button_sprite.set_width(184 + (184 * 0.5));

	// this variable represents the x position of the play and options words
	xp = 1.f;


	// initialising menuChoice to 0 
	menuChoice = 0;


}

float StateMenu::lerp(float _a, float _b, float _t)
{
	return _a + (_b - _a) * _t;
}
