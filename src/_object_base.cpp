#include "_object_base.hpp"

_object_base::_object_base (void) :	_matrix_catch_camera_in_world( 1 ),
					_matrix_in_world( 1 ),
					_matrix_in_camera_world( 1 ),
					_matrix_follow_in_world( 1 ),
					_position_in_world( 0 ),
					_ID( 0 ),
					_be_catched_camera_ID( 0 ),
					_be_catched_controller_ID( 0 ),
					_is_destoried( false ),
					_is_catch_camera( false ),
					_is_be_controlled( false ),
					_model(),
					_force( 0, 0, 0 ),
					_angular( 0, 0, 0 ),
					_mass( 0 ),
					_inertia( 0, 0, 0 ),
					_state( 0 ),
					_motion_state( nullptr ),
					_rigid_body( nullptr ),
					_shape( nullptr ) {}

_object_base::~_object_base (void) {
	this->destory();
}

void _object_base::destory (void) {}

void _object_base::update_gl_uniform ( const _shader_manager& be_using_shader ) {
	if( is_be_controlled() ) {
		glUniformMatrix4fv( be_using_shader.object_transforms, 1, GL_FALSE, glm::value_ptr( _matrix_catch_camera_in_world ) );
		glUniformMatrix3fv( be_using_shader.normal_transforms, 1, GL_FALSE, glm::value_ptr( glm::mat3( _matrix_catch_camera_in_world ) ) );
	} else {
		glUniformMatrix4fv( be_using_shader.object_transforms, 1, GL_FALSE, glm::value_ptr( _matrix_in_camera_world ) );
		glUniformMatrix3fv( be_using_shader.normal_transforms, 1, GL_FALSE, glm::value_ptr( glm::mat3( _matrix_in_camera_world ) ) );
	}
}

void _object_base::draw (void) {
	_model.draw();
}

void _object_base::update_matrix_in_camera_world ( const glm::mat4& update_matrix ) {
	_matrix_in_camera_world = glm::inverse( update_matrix ) * _matrix_in_world;
}

void _object_base::update_matrix_catch_camera_in_world ( const glm::mat4& update_matrix ) {
	_matrix_catch_camera_in_world = glm::inverse( update_matrix );
}

void _object_base::translate ( const glm::vec3& direction ) {
	_matrix_in_world = glm::translate( _matrix_in_world, direction );
}

void _object_base::rotate ( const float& angle, const glm::vec3& rotate_axis ) {
	_matrix_in_world = glm::rotate( _matrix_in_world, angle, rotate_axis );
}

void _object_base::follow ( const _object_base* be_followed_object, bool is_rotate) {
	if( is_rotate ) {
		glm::vec3( _matrix_in_world[3] ) = glm::vec3( be_followed_object->get_matrix_in_world()[3] );
	} else {
		_matrix_in_world = be_followed_object->get_matrix_in_world();
	}
}

void _object_base::update (void) {
	//update object
}

void _object_base::apply_physics (void) {
	/* _rigid_body->applyTorque( _angular ); */
	btVector3 r = _rigid_body->getWorldTransform().getBasis() * _angular;
	_rigid_body->setAngularVelocity( r );
	btVector3 v = _rigid_body->getWorldTransform().getBasis() * _force;
	this->get_rigidbody()->applyCentralForce( v );
	/* _rigid_body->applyTorqueImpulse( _angular ); */
	/* _rigid_body->setLinearVelocity( _force ); */
}

void _object_base::move_and_turn ( const std::vector<int>& msg ) {

	int state;
	for( auto iter = msg.begin(); iter != msg.end(); ++iter ) {
		state = *iter;
		if( state == MOTION_STATE::FORWORD ) {
			_force.setZ( -10.5F );
		} else if( state == BACKWARD ) {
			_force.setZ( 10.0F );
		} else if( state == MOTION_STATE::Z_MOVE_STOP ) {
			_force.setZ( 0.0F );
		}

		else if( state == MOTION_STATE::RIGHT_WARD ) {
			_force.setX( -10.0F );
		} else if( state == MOTION_STATE::LEFT_WARD ) {
			_force.setX( 10.0F );
		} else if( state == MOTION_STATE::X_MOVE_STOP ) {
			_force.setX( 0.0F );
		}

		else if( state == MOTION_STATE::UP_WARD ) {
			_force.setY( 10.0F );
		} else if( state == MOTION_STATE::DOWN_WARD ) {
			_force.setY( -10.0F );
		} else if( state == MOTION_STATE::Y_MOVE_STOP ) {
			_force.setY( 0.0F );
		}

		//
		else if( state == MOTION_STATE::CLOCK_WISE_ROTATION ) {
			_angular.setZ( 1.0F );
		} else if( state == MOTION_STATE::ANTI_CLOCK_WISE_ROTATION ) {
			_angular.setZ( -1.0F );
		} else if( state == MOTION_STATE::Z_TURN_STOP ) {
			_angular.setZ( 0.0F );
		}

		else if( state == MOTION_STATE::RIGHT_ROTATION ) {
			_angular.setY( -1.0F );
		} else if( state == MOTION_STATE::LEFT_ROTATION ) {
			_angular.setY( 1.0F );
		} else if( state == MOTION_STATE::Y_TURN_STOP ) {
			_angular.setY( 0.0F );
		}

		else if( state == MOTION_STATE::UP_ROTATION ) {
			_angular.setX( -1.0F );
		} else if( state == MOTION_STATE::DOWN_ROTATION ) {
			_angular.setX( 1.0F );
		} else if( state == MOTION_STATE::X_TURN_STOP ) {
			_angular.setX( 0.0F );
		}
	}
}

