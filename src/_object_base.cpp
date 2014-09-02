#include "_object_base.hpp"

_object_base::_object_base (void) :	_force( 0, 0, 0 ),
					_angular( 0, 0, 0 ),
					_state( 0 ),
					_is_destoried( false ),
					_is_be_controlled( false ),
					_is_catch_camera( false ),
					_model(),
					_rigid_body( nullptr ) {}

_object_base::~_object_base (void) {}

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
	/* _rigid_body->applyCentralImpulse( _force ); */
	_rigid_body->setAngularFactor( 1.0F );
	_rigid_body->setLinearFactor( btVector3(1.0F, 1.0 ,1.0) );
	_rigid_body->updateInertiaTensor();
	/* std::cout<<_angular.getY(); */
	_rigid_body->applyCentralForce( _force );
	_rigid_body->applyTorque( _angular );
	/* _rigid_body->applyTorqueImpulse( _angular ); */
	std::cout<<"Torque: "<<_rigid_body->getTotalTorque().getY()<<"\n";
	/* _rigid_body->setLinearVelocity( _force ); */
	/* _rigid_body->setAngularVelocity( _angular ); */
}

void _object_base::move_and_turn ( const int state ) {
	_state = state;
	if( state == MOTION_STATE::FORWORD ) {
		_force = btVector3( 0.0F, 0.0F, -10.5F );
		_force = _rigid_body->getWorldTransform().getBasis() * _force;
	} else if( state == BACKWARD ) {
		_force = btVector3( 0.0F, 0.0F, 10.0F );
		_force = _rigid_body->getWorldTransform().getBasis() * _force;
	} else if( state == MOTION_STATE::CLOCK_WISE_ROTATION ) {
		_angular = btVector3( 0.0F, 1.0F, 0.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::ANTI_CLOCK_WISE_ROTATION ) {
		_angular = btVector3( 0.0F, -1.0F, 0.0F );
		_angular = _rigid_body->getWorldTransform().getBasis() * _angular;
	} else if( state == MOTION_STATE::STOP ) {
		_force = btVector3( 0.0F, 0.0F, 0.0F );
		_angular = btVector3( 0.0F, 0.0F, 0.0F );
	} else {
		/* _angular = btVector3( 0.0F, 0.0F, 0.0F ); */
		/* _force = btVector3( 0.0F, 0.0F, 0.0F ); */
		/* std::cout<<"else"<<std::endl; */
	}
}

void _object_base::destory (void) {
}

void _object_base::set_matrix_in_world ( const glm::mat4& matrix ) {
	//set object martix to set_matrix
	_matrix_in_world = matrix;
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

void _object_base::set_rigid_body ( void ) {
	btTransform trasform;
	trasform.setIdentity();
	/* trasform.setOrigin( btVector3(_position_in_world.x, _position_in_world.y, _position_in_world.z) ); */
	trasform.setFromOpenGLMatrix( glm::value_ptr(_matrix_in_world) );
	btDefaultMotionState* motion_state = new btDefaultMotionState( trasform );
	btCollisionShape* sphere = new btBoxShape( btVector3( 1, 1, 1 ) );
	btVector3 localInertia = btVector3( 0.6F, 0.6F, 0.6F );
	sphere->calculateLocalInertia( btScalar(5.F), localInertia );
	btRigidBody::btRigidBodyConstructionInfo rbInfo = btRigidBody::btRigidBodyConstructionInfo( btScalar(5.F), motion_state, sphere, localInertia );
	btRigidBody* rigid_body = new btRigidBody( rbInfo );
	rigid_body->setDamping( 0.392F, 0.392F );
	/* rigid_body->applyGravity(); */
	/* rigid_body->setGravity( btVector3(0, -10, 0) ); */
	/* rigid_body->applyCentralImpulse( btVector3(0, -10, 0) ); */
	_rigid_body = rigid_body;
}

