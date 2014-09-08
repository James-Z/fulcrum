#include "_light_base_set.hpp"

_light_base_set::_light_base_set (void) : _lights(), _diffuse_colors() {}

_light_base_set::~_light_base_set (void) {
	_lights.clear();
}

void _light_base_set::add_light ( _light_base* light ) {
	_lights.push_back( shared_ptr<_light_base>( light ) );
}

void _light_base_set::update_lights (void) {
	_lights_iter = _lights.begin();
	for( ; _lights_iter != _lights.end(); ++_lights_iter ) {
		(*_lights_iter)->update();

		if( (*_lights_iter)->is_destory() ) {
			(*_lights_iter)->destory();
			_lights.erase( _lights_iter );
		}
	}
}

void _light_base_set::update_lights_data ( const glm::mat4& update_matrix ) {
	_diffuse_colors.clear();
	_specular_colors.clear();
	_lights_positions.clear();
	_lights_iter = _lights.begin();
	int count = 0;
	for( ; _lights_iter != _lights.end(); ++_lights_iter, ++count ) {
		_diffuse_colors.push_back( (*_lights_iter)->get_diffuse_color() );
		_specular_colors.push_back( (*_lights_iter)->get_specular_color() );

		(*_lights_iter)->update_matrix_in_camera_world( update_matrix );
		_lights_positions.push_back( vec3((*_lights_iter)->get_matrix_in_camera_world()[3]) );
	}
	_lights_count = count;
}

void _light_base_set::update_lights_data_to_gl_uniform ( const _shader_manager& be_using_shader ) {
	glUniform4fv( be_using_shader.diffuse_color, _lights_count,
			glm::value_ptr( _diffuse_colors[0] ) );
	glUniform4fv( be_using_shader.specular_color, _lights_count,
			glm::value_ptr( _specular_colors[0] ) );
	glUniform3fv( be_using_shader.light_position, _lights_count,
			glm::value_ptr( _lights_positions[0] ) );
	glUniform1i( be_using_shader.lights_count, _lights_count );
}

