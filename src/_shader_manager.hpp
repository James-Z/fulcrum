#ifndef _SHADER_MANAGER_HPP_
#define _SHADER_MANAGER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>

#include "ShaderManage.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

class _shader_manager {
private:
	ShaderManage _shaderManage;
	GLuint _shader;
	std::unordered_map<std::string, GLuint> _uniformNames;

private:
	void _extractNameFromString (std::vector<std::string>& extractNames, const std::string originNames);
	void _bind_uniform_variable_to_shader (void);
public:
	GLuint object_transforms,
	       camera_transforms,
	       normal_transforms,
	       light_transforms,
	       perspective_transforms,
	       light_position,
	       diffuse_color,
	       ambient_color,
	       specular_color,
	       lights_count,
	       light_color,
	       material_diffuse_color,
	       material_specular_color;
public:
	_shader_manager (void);
	virtual ~_shader_manager (void);
	void set_uniform_location ( const std::string names );
	GLuint create_shader ( const std::string shaderSourceName ) ;

	inline GLuint uniform_name ( const std::string uniformNamesInShader ) const { return _uniformNames.at( uniformNamesInShader.c_str() ); }
	inline GLuint get_shader (void) const { return _shader; }

};	//ManageGraph

#endif

