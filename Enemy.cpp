#include "Enemy.h"


Enemy::Enemy()
{


	//////////////////////////
	currentWaypoint = 0;
	NextWaypoint = 1;
	markerTransform.SetIdentity();

	//////////////////////////
	timer = 0.0f;
	SetWaypointPos();

}



Enemy::~Enemy()
{
}

void Enemy::Init()
{
	set_mesh(primitiveBuilder_->CreateBoxMesh(gef::Vector4(.025f, .025f, .025f), gef::Vector4(0.0f, 0.0f, 0.0f)));

}

void Enemy::Update(float frame_time)
{
	timer += frame_time;


	SetWaypointPos();

	CalculateDistance(frame_time);
	if (distanceMovingObj.Length() > temp.Length())
	{
		velocity_ = gef::Vector4(0.0f, 0.0f, 0.0f);
		if (timer > 2.f)
		{
			if (NextWaypoint < _NUMWAYPOINTS - 1)
			{
				currentWaypoint++;
				NextWaypoint++;
			}
		}

	}


	GameObjectMy::Update(frame_time);
	set_transform(localTransform_ * markerTransform);



}

void Enemy::SetWaypointPos()
{
	for (size_t i = 0; i < _NUMWAYPOINTS; i++)
	{

		waypoints[i].position_ = gef::Vector4(i * 0.1f, 0.0f, 0.0f);
		switch (i)
		{
		case 1:
			waypoints[i].position_ = gef::Vector4(i * 0.1f, 0.1f, 0.0f);

		case 2:
			waypoints[i].position_ = gef::Vector4(i * 0.1f, 0.1f, 0.0f);
		case 4:
			waypoints[i].position_ = gef::Vector4(i * 0.1f, -0.2f, 0.0f);
		case 6:
			waypoints[i].position_ = gef::Vector4(4 * 0.1f, 0.1f, 0.0f);
		case 7:
			waypoints[i].position_ = gef::Vector4(i * 0.1f, 0.1f, 0.0f);


		default:
			break;
		}



	}
}

void Enemy::CalculateDistance(float frameTime)
{

	distanceBetweenWaypoints = waypoints[NextWaypoint].position_ - waypoints[currentWaypoint].position_;
	temp = distanceBetweenWaypoints;
	distanceBetweenWaypoints.Normalise();
	velocity_ = distanceBetweenWaypoints;
	velocity_ *= 0.20f;
	distanceMovingObj = position_ - waypoints[currentWaypoint].position_;



}
