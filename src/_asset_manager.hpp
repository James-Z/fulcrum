#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <iostream>
#include <vector>
#include <string>

/* #include <GL/gl.h> */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "_shader_manager.hpp"

struct triangles {
	glm::vec3 x, y, z;
};


class _asset_manager {
private:
	std::map<std::string, std::vector<triangles>> _models_data;
	std::vector<triangles> _model_data;

	std::map<std::string, std::vector<triangles>>::iterator _models_data_iter;
	std::vector<triangles>::iterator _model_data_iter;
public:
	_asset_manager (void);
	virtual ~_asset_manager (void);
	void read_data ( const std::string&, unsigned int ) const;
	const std::vector<triangles>& read_dae ( const std::string& ) const;
	const std::vector<triangles>& get_model_data ( const std::string& ) const { return _model_data; }
};

#endif

