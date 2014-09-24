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

enum CUBE_SIDE{ FRONT = 1, BACK, LEFT, RIGHT, UP, BOTTOM };

class cube {

	glm::vec3	a,
			b,
			c,
			d;

	glm::vec3	d1,
			c1,
			b1,
			a1;

	glm::vec3 _start_vertex;
	float _side_length;

	triangles _triangle;
	std::vector<triangles> _cube_data;
public:
	struct cube_info {
		glm::vec3 start_vertex;
		float side_length;
	};
	void generate_cube_vertexs ( glm::vec3 start_vertex, float side_length ) {
		float x = start_vertex.x,
			y = start_vertex.y,
			z = start_vertex.z;

		a = glm::vec3(x, y, z);
		b = glm::vec3(x, y - side_length, z);
		c = glm::vec3(x + side_length, y - side_length, z);
		d = glm::vec3(x + side_length, y, z);

		d1 = glm::vec3(x + side_length, y, z - side_length);
		c1 = glm::vec3(x + side_length, y - side_length, z - side_length);
		b1 = glm::vec3(x, y - side_length, z - side_length);
		a1 = glm::vec3(x, y, z - side_length);

	}
	inline std::vector<triangles> get_data ( void ) { return _cube_data; }

	void generate_cude_side ( const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d ) {
		/* _data.clear(); */
		triangles temp_triangle;
		temp_triangle.x = a;
		temp_triangle.y = b;
		temp_triangle.z = c;
		_cube_data.push_back( temp_triangle );

		temp_triangle.x = a;
		temp_triangle.y = c;
		temp_triangle.z = d;
		_cube_data.push_back( temp_triangle );
	}

	void generate_cube ( const glm::vec3& start_vertex, const float& side_length ) {
		_start_vertex = start_vertex;
		_side_length = side_length;
		generate_cube_vertexs ( start_vertex, side_length );

		generate_cude_side( a, b, c, d );
		generate_cude_side( d, c, c1, d1 );
		generate_cude_side( d1, c1, b1, a1 );
		generate_cude_side( a1, b1, b, a );
		generate_cude_side( b, b1, c1, c );
		generate_cude_side( a1, a, d, d1 );
	}

	void move_to ( const int& side ) {
		int sd = side;
		glm::vec3 front(0);
		glm::vec3 left(0);
		glm::vec3 up(0);
		switch( sd ) {
		case CUBE_SIDE::FRONT:
			front = glm::vec3( a.x, a.y, a.z + _side_length );
			generate_cube_vertexs( front, _side_length );
			break;
		case CUBE_SIDE::BACK:
			generate_cube_vertexs( a1, _side_length );
			break;
		case CUBE_SIDE::LEFT:
			left = glm::vec3( a.x - _side_length, a.y, a.z );
			generate_cube_vertexs( left, _side_length );
			break;
		case CUBE_SIDE::RIGHT:
			generate_cube_vertexs( d, _side_length );
			break;
		case CUBE_SIDE::UP:
			up = glm::vec3( a.x, a.y + _side_length, a.z );
			generate_cube_vertexs( up, _side_length );
			break;
		case CUBE_SIDE::BOTTOM:
			generate_cube_vertexs( b, _side_length );
			break;
		}
	}

	void generate_another_cube ( const int& side ) {
		int sd = side;
		glm::vec3 front(0);
		glm::vec3 left(0);
		glm::vec3 up(0);
		switch( sd ) {
		case CUBE_SIDE::FRONT:
			front = glm::vec3( a.x, a.y, a.z + _side_length );
			generate_cube( front, _side_length );
			break;
		case CUBE_SIDE::BACK:
			generate_cube( a1, _side_length );
			break;
		case CUBE_SIDE::LEFT:
			left = glm::vec3( a.x - _side_length, a.y, a.z );
			generate_cube( left, _side_length );
			break;
		case CUBE_SIDE::RIGHT:
			generate_cube( d, _side_length );
			break;
		case CUBE_SIDE::UP:
			up = glm::vec3( a.x, a.y + _side_length, a.z );
			generate_cube( up, _side_length );
			break;
		case CUBE_SIDE::BOTTOM:
			generate_cube( b, _side_length );
			break;
		}
	}
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
public:
	_model_manager (void);
	~_model_manager (void);

	void initialize_vbo (void);
	void initialize_vao (void);
	void draw (void);
	virtual void edit_modedl (void);
	void generate_vertex_data (void);
	void generate_normal_data (void);
	inline const std::vector<triangles>& get_data (void) const { return _data; }
};

#endif

