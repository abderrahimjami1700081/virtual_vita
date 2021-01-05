#include "starter_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/font.h>
#include <graphics/scene.h>
#include <maths/vector2.h>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include <maths/math_utils.h>
#include <graphics/renderer_3d.h>

//#include "VirtualSystem.h"
//#include "VirtualSonySample.h"
//#include <vector>
#include <assert.h>
StarterApp::StarterApp(gef::Platform& platform) :
	Application(platform),
	//sprite_renderer_(NULL),
	//font_(NULL),
	//renderer_3d_(NULL),
	//input_manager_(NULL),
	primitive_builder_(NULL)
{
	StateInitInfo::createPointer(platform);

	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	stateInfo->sprite_renderer_ = NULL;
	stateInfo->input_manager_ = NULL;
	stateInfo->font_ = NULL;


}


//bool  StarterApp::sampleIsMarkerFound ( int idx )
//{
//	return virtualSystem_->IsMarkerFound(idx);
//}
//
//void StarterApp::sampleGetTransform ( int idx, gef::Matrix44* mat )
//{
//	virtualSystem_->GetMarkerTransform ( idx, mat );
//}

void StarterApp::Init()
{

	// Initialize all the resouses in my struct 
	// SPRITE RENDERER
	StateInitInfo* stateInfo = StateInitInfo::getInstance();
	stateInfo->sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	stateInfo->platform_ = platform_;
	// 3D RENDERER
	stateInfo->renderer_3d_ = gef::Renderer3D::Create(platform_);

	// FONT
	stateInfo->font_ = new gef::Font(platform_);
	stateInfo->font_->Load("comic_sans");

	// INPUT MANAGER
	stateInfo->input_manager_ = gef::InputManager::Create(platform_);
	stateInfo->Primitive_Builder = new PrimitiveBuilder(platform_);



	//////////////////////////


// INITIALIZE GAME STATE MACHINE
	Current_State = &Splash_Screen_State;
	// call the init for the current state 
	Current_State->Init();


	//////////////////////////












	//sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	//renderer_3d_ = gef::Renderer3D::Create(platform_);
	//input_manager_ = gef::InputManager::Create(platform_);
	//primitive_builder_ = new PrimitiveBuilder ( platform_ );

	//InitFont();
	//SetupCamera();
	//SetupLights();

	//virtualSystem_ = VirtualSystem::Create ();
	//virtualSystem_->Init (stateInfo->Primitive_Builder);

	////////////////////////////////////////////////////////////
	// GAME LOGIC //////////////

	testObject_ = new GameObjectMy;
	testObject_->position_ = gef::Vector4 ( 0.0f, 0.0f, 0.0f );
	//testObject_->scale_ = gef::Vector4 ( 0.05f, 0.05f, 0.05f );
	testObject_->scale_ = gef::Vector4 ( 1.0f, 1.0f, 1.0f );
	//testObject_->set_mesh ( primitive_builder_->GetDefaultCubeMesh () );
	testObject_->set_mesh (stateInfo->Primitive_Builder->CreateBoxMesh ( gef::Vector4 ( 0.059f, 0.059f, 0.001f ), gef::Vector4 ( 0.0f, 0.0f, 0.0f ) ) );

	////////////////////////////////////////////////////////////
	//// initialise sony framework
	//sampleInitialize ();
	//smartInitialize ();

	//// reset marker tracking
	//AppData* dat = sampleUpdateBegin ();
	//smartTrackingReset ();
	//sampleUpdateEnd ( dat );

	///////////////////////////////////////////////////////



}


void StarterApp::CleanUp()
{
	////////////////////////////////////////////////////////////
	//smartRelease ();
	//sampleRelease ();

	////////////////////////////////////////////////////////////
	// GAME LOGIC //////////////
	delete testObject_;
	testObject_ = NULL;


	//////////////////////////////////////////////////////////

	//virtualSystem_->CleanUp ();
	//delete virtualSystem_;
	//virtualSystem_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	CleanUpFont();

	//delete input_manager_;
	//input_manager_ = NULL;

	//delete sprite_renderer_;
	//sprite_renderer_ = NULL;

	//delete renderer_3d_;
	//renderer_3d_ = NULL;


	////////////////
// Menu state code

	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	delete stateInfo->input_manager_;
	stateInfo->input_manager_ = NULL;


	delete stateInfo->sprite_renderer_;
	stateInfo->sprite_renderer_ = NULL;

	delete stateInfo->renderer_3d_;
	stateInfo->renderer_3d_ = NULL;

	delete stateInfo->font_;
	stateInfo->font_ = NULL;


	delete stateInfo->Primitive_Builder;
	stateInfo->Primitive_Builder = NULL;



	// Call to the cleanUp function of the current state
	Current_State->CleanUp();





}

