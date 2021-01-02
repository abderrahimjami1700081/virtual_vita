#include "Level1.h"
#include "StateInfo.h"
#include "system/platform.h"
#include "graphics/sprite_renderer.h"
#include <input/sony_controller_input_manager.h>
#include <input/input_manager.h>
#include "starter_app.h"
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/font.h>
#include <input/touch_input_manager.h>
#include <maths/vector2.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/renderer_3d.h>
#include <graphics/render_target.h>
#include <graphics/scene.h>

#include <input/input_manager.h>
//#include <sony_sample_framework.h>
//#include <sony_tracking.h>

//Virtual vita classes
#include "VirtualSystem.h"
#include "VirtualSonySample.h"
#include <vector>

bool Level1::sampleIsMarkerFound(int idx)
{
	return virtualSystem_->IsMarkerFound(idx);
}

void Level1::sampleGetTransform(int idx, gef::Matrix44* mat)
{
	virtualSystem_->GetMarkerTransform(idx, mat);
}



Level1::Level1() 
{
}


Level1::~Level1()
{
}

void Level1::Init()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	// Setup orthographic matrix 
	OrthoMatrix = stateInfo->platform_.OrthographicFrustum(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	ImageScaleFactor = (960.f / 544.f) / (640.f / 480.f);
	CameraFeedSprite.set_position(gef::Vector4(0.0f, 0.0f, 1.0f));
	CameraFeedSprite.set_width(2.f);
	CameraFeedSprite.set_height(2 * ImageScaleFactor);
	// Setup projection  matrix 
	gef::Matrix44 ScaleMatrix;
	ScaleMatrix.Scale(gef::Vector4(1.0f, ImageScaleFactor, 1.0f));
	//ProjectionMatrix = stateInfo->platform_.PerspectiveProjectionFov(SCE_SMART_IMAGE_FOV, SCE_SMART_IMAGE_WIDTH / (float)SCE_SMART_IMAGE_HEIGHT, .1f, 100.f);

	ProjectionMatrix = ProjectionMatrix * ScaleMatrix;

	SetUpLights();

	virtualSystem_ = VirtualSystem::Create();
	virtualSystem_->Init(stateInfo->Primitive_Builder);




	//// initialise sony framework
	//sampleInitialize();
	//smartInitialize();

	//// reset marker tracking
	//AppData* dat = sampleUpdateBegin();
	//smartTrackingReset();
	//sampleUpdateEnd(dat);


	//Create Cube
	//cube.set_mesh(primitive_builder_->CreateBoxMesh(gef::Vector4(0.0295f, 0.0295f, 0.0295f), gef::Vector4(0.0f, 0.0f, 0.0f)));
	cube.set_mesh(stateInfo->Primitive_Builder->CreateBoxMesh(gef::Vector4(.015f, .015f, .015f), gef::Vector4(0.0f, 0.0f, 0.0f)));

	Cube_GameObject.set_mesh(stateInfo->Primitive_Builder->CreateBoxMesh(gef::Vector4(.015f, .015f, .015f), gef::Vector4(0.0f, 0.0f, 0.0f)));
	SecondCube_GameObject.set_mesh(stateInfo->Primitive_Builder->CreateBoxMesh(gef::Vector4(.015f, .015f, .015f), gef::Vector4(0.0f, 0.0f, 0.0f)));
	ThirdCube_GameObject.set_mesh(stateInfo->Primitive_Builder->CreateBoxMesh(gef::Vector4(.015f, .015f, .015f), gef::Vector4(0.0f, 0.0f, 0.0f)));

	//////////////////////////
	enemy.SetPrimitivePtr(stateInfo->Primitive_Builder);
	enemy.Init();
	//////////////////////////

	wallCubeHalfSize = .005f;
	for (size_t i = 0; i < 10; i++)
	{
		cubes[i].set_mesh(stateInfo->Primitive_Builder->CreateBoxMesh(gef::Vector4(wallCubeHalfSize, wallCubeHalfSize, wallCubeHalfSize), gef::Vector4(0.0f, 0.0f, 0.0f)));
	}


	///////////////
	//Tower Init 

	tower = new Tower01(stateInfo->Primitive_Builder, stateInfo->renderer_3d_);
	isTowerSphereColliding = false;


	isMarker1Found = false;
	lerpAmount = 0;
	isLocalTransformInit = false;
	areBoxesColliding = false;
	hasPosBeenSet = false;





}





