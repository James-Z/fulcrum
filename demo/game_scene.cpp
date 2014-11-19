#include "game_scene.hpp"
#include "cameras.hpp"
#include "circle.hpp"
#include "ship.hpp"

game_scene::game_scene (void) : _scene_base() {}

game_scene::~game_scene (void) {}

void game_scene::start (void) {
	get_physics_world()->setGravity( btVector3(0.0F, 0.0F, 0.0F) );
	//
	std::string shader_file_name = "ver.sdr fag.sdr";
	const unsigned int game_shader = 1;
	shader_load( shader_file_name, game_shader );
	//
	set_ambient_color( glm::vec4(0.3F, 0.3F, 0.3F, 1.0F) );
	//
	_light_base* light_one = new _light_base();
	light_one->set_diffuse_color( glm::vec3(1.0F, 1.0F, 1.0F) );
	/* light_one->set_diffuse_color( glm::vec3(0.36F, 0.05F, 0.67F) ); */
	light_one->set_specular_color( glm::vec3(0.9F, 0.9F, 0.9F) );
	light_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F) );
	/* light_one->rotate( 8.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
	light_one->translate( glm::vec3(400.0F, -100.0F, 400.0F) );
	add_light( light_one );

	/* _light_base* light_two = new _light_base(); */
	/* light_two->set_diffuse_color( glm::vec3(0.F, 0.F, 1.F) ); */
	/* light_two->set_specular_color( glm::vec3(0.9F, 0.9F, 0.9F) ); */
	/* light_two->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F) ); */
	/* /1* light_two->rotate( 8.0F, vec3( 0.0F, 1.0F, 0.0F ) ); *1/ */
	/* light_two->translate( glm::vec3(-400.0F, 200.0F, 400.0F) ); */
	/* add_light( light_two ); */
	/* std::cout<<"dot: "<<glm::dot( glm::vec3(0.0F, 0.0F, -4.0), glm::vec3(0.0F, 0.0F, -1.0) )<<std::endl; */
	//
	camera_main* camera_m = new camera_main();
	camera_m->set_ID( 11 );
	camera_m->perspective( 45.0F, 1366.0F / 768.0F, 1.0F, 1000.0F );
	camera_m->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
	camera_m->rotate( 0.0F, glm::vec3( 0.0F, 1.0F, 0.0F ) );
	camera_m->_camera_base::translate( glm::vec3( 0.0F, 3.F, 8.0F ) );
	camera_m->_camera_base::rotate( -10.0F, glm::vec3( 1.0F, 0.F, 0.0F ) );
	add_camera( camera_m );

	//
	btCollisionDispatcher* dispatcher = static_cast<btCollisionDispatcher*>( this->get_physics_world()->getDispatcher() );
	btGImpactCollisionAlgorithm::registerAlgorithm( dispatcher );
	//
	{
		ship* object_one = new ship();
		/* object_one->generate_model(); */
		/* object_one->load_model_data_from_assets( asset->get_model_data( "lowpolyspaceship.dae" ) ); */
		object_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
		object_one->translate( glm::vec3( .0F, 0.0F, -0.5F ) );
		object_one->set_material_diffuse_color( glm::vec4( 0.0, 0.6, 0.6, 1.0 ) );
		object_one->set_material_specular_color( glm::vec4( 0.0, 0.6, 0.6, 1.0 ) );

		
		/* //////////////////// */
		/* object_one->init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape ); */
		object_one->get_rigidbody()->setDamping( 0.05F, 0.01F );
		object_one->get_rigidbody()->setAngularFactor( btVector3(0.0F, 0.0F, 0.0F) );
		object_one->get_rigidbody()->setLinearFactor( btVector3(0.0F, 0.0 ,0.0) );
		add_object( object_one, game_shader );
	}

	{
		circle* circle_o = new circle();
		circle_o->catch_contrtoller();
		circle_o->catch_camera( camera_m->get_ID() );
		circle_o->set_material_diffuse_color( glm::vec4( 0.6, 0.6, 0.6, 1.0 ) );
		circle_o->set_material_specular_color( glm::vec4( 0.6, 0.6, 0.6, 1.0 ) );
		add_object( circle_o, game_shader );
	}


}

void game_scene::update (void) {}

