#include "OptionsState.h"
#include <starter_app.h>
#include <audio/audio_manager.h>
#include "StateInfo.h"



OptionsState::OptionsState() :
	Yellow_Button_Text(NULL),
	background_(NULL)
{
}


OptionsState::~OptionsState()
{
}

StateBase::EStates OptionsState::Update(float frame_time)
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	const gef::SonyController* controller = stateInfo->input_manager_->controller_input()->GetController(0);

	if (controller)
	{
		// the following if statements are to control the options in the menu
		if (controller->buttons_released()  & gef_SONY_CTRL_DOWN)
		{
			menuChoice++;
		}

		if (controller->buttons_released()  & gef_SONY_CTRL_UP)
		{
			menuChoice--;
		}

		if (controller->buttons_released()  & gef_SONY_CTRL_CROSS)
		{

			switch (menuChoice)
			{
			case 0:
				// the following switch statement sets the difficulty based on what is already on the screen
				//switch (g_state_init_info_->DifficultyLvl)
				//{
				//case EASY: g_state_init_info_->setDifficulyLevel(NORMAL);
				//	break;
				//case NORMAL: g_state_init_info_->setDifficulyLevel(HARD);
				//	break;
				//case HARD: g_state_init_info_->setDifficulyLevel(EASY);
				//	break;

				//default:
				//	break;
				//}
				//break;
			case 1:
				//// switch statement to set the bike colour
				//switch (g_state_init_info_->bike_color)
				//{
				//case GREY: g_state_init_info_->setBikeColor(RED);
				//	break;
				//case RED: g_state_init_info_->setBikeColor(GREY);
				//	break;
				//default:
				//	break;
				//}
				//break;
			case 2:
				// Music if statement
				//if (g_state_init_info_->isMusicOn)
				//{
				//	g_state_init_info_->audio_manager->StopMusic();
				//	g_state_init_info_->isMusicOn = false;
				//}
				//else
				//{
				//	g_state_init_info_->audio_manager->PlayMusic();
				//	g_state_init_info_->isMusicOn = true;

				//}
				//break;
			case 3:
				// third case if to go back to the main menu
				return StateBase::EStates::MENU_STATE;
				break;
			default:
				break;
			}

		}

		if (menuChoice > 3)
			menuChoice = 0;
		if (menuChoice < 0)
			menuChoice = 3;


	}
	return StateBase::EStates::OPTIONS_STATE;
}

void OptionsState::CleanUp()
{
}

void OptionsState::Render()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	stateInfo->sprite_renderer_->Begin();
	stateInfo->sprite_renderer_->DrawSprite(background_sprite);

	// render the select difficulty button sprite
	stateInfo->sprite_renderer_->DrawSprite(Yellow_Button_Sprite);


	// set yellow button position based on menuChoice
	switch (menuChoice)
	{
	case 0: Yellow_Button_Sprite.set_position(gef::Vector4((stateInfo->platform_.width()* 0.5) - 140, (stateInfo->platform_.height() * 0.30) - offsetValue, -0.99f));
		break;
	case 1:  Yellow_Button_Sprite.set_position(gef::Vector4((stateInfo->platform_.width()* 0.5) - 140, (stateInfo->platform_.height() * 0.50) - offsetValue, -0.99f));
		break;
	case 2:  Yellow_Button_Sprite.set_position(gef::Vector4((stateInfo->platform_.width()* 0.5) - 140, (stateInfo->platform_.height()*0.70f) - offsetValue, -0.99f));
		break;
	case 3:  Yellow_Button_Sprite.set_position(gef::Vector4((stateInfo->platform_.width()* 0.5) - 140, (stateInfo->platform_.height()*0.90f) - offsetValue, -0.99f));
		break;

	default:
		break;
	}



	stateInfo->sprite_renderer_->End();

	stateInfo->sprite_renderer_->Begin(false);

	DrawHUD();

	stateInfo->sprite_renderer_->End();



}

