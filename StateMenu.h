#pragma once
//#include <system/application.h>
//#include <graphics/sprite_renderer.h>
#include "..\CMP404Coursework\load_texture.h"

#include "StateBase.h"
#include <graphics/sprite.h>

class StateMenu :
	public StateBase
{
public:

	StateMenu();
	~StateMenu();

	virtual StateBase::EStates Update(float frame_time);
	virtual void CleanUp();
	virtual void Render();
	virtual void Init();


private:

	float lerp(float _a, float _b, float _t);
	float xp;
	gef::Texture* background_;
	gef::Texture* Yellow_Button_Text;
	gef::Texture* blackSlider_Texture;
	// checker sprite and texture 
	gef::Texture* checker_texture_;
	gef::Sprite checker_sprite_;


	gef::Texture* logo_Background_Shadow_texture_;
	gef::Sprite logo_Background_Shadow_sprite_;

	gef::Texture* PlayTextButton_texture;
	gef::Sprite PlayTextButton_sprite;


	gef::Texture* Options_texture;
	gef::Sprite OptionsButton_sprite;

	// checker sprite and texture 
	gef::Texture* tower_texture_;
	gef::Sprite tower_sprite_;
	float towerWidrth, towerHeight;


	gef::Sprite blackSlider_Sprite;
	gef::Sprite Play_yellow_button_sprite;
	gef::Sprite Option_sprite;
	gef::Sprite background_sprite;

	// menu choice int for selecting menu options
	int menuChoice;


	// these variables are used to setup the menu UI
	float menu_options_space;
	float playbutton_space;
	float menu_button_space;


	float timer;
	float sliderFinalPosition, sliderIncrement;
	bool isAnimationPlaying;
	//FONT COLOR
	int font_color = 0xFF0000FF;

	float buttonWidth, buttonHeight;

	float rotationIncrement;
};

