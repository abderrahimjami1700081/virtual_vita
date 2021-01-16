#pragma once
#include "GameObjectMy.h"
#include "primitive_builder.h"
#include <maths/sphere.h>
#include <vector>
#include "TowerProjectile.h"
#include <graphics/renderer_3d.h>
class Tower01 :
	public GameObjectMy
{
public:
	Tower01(PrimitiveBuilder* primBuild, gef::Renderer3D* Renderer_3d_);
	~Tower01();

	void SetMarkerTransform(gef::Matrix44 markerTransform_) { markerTranform = markerTransform_; }
	void Update(float frameTime);
	gef::MeshInstance GetSphereColliderMesh() { return sphereCollider; }
	void ShootProjectile(gef::Matrix44 globalTargetTransform, gef::Vector4 TargetVelocity);
	void FollowCube(gef::Matrix44 targetPos);
	TowerProjectile* GetBullet() { return bullet; }
	gef::Vector4 getBulletEnemyDistVector() { return bulletEnemyDistVector; }

private:
	PrimitiveBuilder * primitiveBuilder;
	gef::Matrix44 markerTranform;
	float towerCubeHalfSize;
	GameObjectMy sphereCollider;
	TowerProjectile* bullet;
	gef::Vector4 bulletEnemyDistVector;

};

