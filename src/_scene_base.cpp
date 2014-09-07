#include "_scene_base.hpp"

_scene_base::_scene_base (void) : _current_shader(), _physic_world() {
	_light_base_set_in_scene = new _light_base_set();
	_controller_in_scene = new _controller_base();

}

_scene_base::~_scene_base (void) {
	if( _light_base_set_in_scene != nullptr ) {
		delete _light_base_set_in_scene;
		_light_base_set_in_scene = nullptr;
	}
	if( _controller_in_scene != nullptr ) {
		delete _controller_in_scene;
		_controller_in_scene = nullptr;
	}
	if( _physic_world != nullptr ) {
		delete _physic_world;
		_physic_world = nullptr;
	}
}

void _scene_base::initilize_scene (void) {
	glClearColor( 0.6f, 0.0f, 0.6f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthRange( 0.0f, 1.0f );
	/* glFrontFace( GL_CCW ); */
	//cull face
	/* glEnable( GL_CULL_FACE ); */
	/* glCullFace( GL_BACK ); */

	//
	/* GLenum err = glewInit (); */
        /* if( err != GLEW_OK ) { */
	/* 	cout << glewGetErrorString( err ) << endl; */
	/* 	exit( 1 ); */
        /* } */
	//need initilize_shader
	//
	//initilize the physic world
	_collision_configuration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher( _collision_configuration );
	_broadphase = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver();
	_physic_world = new btDiscreteDynamicsWorld( _dispatcher, _broadphase, _solver, _collision_configuration );
	_physic_world->setGravity( btVector3(0.0F,0.0F,0.0F) );
}	//initilize_scene

void _scene_base::shader_load ( const std::string shader_file_names, const unsigned int shader_name ) {
	_shader_manager* temp_shader = new _shader_manager();
	temp_shader->create_shader( shader_file_names );
	_current_shader = temp_shader;
	_shaders.insert( std::make_pair( shader_name, temp_shader ) );
	if( _shaders_and_objects_in_scene.find( shader_name ) == _shaders_and_objects_in_scene.end() ) {
		_shaders_and_objects_in_scene[shader_name];
	}
	//delete temp_shader;
	temp_shader = nullptr;
}

void _scene_base::add_camera ( _camera_base* camera ) {
	_cameras_in_scene.push_back( camera );
}

void _scene_base::add_light ( _light_base* light ) {
	_light_base_set_in_scene->add_light( light );
}

void _scene_base::add_object ( _object_base* object, const unsigned int shader_name ) {
	_shaders_and_objects_in_scene_iter = _shaders_and_objects_in_scene.find( shader_name );//->second.push_back( object );
	if( _shaders_and_objects_in_scene_iter != _shaders_and_objects_in_scene.end() ) {
		if( object ) {
			_shaders_and_objects_in_scene_iter->second.push_back( object );
			if( object->get_rigidbody() ) {
				_physic_world->addRigidBody( object->get_rigidbody() );
				/* _physic_world->addCollisionObject( object->get_rigidbody() ); */
			} else {
				std::cerr<<"add_object object do not initilize the collision"<<std::endl;
			}
		} else {
			std::cerr<<"add_object object's point is empty"<<std::endl;
		}
	} else {
		std::cerr<<"add_object can't find shader_name"<<std::endl;
	}
}

void _scene_base::set_ambient_color ( const glm::vec4 color ) {
	_ambient_color_in_scene = color;
}

void _scene_base::load_scene (void) {
	_shaders_and_objects_in_scene_iter = _shaders_and_objects_in_scene.begin();
	for( ; _shaders_and_objects_in_scene_iter != _shaders_and_objects_in_scene.end(); ++_shaders_and_objects_in_scene_iter ) {
		_current_shader = _shaders.find( _shaders_and_objects_in_scene_iter->first )->second;
		//
		glUseProgram( _current_shader->get_shader() );
		glUniform4fv ( _current_shader->ambient_color, 1, glm::value_ptr( get_ambient_color() ) );
		glUseProgram( 0 );
	}
}

void _scene_base::update_scene (void) {

	//physics world update
	btScalar co = (btScalar)_clock.getTimeMicroseconds();
	_physic_world->stepSimulation( btScalar(co / 1000000.0F));
	/* _physic_world->stepSimulation( 1.0/420.0 ); */

	//update lights in scene
	_light_base_set_in_scene->update_lights();

	//update objects in scene
	_shaders_and_objects_in_scene_iter = _shaders_and_objects_in_scene.begin();
	for( ; _shaders_and_objects_in_scene_iter != _shaders_and_objects_in_scene.end(); ++_shaders_and_objects_in_scene_iter ) {
		if( !_shaders_and_objects_in_scene_iter->second.empty() ) {
			_objects_in_scene_iter = _shaders_and_objects_in_scene_iter->second.begin();
			/* std::cerr<<"_objects_in_scene_iter : "<<_shaders_and_objects_in_scene_iter->second.size()<<std::endl; */
			for( ; _objects_in_scene_iter != _shaders_and_objects_in_scene_iter->second.end(); ++_objects_in_scene_iter ) {
				//
				if( (*_objects_in_scene_iter)->is_be_controlled() ) {
					//control by transform
					/* (*_objects_in_scene_iter)->multiply_matrix_in_world( _controller_in_scene->get_object_controller_matrix() ); */

					(*_objects_in_scene_iter)->update();

					(*_objects_in_scene_iter)->move_and_turn( _controller_in_scene->get_object_motion_state() );
					(*_objects_in_scene_iter)->apply_physics();

					(*_objects_in_scene_iter)->apply_physics_transform_update();
					/* std::cout<<"x: "<<tem[3].x<<"y:"<<tem[3].y<<"z: "<<tem[3].z<<std::endl; */

					if( !(*_objects_in_scene_iter)->get_rigidbody()->isActive() ) {
						std::cout<<"unactive\n";
						(*_objects_in_scene_iter)->get_rigidbody()->activate( true );
					}
				} else {
					(*_objects_in_scene_iter)->update();

					(*_objects_in_scene_iter)->apply_physics_transform_update();
				}
				//if this object catch the camera,check which camera has been catched and update camera's matrix
				if( (*_objects_in_scene_iter)->is_catch_camera() ) {
					_cameras_in_scene_iter = _cameras_in_scene.begin();
					for( ; _cameras_in_scene_iter != _cameras_in_scene.end(); ++_cameras_in_scene_iter) {
						if( (*_cameras_in_scene_iter)->get_ID() == (*_objects_in_scene_iter)->be_catched_camera_ID() &&
							//this need a new enum for 0
							(*_cameras_in_scene_iter)->get_ID() > 0 ) {
							(*_cameras_in_scene_iter)->update_camera_matrix_from_object( (*_objects_in_scene_iter)->get_matrix_in_world() );
							//store and mutiply follow matrix
							(*_cameras_in_scene_iter)->multiply_matrix_follow_in_world( _controller_in_scene->get_camera_controller_matrix() );
							/* (*_cameras_in_scene_iter)->update(); */
						}
					}	//_cameras_in_scene_iter loop
				}
				//
				/* we need something spawn (maybe some blooms?) and not destory directly */
				if( (*_objects_in_scene_iter)->is_destory() ) {
					(*_objects_in_scene_iter)->destory();
					_shaders_and_objects_in_scene_iter->second.erase( _objects_in_scene_iter );
				}
			}	//_shaders_and(*_objects_in_scene_iter)->second loop
		} else {
			std::cerr<<"_shaders_and_objects_in_scene_iter, there is empty"<<std::endl;
		}
	}	//_shaders_and_objects_in_scene loop;

	_clock.reset();
}	//update_scene

void _scene_base::render_scene (void) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	_cameras_in_scene_iter = _cameras_in_scene.begin();
	if( _cameras_in_scene.empty() ) {
		std::cerr<<"_cameras_in_scene_iter, there is empty"<<std::endl;
	}
	for( ; _cameras_in_scene_iter != _cameras_in_scene.end() ; ++_cameras_in_scene_iter ) {
		if((*_cameras_in_scene_iter)->get_ID() > 0) {	//camera ID mast bigger than 0
			_shaders_and_objects_in_scene_iter = _shaders_and_objects_in_scene.begin();
			for( ; _shaders_and_objects_in_scene_iter != _shaders_and_objects_in_scene.end(); ++_shaders_and_objects_in_scene_iter ) {
				if( !_shaders_and_objects_in_scene_iter->second.empty() ) {
					/* maybe there is bug at here */
					_current_shader = _shaders.find( _shaders_and_objects_in_scene_iter->first )->second;
					//
					glUseProgram( _current_shader->get_shader() );

					(*_cameras_in_scene_iter)->update_camera_perspective_matrix_gl_uniform( *_current_shader );
					(*_cameras_in_scene_iter)->update_camera_matrix_follow_in_world_gl_uniform( *_current_shader );


					_light_base_set_in_scene->update_lights_data( (*_cameras_in_scene_iter)->get_matrix_in_world() );
					_light_base_set_in_scene->update_lights_data_to_gl_uniform( *_current_shader );

					_objects_in_scene_iter = _shaders_and_objects_in_scene_iter->second.begin();
					for( ; _objects_in_scene_iter != _shaders_and_objects_in_scene_iter->second.end(); ++_objects_in_scene_iter ) {
						if( (*_objects_in_scene_iter)->is_catch_camera() ) {
							(*_objects_in_scene_iter)->update_matrix_catch_camera_in_world( (*_cameras_in_scene_iter)->get_matrix_follow_in_world() );
							(*_objects_in_scene_iter)->update_gl_uniform( *_current_shader );
							(*_objects_in_scene_iter)->draw();
						} else {
							(*_objects_in_scene_iter)->update_matrix_in_camera_world( (*_cameras_in_scene_iter)->get_matrix_in_world() );
							(*_objects_in_scene_iter)->update_gl_uniform( *_current_shader );
							(*_objects_in_scene_iter)->draw();
						}
					}
					glUseProgram( 0 );
				}
			}	//_shaders(_and_objects_in_scene) loop
		}
	}	//_cameras_in_scene loop
}	//render_scene

void _scene_base::edit_scene (void) {}

