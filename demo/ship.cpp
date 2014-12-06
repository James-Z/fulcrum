#include "ship.hpp"

ship::ship (void) : _object_base() {
	initial_ship();
}
ship::~ship (void) {
	std::cout<<"ship is go away!\n";
}
void ship::initial_ship ( void ) {
	load_model_data_from_assets( masset_manager->get_model_data( "lowpolyspaceship1.dae" ) );
	/* load_model_data_from_assets( masset_manager->get_model_data( "lowpolyspaceship.dae" ) ); */
	/* set_position_in_world( glm::vec3( 0.0F, .0F, 0.0F ) ); */
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

	this->set_name( "ship" );
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
	/* get_rigidbody()->setUserPointer( this ); */
	std::cout<<"ship was generated!\n";
}

/* stone_a_l.cpp */

stone_a_l::stone_a_l (void) : _object_base(), aaa("some OK") {
	initial_stone_a_l();
}
stone_a_l::~stone_a_l (void) {
	std::cout<<"stone_a_l is go away!\n";
}
void stone_a_l::initial_stone_a_l ( void ) {
	load_model_data_from_assets( masset_manager->get_model_data( "stone_a_l.dae" ) );
	/* load_model_data_from_assets( masset_manager->get_model_data( "lowpolyspacestone_a_l.dae" ) ); */
	/* set_position_in_world( glm::vec3( 0.0F, .0F, 0.0F ) ); */
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

	this->set_name( "stone_a_l" );
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
	/* get_rigidbody()->setUserPointer( this ); */
	std::cout<<"stone_a_l was generated!\n";
}

void stone_a_l::update (void) {
	if( is_interact_with( "ship" ) ) {
		this->set_material_diffuse_color( glm::vec4( 0.2, 0.2, 0.8, 1.0 ) );
		this->set_material_specular_color( glm::vec4( 0.1, 0.6, 0.6, 1.0 ) );
		/* std::cout<<"alerm!\n"; */
	}
	if( is_interact_with( "circle" ) ) {
		this->set_material_diffuse_color( glm::vec4( 0.8, 0.2, 0.2, 1.0 ) );
		this->set_material_specular_color( glm::vec4( 0.1, 0.6, 0.6, 1.0 ) );
		/* std::cout<<"alerm!\n"; */
	}
}


