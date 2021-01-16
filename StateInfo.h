#pragma once

#include "../gef_abertay/graphics/sprite_renderer.h"
#include <input\sony_controller_input_manager.h>
#include "../gef_abertay/graphics/renderer_3d.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include "primitive_builder.h"
#include "input/keyboard.h"
#include "input/input_manager.h"
namespace gef
{
	class SonyController;
	class Renderer3D;
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
}

// this structure contains all the resources needed in my game
struct StateInitInfo
{
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::InputManager* input_manager_;
	PrimitiveBuilder* Primitive_Builder;
	gef::Renderer3D* renderer_3d_;
	
	gef::Platform &platform_;

	StateInitInfo(gef::Platform &_p) : platform_(_p)
	{
	};

	static void createPointer(gef::Platform &_p);

	static StateInitInfo* getInstance();
};