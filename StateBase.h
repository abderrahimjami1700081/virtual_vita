#pragma once
#include "StateInfo.h"	
class PrimitiveBuilder;

namespace gef
{
	class SonyController;
	class Renderer3D;
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
}




class StateBase
{
public:
	StateBase();
	~StateBase();


// this enum is part of my state machine, it's used to switch between states
enum EStates
{
	MENU_STATE,
	SPLASH_SCREEN_STATE,
	OPTIONS_STATE,
	LEVEL1_STATE

};
	// I'm using virtual functions for the update, init, cleanUp and render to run different versions of them based on the state of my game
	virtual EStates Update(float frame_time) = 0;
	virtual void Init() = 0;
	virtual void CleanUp() = 0;
	virtual void Render() = 0;

};

