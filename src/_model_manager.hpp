#ifndef _MODEL_MANAGER_HPP_
#define _MODEL_MANAGER_HPP_

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "_shader_manager.hpp"

struct triangles {
	glm::vec3 x, y, z;
};

class _model_manager {
public:
	_model_manager (void);
	~_model_manager (void);

	void initialize_vbo (void);
	void initialize_vao (void);
	void draw (void);
	void generate_vertex_data (void);
	void generate_normal_data (void);
private:
	vector<triangles> _data;
	/* GLfloat* _data; */
	GLuint _float_number;
	GLuint _vertex_number;
	GLuint _triangle_number;
	GLuint _vbo;
	GLuint _vao;
};

#endif

