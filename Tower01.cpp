#include "Tower01.h"
#include <math.h>
#include <maths\sphere.h>
#include <maths/math_utils.h>

Tower01::Tower01(PrimitiveBuilder * primBuild, gef::Renderer3D* Renderer_3d_):
	primitiveBuilder(primBuild)
{	

	towerCubeHalfSize = .015f;
	set_mesh(primitiveBuilder->CreateBoxMesh(gef::Vector4(towerCubeHalfSize, towerCubeHalfSize, towerCubeHalfSize), gef::Vector4(0.0f, 0.0f, 0.0f)));
	/*sphereCollider.set_mesh(primitiveBuilder->GetDefaultSphereMesh());*/
	sphereCollider.set_mesh(primitiveBuilder->CreateSphereMesh(.10, 20, 20));

	bullet = new TowerProjectile(primitiveBuilder, Renderer_3d_);

}


Tower01::~Tower01()
{
	delete primitiveBuilder;
	primitiveBuilder = NULL;

}

void Tower01::Update(float frameTime)
{
	localTransform_ = localTransform_ * markerTranform;
	//position_ = gef::Vector4(.1f, -.1f, 0.0f);
	GameObjectMy::Update(frameTime);
	set_transform(localTransform_ * markerTranform);
	

	//Update for the sphereColliderGameObject
	sphereCollider.localTransform_ = sphereCollider.localTransform_ * markerTranform;
	sphereCollider.Update(frameTime);
	sphereCollider.set_transform(sphereCollider.localTransform_ * markerTranform);

	




}

void Tower01::ShootProjectile(gef::Matrix44 globalTargetTransform)
{
	gef::Matrix44 InverseOfMarkerTransform, temp3;
	InverseOfMarkerTransform.AffineInverse(markerTranform);
	temp3 = globalTargetTransform * InverseOfMarkerTransform;
	gef::Vector4 distVector = temp3.GetTranslation(); 
	gef::Vector4 BulletPosition = bullet->position_;
	bulletEnemyDistVector = globalTargetTransform.GetTranslation() - BulletPosition;
	if (bulletEnemyDistVector.Length() < 0.001f)
	{
		bullet->position_ = gef::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		distVector.Normalise();
		bullet->velocity_ = distVector * 0.4f;

	}
	





}

void Tower01::FollowCube(gef::Matrix44 globalTargetTransform)
{
	// Calculate inverse of towerTransform 
	gef::Matrix44 InverseOfMarkerTransform, temp3;
	InverseOfMarkerTransform.AffineInverse(markerTranform);
	temp3 = globalTargetTransform * InverseOfMarkerTransform;
	
	gef::Vector4 angleVector = temp3.GetTranslation();

	//gef::Vector4 tempRotationVector = temp.GetTranslation();
	float angle = atan2(angleVector.y(), angleVector.x());
	angle = gef::RadToDeg(angle);
	rotationZ_ = angle;




}


