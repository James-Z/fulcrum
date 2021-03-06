#include "circle.hpp"
#include "ship.hpp"

circle::circle (void) : _object_base() {
	initial_circle();
}

circle::~circle (void) {
	std::cout<<"circle is go away!\n";
}

void circle::initial_circle (void) {
	load_model_data_from_assets( masset_manager->get_model_data( "circle.dae" ) );
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

	this->set_name( "circle" );
	triangle_mesh = std::make_shared<btTriangleMesh>();
	auto i = get_model_data().begin();
	for ( int it = 0; it < get_model_data().size()/2; ++i, ++it ) {
		triangle_mesh->addTriangle(	btVector3(i->x.x, i->x.y, i->x.z),
				btVector3(i->y.x, i->y.y, i->y.z),
				btVector3(i->z.x, i->z.y, i->z.z) );
	}
	btVector3 aabbMin(-1000,-1000,-1000),aabbMax(1000,1000,1000);
	tmpshape = std::make_shared<btGImpactMeshShape>( triangle_mesh.get() );//, true, aabbMin, aabbMax );
	tmpshape->updateBound();

	//
	/* init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape.get() ); */
	init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape );
	get_rigidbody()->setMassProps( 1, btVector3(0.918, 0.918, 0.918) );
	get_rigidbody()->setDamping( 0.618F, 0.618F );
	get_rigidbody()->setAngularFactor( btVector3(1.0F, 1.0F, 1.0F) );
	get_rigidbody()->setLinearFactor( btVector3(1.0F, 1.0 ,1.0) );
	/* get_rigidbody()->setUserPointer( this ); */
	std::cout<<"circle was generated!\n";
	/* add_object( this ); */
}

static int stone_numer = 0;
void circle::update (void) {
	if( (this->get_local_position_in_world().z < 0.0F) && (stone_numer < 2) ){
		std::shared_ptr<stone_a_l> stone_a_l_a = std::make_shared<stone_a_l>();
		/* stone_a_l_a->generate_model(); */
		/* stone_a_l_a->load_model_data_from_assets( asset->get_model_data( "lowpolyspacestone_a_l.dae" ) ); */
		stone_a_l_a->set_name( "s1" );
		stone_a_l_a->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
		stone_a_l_a->translate( glm::vec3( 0.0F, float(stone_numer)*3.0F, float(stone_numer)*(-5.0F) ) );
		stone_a_l_a->set_material_diffuse_color( glm::vec4( 0.0, 0.6, 0.6, 1.0 ) );
		stone_a_l_a->set_material_specular_color( glm::vec4( 0.0, 0.6, 0.6, 1.0 ) );

		/* //////////////////// */
		/* stone_a_l_a->init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape ); */
		stone_a_l_a->get_rigidbody()->setDamping( 0.05F, 0.01F );
		stone_a_l_a->get_rigidbody()->setAngularFactor( btVector3(0.4F, 0.4F, 0.4F) );
		stone_a_l_a->get_rigidbody()->setLinearFactor( btVector3(0.4F, 0.4F, 0.4F) );
		add_object( stone_a_l_a );
		++stone_numer;
	}
}


