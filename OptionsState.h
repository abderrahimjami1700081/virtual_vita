#pragma once
#include "StateBase.h"
#include <input/input_manager.h>
#include <system/application.h>
#include <input\sony_controller_input_manager.h>
#include <graphics/sprite_renderer.h>
#include <graphics/sprite.h>
#include "load_texture.h"
#include <graphics/font.h>
class OptionsState :
	public StateBase
{
public:
	OptionsState();
	~OptionsState();

	virtual StateBase::EStates Update(float frame_time);
	virtual void CleanUp();
	virtual void Render();
	virtual void Init();
	void DrawHUD();

private:
	gef::Texture* background_;
	gef::Texture* Yellow_Button_Text;


	gef::Sprite Yellow_Button_Sprite;
	gef::Sprite background_sprite;

	int menuChoice;


	// the float variable are used to setup the options menu UI
	float menu_options_space;
	float playbutton_space;
	float menu_button_space;
	float offsetValue = 20.f;
	float Y_text_offset_value = 0.20;

	// font colour 
	int font_color = 0xFF0000FF;

};