void OptionsState::Init()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	background_ = CreateTextureFromPNG("TempSpriteAssetFolder/trialsRising Background900x506.png", stateInfo->platform_);

	Yellow_Button_Text = CreateTextureFromPNG("UIMenuSprites/yellow_button02.png", stateInfo->platform_);



	Yellow_Button_Sprite.set_texture(Yellow_Button_Text);
	Yellow_Button_Sprite.set_position(gef::Vector4((stateInfo->platform_.width() * 0.5) - 140, stateInfo->platform_.height() * 0.30, -0.99f));
	Yellow_Button_Sprite.set_height(40 + (40 * 0.5));
	Yellow_Button_Sprite.set_width(184 * 2.8);



	// initialising menuChoice to 0 
	menuChoice = 0;

	// setting up the background
	background_sprite.set_texture(background_);
	background_sprite.set_position(gef::Vector4(stateInfo->platform_.width() * 0.5, stateInfo->platform_.height() * 0.5, -0.99f));
	background_sprite.set_height(stateInfo->platform_.height());
	background_sprite.set_width(stateInfo->platform_.width());

}

void OptionsState::DrawHUD()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	if (stateInfo->font_)
	{

		// render difficulty text on screen, based on what the player chose
		stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4(stateInfo->platform_.width() * 0.10, stateInfo->platform_.height() * Y_text_offset_value, -0.9f), 2.0f, font_color, gef::TJ_LEFT, "SELECT DIFFICULTY:");
		switch (0)
		{
		case 0: stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((stateInfo->platform_.width() * 0.5f) + (stateInfo->platform_.width() * 0.3), stateInfo->platform_.height() * Y_text_offset_value, -0.9f), 2.0f, font_color, gef::TJ_CENTRE, "EASY");
			break;
		case 1: stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((stateInfo->platform_.width() * 0.5f) + (stateInfo->platform_.width() * 0.3), stateInfo->platform_.height() * Y_text_offset_value, -0.9f), 2.0f, font_color, gef::TJ_CENTRE, "NORMAL");
			break;
		case 2: stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((stateInfo->platform_.width() * 0.5f) + (stateInfo->platform_.width() * 0.3), stateInfo->platform_.height() * Y_text_offset_value, -0.9f), 2.0f, font_color, gef::TJ_CENTRE, "HARD");
			break;

		default:
			break;
		}

		// render bike colour text on screen, based on what the player chose
		stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4(stateInfo->platform_.width() * 0.10, stateInfo->platform_.height() * (Y_text_offset_value * 2), -0.9f), 2.0f, font_color, gef::TJ_LEFT, "SELECT BIKE COLOR:");
		if (true)
			stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((stateInfo->platform_.width() * 0.50) + (stateInfo->platform_.width() * 0.3f), stateInfo->platform_.height() * (Y_text_offset_value * 2), -0.9f), 2.0f, font_color, gef::TJ_CENTRE, "GREY");
		else
			stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((stateInfo->platform_.width() * 0.50) + (stateInfo->platform_.width() * 0.3f), stateInfo->platform_.height() * (Y_text_offset_value * 2), -0.9f), 2.0f, font_color, gef::TJ_CENTRE, "RED");


		// render music text 
		stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4(stateInfo->platform_.width() * 0.10, stateInfo->platform_.height() * (Y_text_offset_value * 3), -0.9f), 2.0f, font_color, gef::TJ_LEFT, "TOGGLE MUSIC:");

		//if (stateInfo->isMusicOn)
		//	stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((g_state_init_info_->platform_.width() * 0.50) + 250, stateInfo->platform_.height() * (Y_text_offset_value * 3), -0.9f), 2.0f, font_color, gef::TJ_LEFT, "ON");
		//else
		//	stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4((g_state_init_info_->platform_.width() * 0.50) + 250, stateInfo->platform_.height() * (Y_text_offset_value * 3), -0.9f), 2.0f, font_color, gef::TJ_LEFT, "OFF");


		// render go back message
		stateInfo->font_->RenderText(stateInfo->sprite_renderer_, gef::Vector4(stateInfo->platform_.width() * 0.10, stateInfo->platform_.height() * (Y_text_offset_value * 4), -0.9f), 2.0f, font_color, gef::TJ_LEFT, "GO BACK");

	}
}
