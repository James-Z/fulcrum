#include "_controller_base.hpp"

_controller_base::_controller_base (void) : _object_base() {}
_controller_base::~_controller_base (void) {}

void _controller_base::turn_camera ( const float angle, const glm::vec3& aix ) {
	_object_controller_matrix = glm::rotate( glm::mat4(1), angle, aix );
}

void _controller_base::move_camera ( const glm::vec3& move_to ) {
	_object_controller_matrix = glm::translate( glm::mat4(1), move_to );
}

void _controller_base::move_object ( const int move ) {
	_object_motion_state = move;
}

