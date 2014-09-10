#ifndef _MODEL_MANAGER_HPP_
#define _MODEL_MANAGER_HPP_

#include <iostream>
#include <vector>

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
private:
	std::vector<triangles> _data;
	/* GLfloat* _data; */
	GLuint _float_number;
	GLuint _vertex_number;
	GLuint _triangle_number;
	GLuint _vbo;
	GLuint _vao;
	void generate_cude_side ( glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d );
	void generate_cube_vertexs ( glm::vec3 start_vertex, float side_length );
public:
	_model_manager (void);
	~_model_manager (void);

	void initialize_vbo (void);
	void initialize_vao (void);
	void draw (void);
	void generate_vertex_data (void);
	void generate_normal_data (void);
};

#endif