bool StarterApp::Update(float frame_time)
{
	//fps_ = 1.0f / frame_time;
	//// read input devices
	//if (input_manager_)
	//{
	//	input_manager_->Update ();

	//	// controller input
	//	gef::SonyControllerInputManager* controller_manager = input_manager_->controller_input ();
	//	if (controller_manager)
	//	{
	//	}

	//	// keyboard input
	//	gef::Keyboard* keyboard = input_manager_->keyboard ();
	//	virtualSystem_->ProcessKeyboardInput ( keyboard, frame_time );
	//}

	//virtualSystem_->Update ( frame_time );

	////////////////////////////////////////////////////////////
	//AppData* dat = sampleUpdateBegin ();

	//// use the tracking library to try and find markers
	//smartUpdate ( dat->currentImage );
	//sampleUpdateEnd ( dat );
		
	////////////////////////////////////////////////////////////
	// GAME LOGIC //////////////

	//// check to see if a particular marker can be found
	//if (sampleIsMarkerFound ( 0 ))
	//{
	//	// marker is being tracked, get its transform
	//	gef::Matrix44 marker_transform;
	//	sampleGetTransform (
	//		0,
	//		&marker_transform );

	//	// set the transform of the 3D mesh instance to draw on
	//	// top of the marker
	//	gef::Matrix44 trans = marker_transform;

	//	gef::Matrix44 scale;
	//	scale.Scale ( gef::Vector4 (0.1f, 0.1f, 0.1f ) );
	//	gef::Vector4 position = trans.GetTranslation ();
	//	position.set_y ( position.y () + 0.15f );
	//	trans = scale * trans;
	//	trans.SetTranslation ( position );


	//	testObject_->set_transform ( trans );

	//}

	//for (int i = 0; i < 6; i++)
	//{
	//	if (sampleIsMarkerFound ( i ))
	//	{
	//		// marker is being tracked, get its transform
	//		gef::Matrix44 marker_transform;
	//		sampleGetTransform ( i, &marker_transform );
	//		// set the transform of the 3D mesh instance to draw on
	//		// top of the marker
	//		gef::Vector4 position = marker_transform.GetTranslation ();
	//		position.set_y ( position.y () + 0.10f );
	//		marker_transform.SetTranslation ( position );

	//		testObject_->set_transform ( marker_transform );
	//	}
	//}



	//////////////////////////////////////////////////////////


	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	// Updating the input manager
	stateInfo->input_manager_->Update();

	UpdateGameStateMachine(frame_time);
	return true;


	return true;
}

void StarterApp::Render()
{
	////////////////////////////////////////////////////////////
	//AppData* dat = sampleRenderBegin ();

	//gef::Matrix44 projection_matrix;

	//projection_matrix = platform_.PerspectiveProjectionFov(camera_fov_, (float)platform_.width() / (float)platform_.height(), near_plane_, far_plane_);
	//renderer_3d_->set_projection_matrix(projection_matrix);

	//// draw meshes here
	//renderer_3d_->Begin();
	//virtualSystem_->Render ( renderer_3d_ );

	//gef::Matrix44 view_matrix;
	//view_matrix.SetIdentity ();
	//renderer_3d_->set_view_matrix ( view_matrix );

	//////////////////////////////////////////////////////////////
	//// GAME LOGIC //////////////


	//renderer_3d_->DrawMesh ( *testObject_ );

	//////////////////////////////////////////////////////////////


	//renderer_3d_->End();

	//// setup the sprite renderer, but don't clear the frame buffer
	//// draw 2D sprites here
	//sprite_renderer_->Begin(false);
	//DrawHUD();
	//sprite_renderer_->End();



	//sampleRenderEnd ();
	////////////////////////////////////////////////////////////

	Current_State->Render();



}
void StarterApp::InitFont()
{
	//font_ = new gef::Font(platform_);
	//font_->Load("comic_sans");
}

void StarterApp::CleanUpFont()
{
	//delete font_;
	//font_ = NULL;
}

void StarterApp::DrawHUD()
{
	//if(font_)
	//{
	//	// display frame rate
	//	font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	//	
	//}
}

void StarterApp::SetupLights()
{
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));

	//gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();
	//default_shader_data.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
	//default_shader_data.AddPointLight(default_point_light);
}

void StarterApp::SetupCamera()
{
	// initialise the camera settings
	camera_eye_ = gef::Vector4(5.0f, 5.0f, 215.0f);
	camera_lookat_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_fov_ = gef::DegToRad(45.0f);
	near_plane_ = 0.01f;
	far_plane_ = 100.f;
}