void _object_base::move_and_turn ( const int state ) {
	_state = state;

	if( state == MOTION_STATE::FORWORD ) {
		_force = btVector3( 0.0F, 0.0F, -10.5F );
	} else if( state == BACKWARD ) {
		_force  = btVector3( 0.0F, 0.0F, 10.0F );
	} else if( state == MOTION_STATE::Z_MOVE_STOP ) {
		_force.setZ( 0.0F );
	}
	
	if( state == MOTION_STATE::FORWORD ) {
		_force = btVector3( 0.0F, 0.0F, -10.5F );
	} else if( state == BACKWARD ) {
		_force  = btVector3( 0.0F, 0.0F, 10.0F );
	} else if( state == MOTION_STATE::Z_MOVE_STOP ) {
		_force.setZ( 0.0F );
	}

	if( state == MOTION_STATE::FORWORD ) {
		_force = btVector3( 0.0F, 0.0F, -10.5F );
	} else if( state == BACKWARD ) {
		_force  = btVector3( 0.0F, 0.0F, 10.0F );
	} else if( state == MOTION_STATE::Z_MOVE_STOP ) {
		_force.setZ( 0.0F );
	}

	//
	if( state == MOTION_STATE::CLOCK_WISE_ROTATION ) {
		_angular.setZ( 1.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::ANTI_CLOCK_WISE_ROTATION ) {
		_angular.setZ( -1.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::Z_TURN_STOP ) {
		_angular.setZ( 0.0F );
	}

	if( state == MOTION_STATE::RIGHT_ROTATION ) {
		_angular.setY( -1.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::LEFT_ROTATION ) {
		_angular.setY( 1.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::Y_TURN_STOP ) {
		_angular.setY( 0.0F );
	}

	if( state == MOTION_STATE::UP_ROTATION ) {
		_angular.setX( -1.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::DOWN_ROTATION ) {
		_angular.setX( 1.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::X_TURN_STOP ) {
		_angular.setX( 0.0F );
	}
}

void _object_base::apply_physics_transform_update (void) {
	glm::mat4 tem( 1 );
	this->get_rigidbody()->getWorldTransform().getOpenGLMatrix( glm::value_ptr(tem) );
	this->set_matrix_in_world( tem );
}

void _object_base::multiply_matrix_in_world ( const glm::mat4& matrix ) {
	_matrix_in_world = _matrix_in_world * matrix;
}

void _object_base::multiply_matrix_follow_in_world ( const glm::mat4& matrix ) {
	_matrix_follow_in_world = _matrix_follow_in_world * matrix;
}

void _object_base::set_position_in_world ( const glm::vec3& position ) {
	_position_in_world = glm::vec4( position, 1.0F);
	_matrix_in_world = glm::translate( glm::mat4(1.0F), position );
}

void _object_base::init_rigid_body ( const btScalar mass, const btVector3 inertia, btCollisionShape* shape ) {

	btTransform bt_matrix_in_world;
	bt_matrix_in_world.setFromOpenGLMatrix( glm::value_ptr(this->get_matrix_in_world()) );
	_motion_state = std::make_shared<btDefaultMotionState>( bt_matrix_in_world );
	_shape = std::shared_ptr<btCollisionShape>( shape );

	btRigidBody::btRigidBodyConstructionInfo rigidbody_info = btRigidBody::btRigidBodyConstructionInfo(	btScalar(2.F),
														_motion_state.get(),
														_shape.get(),
														inertia );
	_rigid_body = std::make_shared<btRigidBody>( rigidbody_info );
}