StateBase::EStates Level1::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	AppData* dat = sampleUpdateBegin();
	// use the tracking library to try and find markers
	smartUpdate(dat->currentImage);
	//for (int i = 0; i < 6; i++)
	//{

	//	if (sampleIsMarkerFound(i))
	//	{
	//		if (i == 0)
	//		{


	//			gef::Matrix44 markerTransform;
	//			sampleGetTransform(i, &markerTransform);
	//			gef::Matrix44 /*ScaleMatrix, ScaleMatrix2,*/ translationMatrix;
	//			translationMatrix.SetIdentity();
	//			//ScaleMatrix2.SetIdentity();
	//			//ScaleMatrix.SetIdentity();
	//			//ScaleMatrix.Scale(gef::Vector4(0.001f, 0.001f, 0.001f));
	//			//ScaleMatrix.SetIdentity();
	//			//ScaleMatrix = ScaleMatrix * markerTransform;
	//			//importedModelInstance_.set_transform(ScaleMatrix);
	//			//ScaleMatrix2.Scale(gef::Vector4(0.1f, 0.1f, 0.1f));
	//			//translationMatrix.SetTranslation(gef::Vector4(0.0f, 0.0f, 0.2f));
	//			translationMatrix.Scale(gef::Vector4(2.0f, 2.0f, 2.0f));
	//			translationMatrix =/* ScaleMatrix2 **/ translationMatrix * markerTransform;
	//			cube.set_transform(translationMatrix);
	//			//importedModelMesh_->aabb();
	//			//importedModelInstance_.set_transform(ScaleMatrix);


	//			//Multiply cube_GameObject local transform by markerTransform
	//			Cube_GameObject.localTransform_ = Cube_GameObject.localTransform_ * markerTransform;
	//			//Move it along the X
	//		
	//			Cube_GameObject.set_transform(Cube_GameObject.localTransform_);
	//		}

	//		if (i == 3)
	//		{
	//			gef::Matrix44 markerTransform;
	//			sampleGetTransform(i, &markerTransform);

	//			SecondCube_GameObject.localTransform_ = SecondCube_GameObject.localTransform_ * markerTransform;
	//			SecondCube_GameObject.set_transform(SecondCube_GameObject.localTransform_);
	//		}

	//		// //read input devices
	//		//if (input_manager_)
	//		//{
	//		//	input_manager_->Update();
	//		//	// controller input
	//		//	gef::SonyControllerInputManager* controller_manager = input_manager_->controller_input();
	//		//	if (controller_manager)
	//		//	{
	//		//		const gef::SonyController* controller = controller_manager->GetController(0);
	//		//		if (controller)
	//		//		{
	//		//			float left_x_axis = controller->left_stick_x_axis();
	//		//			float left_y_axis = controller->left_stick_y_axis();
	//		//			if (left_x_axis < 0)
	//		//			{
	//		//				Cube_GameObject.position_.set_x(Cube_GameObject.position_.x() - .01f);
	//		//			}
	//		//			if (left_y_axis < 0)
	//		//			{
	//		//				Cube_GameObject.position_.set_y(Cube_GameObject.position_.y() + .01f);
	//		//			}
	//		//			if (left_x_axis > 0)
	//		//			{
	//		//				Cube_GameObject.position_.set_x(Cube_GameObject.position_.x() + .01f);
	//		//			}
	//		//			if (left_y_axis > 0)
	//		//			{
	//		//				Cube_GameObject.position_.set_y(Cube_GameObject.position_.y() - .01f);
	//		//			}
	//		//		}
	//		//	}
	//		//}	

	//	}


	//}
	gef::Matrix44 marker2Transform;		 // Marker 2 transform
	gef::Matrix44 markerTransform;

	if (sampleIsMarkerFound(0))
	{
		sampleGetTransform(0, &markerTransform);		// Marker 1 transform
		//cube.set_transform(markerTransform);
		//Multiply cube_GameObject local transform by markerTransform
		Cube_GameObject.localTransform_ = Cube_GameObject.localTransform_ * markerTransform;
		//Cube_GameObject.position_ = gef::Vector4(.3f, 0.0f, 0.0f);
		Cube_GameObject.set_transform(Cube_GameObject.localTransform_);
		Cube_GameObject.Update(frame_time);
		
		// Place second game object relative to first marker 
		//SecondCube_GameObject.localTransform_ = Cube_GameObject.localTransform_ * markerTransform;
		//Set Second cube transform to be relative to the first marker transform
		SecondCube_GameObject.localTransform_ = SecondCube_GameObject.localTransform_ * markerTransform;
		SecondCube_GameObject.set_transform(SecondCube_GameObject.localTransform_);
		SecondCube_GameObject.Update(frame_time);
		SecondCube_GameObject.position_ = gef::Vector4(0.1, 0.1f, 0.0f);


		//Third Cube 
		//Set Third cube to be relative to first marker 
		ThirdCube_GameObject.localTransform_ = ThirdCube_GameObject.localTransform_ * markerTransform;
		ThirdCube_GameObject.set_transform(ThirdCube_GameObject.localTransform_);
		ThirdCube_GameObject.Update(frame_time);
		ThirdCube_GameObject.position_ = gef::Vector4(0.2f, 0.0f,0.0f);

		lerpAmount += frame_time * .10f;
		if (lerpAmount > 1.f)
		{
			lerpAmount = 1;
		}

		//MovingCube_GameObject.position_.Lerp(gef::Vector4(0.0f, 0.0f, 0.0f), SecondCube_GameObject.localTransform_.GetTranslation(), lerpAmount);
		//MovingCube_GameObject.Update(frame_time);
		//MovingCube_GameObject.set_transform(MovingCube_GameObject.localTransform_ * markerTransform);




		/////////////////
		// -------- Enemy Code
		enemy.localTransform_ = enemy.localTransform_ * markerTransform;
		enemy.SetMarkerTransform(markerTransform);
		enemy.Update(frame_time);

		/////////////////

		/////// Setup Map Wall 
		SetUpMapWalls(markerTransform, frame_time);

		isMarker1Found = true;

	}


	if (sampleIsMarkerFound(1))
	{
		sampleGetTransform(1, &marker2Transform);		// Marker 2 transform
		tower->SetMarkerTransform(marker2Transform);
		tower->GetBullet()->SetMarkerTransform(marker2Transform);
		tower->Update(frame_time);
		tower->GetBullet()->Update(frame_time);
		if (IsCollidingAABB(tower->GetSphereColliderMesh(), enemy))
		{
			//If enemy found face it
			tower->FollowCube(enemy.localTransform_ * markerTransform);
			isTowerSphereColliding = true;

			// call shoot function
			if (IsCollidingAABB(enemy, *tower->GetBullet()))
			{
				tower->GetBullet()->velocity_ = gef::Vector4(0.0f, 0.0f, 0.0f);
			}
			else
				tower->ShootProjectile(enemy.localTransform_ * markerTransform);


		}
		else
		{
			isTowerSphereColliding = false;
		}

	}

	//dynamicsWorld->stepSimulation(frame_time);


	sampleUpdateEnd(dat);

	// Check for collision
	if (IsCollidingAABB(Cube_GameObject, SecondCube_GameObject))
	{
		areBoxesColliding = true;
	}
	else
	{
		areBoxesColliding = false;
	}


	return StateBase::LEVEL1;
}