void StarterApp::UpdateCamera ()
{
	// initialise the camera settings
	camera_eye_ = gef::Vector4 ( 1.5f, 1.0f, 1.5f );
	camera_lookat_ = gef::Vector4 ( 0.0f, 0.0f, 0.0f );
	camera_up_ = gef::Vector4 ( 0.0f, 1.0f, 0.0f );
	camera_fov_ = gef::DegToRad ( 45.0f );
	near_plane_ = 0.01f;
	far_plane_ = 1000.f;
}

gef::Mesh* StarterApp::GetFirstMesh ( gef::Scene* scene )
{
	gef::Mesh* mesh = NULL;

	if (scene)
	{
		// now check to see if there is any mesh data in the file, if so lets create a mesh from it
		if (scene->mesh_data.size () > 0)
			mesh = scene->CreateMesh ( platform_, scene->mesh_data.front () );
	}

	return mesh;
}


void StarterApp::ReadSceneAndAssignFirstMesh ( const char* filename, gef::Scene** scene, gef::Mesh** mesh )
{
	gef::Scene* scn = new gef::Scene;
	scn->ReadSceneFromFile ( platform_, filename );

	// we do want to render the data stored in the scene file so lets create the materials from the material data present in the scene file
	scn->CreateMaterials ( platform_ );

	*mesh = GetFirstMesh ( scn );
	*scene = scn;
}

bool StarterApp::IsColliding_SphereToSphere ( const gef::MeshInstance& meshInstance1, const gef::MeshInstance& meshInstance2 )
{
	gef::Sphere sphere1 = meshInstance1.mesh ()->bounding_sphere ();
	gef::Sphere sphere2 = meshInstance2.mesh ()->bounding_sphere ();

	gef::Sphere sphere1_transformed = sphere1.Transform ( meshInstance1.transform () );
	gef::Sphere sphere2_transformed = sphere2.Transform ( meshInstance2.transform () );

	gef::Vector4 offset = sphere1_transformed.position () - sphere2_transformed.position ();
	float distance = sqrtf(offset.x() * offset.x() + offset.y() * offset.y() + offset.z() * offset.z());
	float combined_radii = sphere1_transformed.radius () + sphere2_transformed.radius ();

	return distance < combined_radii;
}


bool StarterApp::IsColliding_AABBToAABB ( const gef::MeshInstance& meshInstance1, const gef::MeshInstance& meshInstance2 )
{
	gef::Aabb Aabb1 = meshInstance1.mesh ()->aabb ();
	gef::Aabb Aabb2 = meshInstance2.mesh ()->aabb ();

	gef::Aabb Aabb1_t = Aabb1.Transform ( meshInstance1.transform () );
	gef::Aabb Aabb2_t = Aabb2.Transform ( meshInstance2.transform () );

	if (Aabb1_t.max_vtx ().x () > Aabb2_t.min_vtx ().x () &&
		Aabb1_t.min_vtx ().x () < Aabb2_t.max_vtx ().x () &&
		Aabb1_t.max_vtx ().y () > Aabb2_t.min_vtx ().y () &&
		Aabb1_t.min_vtx ().y () < Aabb2_t.max_vtx ().y () &&
		Aabb1_t.max_vtx ().z () > Aabb2_t.min_vtx ().z () &&
		Aabb1_t.min_vtx ().z () < Aabb2_t.max_vtx ().z ()
		)
	{
		return true;
	}

	return false;

}


StateBase * StarterApp::getState(StateBase::EStates stateEnum)
{
	/// This function returns the instance of the class that corresponds to the enum being passed 
	switch (stateEnum)
	{
	case StateBase::EStates::MENU_STATE:
		return &Menu_State;
	case StateBase::EStates::SPLASH_SCREEN_STATE:
		return &Splash_Screen_State;
	case StateBase::EStates::OPTIONS_STATE:
		return &OptionsState;
	case StateBase::EStates::LEVEL1_STATE:
		return &Level1State;

		break;
	default:
		assert(false && "add a new state to the SceneApp::getState function");
		break;
	}
}



/// This function updates the state machine, 
/// the update function of the current state returns an enum that is passed to the getState function
/// which returns the new state,
/// if the new state is different than the current state, the function calls the cleanup for the old state,
/// changes the currentState to be equal to the newState and finally calls the init for the current state 
void StarterApp::UpdateGameStateMachine(float frame_time)
{
	StateBase::EStates newStateEnum = Current_State->Update(frame_time);
	StateBase *newState = getState(newStateEnum);

	if (newState != Current_State)
	{
		Current_State->CleanUp();
		Current_State = newState;
		Current_State->Init();
	}
}
