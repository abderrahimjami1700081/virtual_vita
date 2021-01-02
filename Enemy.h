#pragma once
#include "GameObjectMy.h"
#include "primitive_builder.h"

#ifndef _NUMWAYPOINTS
#define _NUMWAYPOINTS 10
#endif // _NUMWAYPOINTS

class Enemy :
	public GameObjectMy
{
public:
	Enemy();
	~Enemy();
	void Init();
	void Update(float frameTime);
	void SetWaypointPos();
	void CalculateDistance(float frameTime);
	void SetMarkerTransform(gef::Matrix44 markerTrans) { markerTransform = markerTrans; }
	void SetPrimitivePtr(PrimitiveBuilder* primitiveBuilderPtr) { primitiveBuilder_ = primitiveBuilderPtr; }

private:

	//Enemy class holds waypoints positions (which are gameobjects in the game)
	GameObjectMy waypoints[_NUMWAYPOINTS];
	gef::Vector4 distanceBetweenWaypoints;
	gef::Vector4 distanceMovingObj;
	int currentWaypoint;
	int NextWaypoint;

	// Temp Timer for testing 
	float timer;
	gef::Matrix44 markerTransform;
	gef::Vector4 temp;
	PrimitiveBuilder* primitiveBuilder_;

	////////////////
	








};

