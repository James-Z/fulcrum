#ifndef _LIGHT_BASE_HPP_
#define _LIGHT_BASE_HPP_

#include <iostream>

#include "_object_base.hpp"
#include <vector>
#include <unordered_map>
#include <list>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class _light_base : public _object_base {
private:
	glm::vec4 _diffuse_color,
	_ambient_color,
	_specular_color,
	_light_position;
public:
	_light_base (void);
	virtual ~_light_base (void);

	void set_diffuse_color ( glm::vec3 color );
	void set_specular_color ( glm::vec3 color );

	inline glm::vec4 get_diffuse_color (void) const { return _diffuse_color; }
	inline glm::vec4 get_specular_color (void) const { return _specular_color; }
};

#endif

