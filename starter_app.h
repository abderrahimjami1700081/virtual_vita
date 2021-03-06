#ifndef _STARTER_APP_H
#define _STARTER_APP_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector2.h>
#include <maths/vector4.h>
#include <maths/matrix44.h>
#include <vector>
#include <graphics/mesh_instance.h>
#include "primitive_builder.h"
#include "GameObjectMy.h"


//Bullet Includes
#include "Enemy.h"
#include "Tower01.h"

//Menu includes
#include "StateBase.h"
#include "SplashScreenState.h"
#include "StateMenu.h"
#include "OptionsState.h"
#include "Level1.h"


// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class InputManager;
	class Scene;
	class Keyboard;
}

class VirtualSystem;

class StarterApp : public gef::Application
{
public:
	StarterApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();
	void SetupCamera();
	void AdvanceControl ();
	void ProcessKeyboardInput ( gef::Keyboard* keyboard, float frame_time );
	bool sampleIsMarkerFound ( int idx );
	void sampleGetTransform ( int idx, gef::Matrix44* mat );
	void UpdateCamera ();

	gef::Mesh* GetFirstMesh ( gef::Scene* scene );
	void ReadSceneAndAssignFirstMesh ( const char* filename, gef::Scene** scene, gef::Mesh** mesh );
	bool IsColliding_SphereToSphere ( const gef::MeshInstance& meshInstance1, const gef::MeshInstance& meshInstance2 );
	bool IsColliding_AABBToAABB ( const gef::MeshInstance& meshInstance1, const gef::MeshInstance& meshInstance2 );

	//gef::SpriteRenderer* sprite_renderer_;
	//gef::Renderer3D* renderer_3d_;
	//gef::InputManager* input_manager_;
	//gef::Font* font_;

	float fps_;

	gef::Vector4 camera_eye_;
	gef::Vector4 camera_lookat_;
	gef::Vector4 camera_up_;
	float camera_fov_;
	float near_plane_;
	float far_plane_;

	GameObjectMy* testObject_;


	VirtualSystem* virtualSystem_;

	bool isColliding;

	PrimitiveBuilder* primitive_builder_;
	////// Menu State //////

	StateBase *Current_State;
	StateBase *getState(StateBase::EStates stateEnum);
	SplashScreenState Splash_Screen_State;
	StateMenu Menu_State;
	OptionsState OptionsState;
	Level1 Level1State;
	void UpdateGameStateMachine(float frame_time);


};

#endif // _STARTER_APP_H
