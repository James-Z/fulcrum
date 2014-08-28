#ifndef _LIGHT_BASE_SET_HPP_
#define _LIGHT_BASE_SET_HPP_

#include <iostream>

#include "_shader_manager.hpp"
#include "_light_base.hpp"
#include <vector>
#include <unordered_map>
#include <list>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class _light_base_set {
private:
	std::list<_light_base*> _lights;

	std::vector<glm::vec4> _diffuse_colors;
	std::vector<glm::vec4> _specular_colors;
	std::vector<glm::vec3> _lights_positions;
	int _lights_count;

	std::list<_light_base*>::iterator _lights_iter;
public:
	_light_base_set ( void );
	virtual ~_light_base_set ( void );
	void add_light ( _light_base* light );
	void update_lights (void);
	void update_lights_data ( const glm::mat4& update_matrix );
	void update_lights_data_to_gl_uniform ( const _shader_manager& be_using_shader );

	inline std::list<_light_base*> get_lights ( void ) const { return _lights; }
};

#endif

