#include "TowerProjectile.h"



TowerProjectile::TowerProjectile(PrimitiveBuilder * primitive_builder, gef::Renderer3D* Renderer_3d_) :
	primitive_builder(primitive_builder),
	renderer_3d_(Renderer_3d_)
{
	set_mesh(primitive_builder->CreateSphereMesh(.01, 20, 20));

}


TowerProjectile::~TowerProjectile()
{
	delete primitive_builder;
	primitive_builder = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;
}

void TowerProjectile::Update(float frameTime)
{
	localTransform_ = localTransform_ * markerTranform;
	GameObjectMy::Update(frameTime);
	set_transform(localTransform_ * markerTranform);



}

void TowerProjectile::Init()
{
}

void TowerProjectile::Render()
{
	// Begin rendering 3D meshes, don't clear the frame buffer
	renderer_3d_->Begin(false);

	renderer_3d_->DrawMesh(*this);


	renderer_3d_->End();


}

