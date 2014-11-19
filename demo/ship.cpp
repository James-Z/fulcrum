#include "ship.hpp"

ship::ship (void) : _object_base() {
	initial_ship();
}
ship::~ship (void) {
	std::cout<<"ship is go away!\n";
}
void ship::initial_ship ( void ) {
	load_model_data_from_assets( masset_manager->get_model_data( "lowpolyspaceship.dae" ) );
	set_position_in_world( glm::vec3( 0.0F, .0F, 0.0F ) );
	/* catch_camera( camera_one->get_ID() ); */
	/* realse_camera(); */
	////////////////////
	/* tmpshape1 = std::make_shared<btConvexHullShape>(); */
	/* int it = 0; */
	/* for ( auto i = get_model_data().begin(); it < get_model_data().size()/2; ++it,++i ) { */
	/* 	tmpshape1 ->addPoint( btVector3(i->x.x, i->x.y, i->x.z) ); */
	/* 	tmpshape1->addPoint( btVector3(i->y.x, i->y.y, i->y.z) ); */
	/* 	tmpshape1->addPoint( btVector3(i->z.x, i->z.y, i->z.z) ); */

	/* } */
	/* // */
	/* tmpshape->setLocalScaling( btVector3(0.95, 0.95, 0.95) ); */

	triangle_mesh = std::make_shared<btTriangleMesh>();
	auto i = get_model_data().begin();
	for ( int it = 0; it < get_model_data().size()/2; ++i, ++it ) {
		triangle_mesh->addTriangle(	btVector3(i->x.x, i->x.y, i->x.z),
				btVector3(i->y.x, i->y.y, i->y.z),
				btVector3(i->z.x, i->z.y, i->z.z) );
	}
	btVector3 aabbMin(-1000,-1000,-1000), aabbMax(1000,1000,1000);
	tmpshape = std::make_shared<btGImpactMeshShape>( triangle_mesh.get() );//, true, aabbMin, aabbMax );
	tmpshape->updateBound();

	//
	/* init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape.get() ); */
	init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape );
	get_rigidbody()->setMassProps( 1, btVector3(0.918, 0.918, 0.918) );
	get_rigidbody()->setDamping( 0.618F, 0.618F );
	get_rigidbody()->setAngularFactor( btVector3(0.0F, 0.0F, 0.0F) );
	get_rigidbody()->setLinearFactor( btVector3(0.0F, 0.0 ,0.0) );
	std::cout<<"ship was generated!\n";
}