void Level1::CleanUp()
{
	//smartRelease();
	//sampleRelease();

}

void Level1::Render()
{

}


void Level1::SetUpLights()
{
	StateInitInfo* stateInfo = StateInitInfo::getInstance();

	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));

	gef::Default3DShaderData& default_shader_data = stateInfo->renderer_3d_->default_shader_data();
	default_shader_data.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
	default_shader_data.AddPointLight(default_point_light);

}

bool Level1::IsCollidingAABB(const gef::MeshInstance & meshInstance1_, const gef::MeshInstance & meshInstance2_)
{
	gef::Aabb Aabb1 = meshInstance1_.mesh()->aabb();
	gef::Aabb Aabb2 = meshInstance2_.mesh()->aabb();

	gef::Aabb Aabb1_t = Aabb1.Transform(meshInstance1_.transform());
	gef::Aabb Aabb2_t = Aabb2.Transform(meshInstance2_.transform());

	if (Aabb1_t.max_vtx().x() > Aabb2_t.min_vtx().x() &&
		Aabb1_t.min_vtx().x() < Aabb2_t.max_vtx().x() &&
		Aabb1_t.max_vtx().y() > Aabb2_t.min_vtx().y() &&
		Aabb1_t.min_vtx().y() < Aabb2_t.max_vtx().y() &&
		Aabb1_t.max_vtx().z() > Aabb2_t.min_vtx().z() &&
		Aabb1_t.min_vtx().z() < Aabb2_t.max_vtx().z()
		)
	{
		return true;
	}

	return false;

}

void Level1::SetUpMapWalls(gef::Matrix44 markerTranform, float frameTime)
{
	for (size_t i = 0; i < 10; i++)
	{
		cubes[i].localTransform_ = cubes[i].localTransform_ * markerTranform;
		if (i < 5)
		{
			cubes[i].position_ = gef::Vector4(i * (wallCubeHalfSize * 2 * 8.f), 0.1f, 0.0f);
			cubes[i].scale_ = gef::Vector4(8.0f, 2.0f, 2.0f);
			cubes[i].Update(frameTime);
			cubes[i].set_transform(cubes[i].localTransform_ * markerTranform);
		}
		else if (i >= 5)
		{
			cubes[i].position_ = gef::Vector4(5 * (wallCubeHalfSize * 2), i * (wallCubeHalfSize * 2 * 8.f), 0.0f);
			cubes[i].scale_ = gef::Vector4(2.0f, 8.0f, 2.0f);
			cubes[i].Update(frameTime);
			cubes[i].set_transform(cubes[i].localTransform_ * markerTranform);

		}
	}


}
