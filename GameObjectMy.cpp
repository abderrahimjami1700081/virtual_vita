#include "GameObjectMy.h"
#include <maths/math_utils.h>



GameObjectMy::GameObjectMy()
{
	Init();
}


GameObjectMy::~GameObjectMy()
{
}

void GameObjectMy::Init()
{
	velocity_ = gef::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	position_ = gef::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	rotationX_ = 0.0f;
	rotationY_ = 0.0f;
	rotationZ_ = 0.0f;

	localTransform_.SetIdentity();

	scale_ = { 1.0f, 1.0f, 1.0f };
}

bool GameObjectMy::Update(float frame_time)
{
	position_ += velocity_ * frame_time;
	BuildTransformationMatrix();
	return true;
}



gef::Matrix44 GameObjectMy::BuildRotationX(float RadAngle_)
{
	gef::Matrix44 rotation;
	rotation.SetIdentity();
	rotation.RotationX(gef::DegToRad(RadAngle_));
	return rotation;
}

gef::Matrix44 GameObjectMy::BuildRotationY(float RadAngle_)
{
	gef::Matrix44 rotation;
	rotation.SetIdentity();
	rotation.RotationY(gef::DegToRad(RadAngle_));
	return rotation;
}

gef::Matrix44 GameObjectMy::BuildRotationZ(float RadAngle_)
{
	gef::Matrix44 rotation;
	rotation.SetIdentity();
	rotation.RotationZ(gef::DegToRad(RadAngle_));
	return rotation;
}

gef::Matrix44 GameObjectMy::BuildScale(gef::Vector4 scale)
{
	gef::Matrix44 Scale;
	Scale.SetIdentity();
	Scale.Scale(scale);
	return Scale;

}

gef::Matrix44 GameObjectMy::BuildTranslate(gef::Vector4 tranlate)
{
	gef::Matrix44 Trans;
	Trans.SetIdentity();
	Trans.SetTranslation(tranlate);
	return Trans;
}

void GameObjectMy::BuildTransformationMatrix()
{
	gef::Matrix44 rotation_X,
		rotation_Y,
		rotation_Z,
		Scaleing,
		translate;

	Scaleing = BuildScale(scale_);
	rotation_X = BuildRotationX(rotationX_);
	rotation_Y = BuildRotationY(rotationY_);
	rotation_Z = BuildRotationZ(rotationZ_);
	translate = BuildTranslate(position_);

	localTransform_= Scaleing * rotation_X * rotation_Y * rotation_Z * translate;
}


