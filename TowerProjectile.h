#pragma once
#include "GameObjectMy.h"
#include "..\CMP404Coursework\primitive_builder.h"
#include <graphics/renderer_3d.h>

class TowerProjectile :
	public GameObjectMy
{
public:
	TowerProjectile(PrimitiveBuilder * primitive_builder, gef::Renderer3D* Renderer_3d_);
	~TowerProjectile();

	void Update(float frameTime);
	void Init();
	void Render();
	void SetMarkerTransform(gef::Matrix44 markerTransform_) { markerTranform = markerTransform_; }



private:
	PrimitiveBuilder * primitive_builder;
	gef::Matrix44 markerTranform;
	gef::Renderer3D* renderer_3d_;
};

