#pragma once
#include "StateBase.h"
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <graphics/mesh_instance.h>
#include <system/debug_log.h>
//#include "Camera.h"
#include <graphics/font.h>
#include "load_texture.h"
#include <graphics/sprite_renderer.h>
#include <graphics/sprite.h>
#include <system/application.h>
#include <maths/vector2.h>
#include <vector>

#include <platform/vita/graphics/texture_vita.h>
#include "primitive_builder.h"
#include "GameObjectMy.h"

#include "Enemy.h"
#include "Tower01.h"

// Vita AR includes
//#include <camera.h>
//#include <gxm.h>
//#include <motion.h>
//#include <libdbg.h>
//#include <libsmart.h>

namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class RenderTarget;
	//class TextureVita;
	class InputManager;
	class Scene;

}

class VirtualSystem;


class Level1 :
	public StateBase
{

public:
	Level1();
	~Level1();

	virtual StateBase::EStates Update(float frame_time);
	virtual void CleanUp();
	virtual void Render();
	virtual void Init();
	void SetUpLights();
private:
	bool IsCollidingAABB(const gef::MeshInstance& meshInstance1_, const gef::MeshInstance& meshInstance2_);
	void RenderOverlay();
	void SetUpMapWalls(gef::Matrix44 markerTranform, float frameTime);
	void ReadSceneAndAssignFistMesh(const char* filename_, gef::Scene** scene_, gef::Mesh** mesh_);
	gef::Mesh* GetFirstMesh(gef::Scene* scene);
	bool sampleIsMarkerFound(int idx);
	void sampleGetTransform(int idx, gef::Matrix44* mat);


	gef::Matrix44 OrthoMatrix;
	gef::Matrix44 ProjectionMatrix;
	float ImageScaleFactor;

	gef::Sprite CameraFeedSprite;
	//gef::TextureVita TextureCameraMap;

	GameObjectMy Cube_GameObject;
	GameObjectMy SecondCube_GameObject;
	GameObjectMy ThirdCube_GameObject;

#ifndef _NUMWAYPOINTS
#define _NUMWAYPOINTS 10
#endif // _NUMWAYPOINTS
	Enemy enemy;

	///////////////////
	// ----- MAP WALLS ---------
	GameObjectMy cubes[20];
	bool hasPosBeenSet;
	float wallCubeHalfSize;

	//////////////////

	Tower01* tower;
	bool isTowerSphereColliding;
	// mesh instance 
	gef::MeshInstance cube;
	float fps_;

	//Mesh instance  
	gef::MeshInstance importedModelInstance_;
	class gef::Mesh* importedModelMesh_;

	gef::Scene* model_scene_;


	bool isMarkerFound;
	bool areBoxesColliding;

	float lerpAmount;
	bool isLocalTransformInit;

	bool isMarker1Found;

	//Virtual Vita
	VirtualSystem* virtualSystem_;

};

