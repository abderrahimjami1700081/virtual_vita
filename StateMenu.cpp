#include "StateMenu.h"
#include "StateInfo.h"
#include <input/input_manager.h>
#include <starter_app.h>
#include "input/keyboard.h"
//#include "load_texture.h"



StateMenu::StateMenu() :
	background_(NULL),
	Yellow_Button_Text(NULL),
	checker_texture_(NULL),
	logo_Background_Shadow_texture_(NULL),
	blackSlider_Texture(NULL),
	PlayTextButton_texture(NULL),
	Options_texture(NULL),
	tower_texture_(NULL),
	timer(0.0f),
	isAnimationPlaying(true), 
	towerHeight(100),
	towerWidrth(98),
	rotationIncrement(0.0f),
	buttonWidth(((40 + (40 * 0.5)) * 3)),
	buttonHeight(((40 + (40 * 0.5)) * 3))
{
	menu_options_space = 28.f;
	playbutton_space = 60.f;
	menu_button_space = 40.f;
}

uint32_t makeABGR2(float r, float g, float b, float a)
{
	return (int)(a * 255) << 24 | (int)(b * 255) << 16 | (int)(g * 255) << 8 | (int)(r * 255);
}

StateMenu::~StateMenu()
{
}

StateBase::EStates StateMenu::Update(float frame_time)
{
	//timer += frame_time * 0.5;
	//if (timer > 1.0f)
	//{
	//	timer = 1.0f;
	//}
	//if (isAnimationPlaying)
	//{
	//	if (blackSlider_Sprite.position().x() != sliderFinalPosition)
	//	{
	//		sliderIncrement = lerp(blackSlider_Sprite.position().x(), sliderFinalPosition, timer);
	//	}
	//	else
	//	{
	//		isAnimationPlaying = false;
	//	}
	//}


	//if (!isAnimationPlaying)
	//{
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

	}
	if (stateInfo->input_manager_)
	{
		stateInfo->input_manager_->Update();


		// keyboard input
		gef::Keyboard* keyboard = stateInfo->input_manager_->keyboard();

		if (keyboard)
		{
			// the following if statements are to control the options in the menu
			if (keyboard->IsKeyDown(gef::Keyboard::KC_S))
			{
				menuChoice++;
			}

			if (keyboard->IsKeyDown(gef::Keyboard::KC_W))
			{
				menuChoice--;
			}

			if (keyboard->IsKeyDown(gef::Keyboard::KC_RETURN))
			{

				// I set up a switch to check whether the state machine needs to go to the lvl1 stato or option's menu state
				switch (menuChoice)
				{
					case 0: return StateBase::EStates::LEVEL1_STATE;
						break;
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
		}
	}


	rotationIncrement += .3f;
	if (rotationIncrement > 360)
	{
		rotationIncrement = 0.f;
	}
	logo_Background_Shadow_sprite_.set_rotation(gef::DegToRad(rotationIncrement));
	Play_yellow_button_sprite.set_rotation(gef::DegToRad(rotationIncrement));


	timer += frame_time * 4.5;
	if (timer > 1.0f)
		timer = 1.0f;
	Play_yellow_button_sprite.set_width(lerp(0.0f, buttonWidth, timer));
	logo_Background_Shadow_sprite_.set_width(lerp(0.0f, buttonWidth, timer));

	Play_yellow_button_sprite.set_height(lerp(0.0f, buttonWidth, timer));
	logo_Background_Shadow_sprite_.set_height(lerp(0.0f, buttonWidth, timer));

	PlayTextButton_sprite.set_width(lerp(0.0f, buttonWidth * 0.8f, timer));
	PlayTextButton_sprite.set_height(lerp(0.0f, buttonWidth * 0.8f, timer));


	OptionsButton_sprite.set_width(lerp(0.0f, buttonWidth * 0.8f, timer));
	OptionsButton_sprite.set_height(lerp(0.0f, buttonWidth * 0.8f, timer));





	//}
	// 
	return StateBase::EStates::MENU_STATE;

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
	//stateInfo->sprite_renderer_->DrawSprite(background_sprite);
	static int s_frame = 0;



	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			checker_sprite_.set_position(i * 64 - (s_frame % 64) + 32, j * 64 - (s_frame % 64) + 32, 0);
			stateInfo->sprite_renderer_->DrawSprite(checker_sprite_);
		}
	}
	s_frame++;

		// with this switch statement I'm changing the button sprite based on what the player is choosing
	switch (menuChoice)
	{
	case 0: 
		Play_yellow_button_sprite.set_position(gef::Vector4(stateInfo->platform_.width() * 0.25f, stateInfo->platform_.height()*0.5f - menu_button_space * 2, -0.99f));
		logo_Background_Shadow_sprite_.set_position(gef::Vector4((stateInfo->platform_.width() * 0.25f) + 3, (stateInfo->platform_.height()*0.5f - menu_button_space * 2) + 3, -0.99f));

		break;
	case 1:  
		Play_yellow_button_sprite.set_position(gef::Vector4(stateInfo->platform_.width() * 0.25f, (stateInfo->platform_.height() * 0.5f + menu_button_space * 2), -0.99f));
		logo_Background_Shadow_sprite_.set_position(gef::Vector4((stateInfo->platform_.width() * 0.25f) + 3, ((stateInfo->platform_.height()*0.5f + menu_button_space * 2) + 3), -0.99f));
		break;																																	
	default:
		break;
	}

	stateInfo->sprite_renderer_->DrawSprite(logo_Background_Shadow_sprite_);
	stateInfo->sprite_renderer_->DrawSprite(Play_yellow_button_sprite);

	stateInfo->sprite_renderer_->DrawSprite(tower_sprite_);
	stateInfo->sprite_renderer_->DrawSprite(PlayTextButton_sprite);
	stateInfo->sprite_renderer_->DrawSprite(OptionsButton_sprite);
	stateInfo->sprite_renderer_->End();


	//// The following part of the code is for rendering the Play and Options text 
	//stateInfo->font_->RenderText(
	//	stateInfo->sprite_renderer_,
	//	gef::Vector4(xp, (stateInfo->platform_.height()*0.5f - playbutton_space) - (menu_options_space * 2), -0.99f),
	//	2.0,
	//	font_color,
	//	gef::TJ_CENTRE,
	//	"PLAY");

	//	
	//stateInfo->font_->RenderText(
	//	stateInfo->sprite_renderer_,
	//	gef::Vector4(xp, (stateInfo->platform_.height()*0.5f - playbutton_space) + menu_options_space, -0.99f),
	//	2.0f,
	//	font_color,
	//	gef::TJ_CENTRE,
	//	"OPTIONS");

	//blackSlider_Sprite.set_position(gef::Vector4(sliderIncrement, stateInfo->platform_.height() / 2, 0.0f));
	//stateInfo->sprite_renderer_->DrawSprite(blackSlider_Sprite);


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
	Yellow_Button_Text = CreateTextureFromPNG("MenuPNGs/MenuButton.png", stateInfo->platform_);
	Play_yellow_button_sprite.set_texture(Yellow_Button_Text);
	Play_yellow_button_sprite.set_height(((40 + (40 * 0.5)) * 3));
	Play_yellow_button_sprite.set_width(((40 + (40 * 0.5)) * 3));


	// initalize tower texture and sprite settings
	tower_texture_ = CreateTextureFromPNG("Tower/old-defense-tower-cartoon-illustration-medieval.png", stateInfo->platform_);
	tower_sprite_.set_texture(tower_texture_);
	tower_sprite_.set_height(towerHeight);
	tower_sprite_.set_width(towerWidrth);
	tower_sprite_.set_position(gef::Vector4(stateInfo->platform_.width() / 2, stateInfo->platform_.height() / 2, 0.0f));


	// initialize background logo shadow sprite
	logo_Background_Shadow_texture_ = CreateTextureFromPNG("SplashScreenPNGs/LogoBackgroundShadow.png", stateInfo->platform_);
	logo_Background_Shadow_sprite_.set_texture(logo_Background_Shadow_texture_);
	logo_Background_Shadow_sprite_.set_width(((40 + (40 * 0.5)) * 3));
	logo_Background_Shadow_sprite_.set_height(((40 + (40 * 0.5)) * 3));


	// initialize playButton sprite logo shadow sprite
	PlayTextButton_texture = CreateTextureFromPNG("MenuPNGs/PlayOptionButton.png", stateInfo->platform_);
	PlayTextButton_sprite.set_texture(PlayTextButton_texture);
	PlayTextButton_sprite.set_width(((40 + (40 * 0.5)) * 3));
	PlayTextButton_sprite.set_height(((40 + (40 * 0.5)) * 3));
	PlayTextButton_sprite.set_position(gef::Vector4((stateInfo->platform_.width() * 0.25f) + 3, (stateInfo->platform_.height()*0.5f - menu_button_space * 2) + 3, -0.99f));

	// initialize Options Button sprite logo shadow sprite
	Options_texture = CreateTextureFromPNG("MenuPNGs/PlayOptionButton.png", stateInfo->platform_);
	OptionsButton_sprite.set_texture(Options_texture);
	OptionsButton_sprite.set_width(((40 + (40 * 0.5)) * 3));
	OptionsButton_sprite.set_height(((40 + (40 * 0.5)) * 3));
	OptionsButton_sprite.set_position(gef::Vector4((stateInfo->platform_.width() * 0.25f) + 3, (stateInfo->platform_.height()*0.5f + menu_button_space * 2) + 3, -0.99f));
	

	// initialize checker sprite
	checker_texture_ = CreateTextureFromPNG("Backgrounds/check.png", stateInfo->platform_);
	checker_sprite_.set_texture(checker_texture_);
	checker_sprite_.set_width(64);
	checker_sprite_.set_height(64);
	checker_sprite_.set_position(0, 0, 0);
	float r = 197;
	float g = 123;
	float b = 87;
	r /= 255.f;
	g /= 255.f;
	b /= 255.f;
	checker_sprite_.set_colour(makeABGR2(r, g, b, 1.0f));


	// initalize black slider texture and sprite settings
	blackSlider_Texture = CreateTextureFromPNG("Backgrounds/SphereBackground.png", stateInfo->platform_);
	blackSlider_Sprite.set_texture(blackSlider_Texture);
	blackSlider_Sprite.set_height(stateInfo->platform_.height());
	blackSlider_Sprite.set_width((stateInfo->platform_.width() * 1.5f));
	blackSlider_Sprite.set_rotation(gef::DegToRad(180.0f));
	float temp = -stateInfo->platform_.width() * 1.5f;
	sliderFinalPosition = temp;
	sliderIncrement = stateInfo->platform_.width() * 1.5f;
	blackSlider_Sprite.set_position(stateInfo->platform_.width() * 1.5f, stateInfo->platform_.height() / 2, 0.0f);
	// this variable represents the x position of the play and options words
	xp = 1.f;


	// initialising menuChoice to 0 
	menuChoice = 0;


}

float StateMenu::lerp(float _a, float _b, float _t)
{
	return _a + (_b - _a) * _t;
}
