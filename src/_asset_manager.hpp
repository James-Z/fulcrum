#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>

/* #include <GL/gl.h> */
#include <GL/glew.h>
#include <GL/gl.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>        // Plain-C interface

#include "_shader_manager.hpp"

enum FILE_FORMAT { DAE = 1 };

struct triangle {
	glm::vec3 x, y, z;
	triangle (void) : x(), y(), z() {}
	triangle ( const glm::vec3& x_, const glm::vec3& y_, const glm::vec3& z_ ) : x(x_), y(y_), z(z_) {}
	triangle ( const triangle& right) : x(right.x), y(right.y), z(right.z) {}
	triangle& operator= ( const triangle& right ) {
		this->x = right.x;
		this->y = right.y;
		this->z = right.z;
		return *this;
	}
};


class _asset_manager {
private:
	std::map<std::string, std::vector<triangle>> _models_data;
	std::vector<triangle> _model_data;
	std::vector<triangle> _vertex_data;
	std::vector<triangle> _normal_data;
	GLuint _float_number;
	GLuint _vertex_number;
	GLuint _triangle_number;

	std::map<std::string, std::vector<triangle>>::iterator _models_data_iter;
	std::vector<triangle>::iterator _model_data_iter;
public:
	_asset_manager (void);
	virtual ~_asset_manager (void);

	void read_file ( const std::string&, const unsigned int& );
	void read_dae ( const std::string& );
	void recursiveProcess ( const aiNode*, const aiScene* );
	bool store_model_data ( const std::string& );
	const std::vector<triangle>& get_model_data ( const std::string& model_name ) {
		if( !_models_data.empty() ) {
			const std::vector<triangle>& temp_data( _models_data.find( model_name )->second );
			return temp_data;
		} else {
			std::cerr<<"models data is empty!"<<std::endl;
		}
	}
};

#endif

