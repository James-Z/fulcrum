#include "_camera_base.hpp"

_camera_base::_camera_base (void) : _object_base(), _perspective_matrix(1) {}

_camera_base::~_camera_base (void) {}

void _camera_base::perspective ( float fovy, float aspect, float zNear, float zFar ) {
	_perspective_matrix = glm::perspective( fovy, aspect, zNear, zFar );
}

void _camera_base::update_camera_matrix_from_object ( const glm::mat4& object_matrix ) {
	/* _matrix_in_world = glm::inverse ( object_matrix ); */
	_matrix_in_world = object_matrix;
}

void _camera_base::update_camera_matrix ( const glm::mat4& update_matrix ) {
	_matrix_in_world  = _matrix_in_world * update_matrix;
}

void _camera_base::update_camera_matrix_follow_in_world_gl_uniform ( const _shader_manager& be_using_shader ) {
	glUniformMatrix4fv( be_using_shader.camera_transforms, 1, GL_FALSE,
			glm::value_ptr( this->get_matrix_follow_in_world() ) );
}

void _camera_base::update_camera_perspective_matrix_gl_uniform ( const _shader_manager& be_using_shader ) {
	glUniformMatrix4fv( be_using_shader.perspective_transforms, 1, GL_FALSE,
			glm::value_ptr( this->get_perspective() ) );
}

void _camera_base::translate ( const glm::vec3& direction) {
	_matrix_follow_in_world = glm::translate( _matrix_follow_in_world, direction );
	/* _matrix_in_world = glm::translate( _matrix_in_world, direction ); */
}

void _camera_base::rotate ( const float& angle, const glm::vec3& rotate_axis ) {
	_matrix_follow_in_world = glm::rotate( _matrix_follow_in_world, angle, rotate_axis );
	_matrix_in_world = glm::rotate( _matrix_in_world, angle, rotate_axis  );
}

void _camera_base::follow ( const _object_base* be_followed_object, bool is_rotate ) {}

void _camera_base::update (void) {}

