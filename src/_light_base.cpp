#include "_light_base.hpp"

_light_base::_light_base (void) : _object_base(), _diffuse_color(), _light_position() {}

_light_base::~_light_base (void) {}

void _light_base::set_diffuse_color ( glm::vec3 color ) {
	_diffuse_color = glm::vec4( color, 1.0F);
}

void _light_base::set_specular_color ( glm::vec3 color ) {
	_specular_color = glm::vec4( color, 1.0F);
}

