#include "_model_manager.hpp"

_model_manager::_model_manager (void) : _data(), _float_number(0), _vertex_number(0), _triangle_number(0), _vbo(0), _vao(0) {
	/* _data = new GLfloat[18]; */
}


_model_manager::~_model_manager (void) {
	glDeleteBuffers(1, &_vbo);
	_data.clear();
	/* glDisableVertexAttribArray( ATTRIBUTE_INDEX_VERTEX ); */
	/* glDisableVertexAttribArray( ATTRIBUTE_INDEX_NORMAL ); */
}

void _model_manager::initialize_vbo (void) {
	glGenBuffers( 1, &_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, _vbo );
	/* glBufferData( GL_ARRAY_BUFFER,  ( sizeof( float ) * _float_number * 2 ), glm::value_ptr( _data.begin()->x ), GL_STATIC_DRAW ); */
	glBufferData( GL_ARRAY_BUFFER,  ( sizeof( float ) * _float_number * 2 ), _data.data(), GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void _model_manager::initialize_vao (void) {
	glGenVertexArrays( 1, &_vao );
	glBindVertexArray( _vao );

	glBindBuffer( GL_ARRAY_BUFFER, _vbo );

	glEnableVertexAttribArray( ATTRIBUTE_INDEX_VERTEX );
	glVertexAttribPointer( ATTRIBUTE_INDEX_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray( ATTRIBUTE_INDEX_NORMAL );
	glVertexAttribPointer( ATTRIBUTE_INDEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void*)( sizeof( float ) * _float_number ) );

	glBindVertexArray(0);
}

void _model_manager::draw (void) {
	glBindVertexArray( _vao );
	glDrawArrays( GL_TRIANGLES, 0, _vertex_number );
	glBindVertexArray(0);
}

void _model_manager::edit_modedl (void) {
}

bool _model_manager::load_model_data_from_assets ( const std::vector<triangle>& model_data ) {
	//check the scurce
	if(_data.capacity() < model_data.size()) {
		_data.resize(model_data.size());
	}

	if( !model_data.empty() ) {
		_data.clear();
		_data = model_data;
		if( !_data.empty() ) {
		_triangle_number = _data.size() / 2;
		_vertex_number = _triangle_number * 3;
		_float_number = _vertex_number * 3;
		} else {
			std::cerr<<"no model data generate!\n";
		}
		return true;
	} else {
		std::cerr<<"data not gen by model data"<<std::endl;
		return false;
	}
}

void _model_manager::recursiveProcess( aiNode* node, const aiScene* scene ) {
	//process
	/* _data.clear(); */
	std::cout<<node->mNumMeshes;
	for(int i=0;i<node->mNumMeshes;i++) {
		aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
		triangle temp_triangle_one, temp_triangle_two;
		for( int n = 0; n < (mesh->mNumVertices); ++n ) {
			temp_triangle_one.x = glm::vec3(mesh->mVertices[n].x, mesh->mVertices[n].y, mesh->mVertices[n].z);
			temp_triangle_two.x = glm::vec3(mesh->mNormals[n].x, mesh->mNormals[n].y, mesh->mNormals[n].z); ++n;

			temp_triangle_one.y = glm::vec3(mesh->mVertices[n].x, mesh->mVertices[n].y, mesh->mVertices[n].z);
			temp_triangle_two.y = glm::vec3(mesh->mNormals[n].x, mesh->mNormals[n].y, mesh->mNormals[n].z); ++n;

			temp_triangle_one.z = glm::vec3(mesh->mVertices[n].x, mesh->mVertices[n].y, mesh->mVertices[n].z);
			temp_triangle_two.z = glm::vec3(mesh->mNormals[n].x, mesh->mNormals[n].y, mesh->mNormals[n].z);

			_vertex_data.push_back( temp_triangle_one );
			_normal_data.push_back( temp_triangle_two );
		}
	}
	
	//recursion
	for( int i=0; i < node->mNumChildren; i++ ) {
		recursiveProcess( node->mChildren[i], scene );
	}
}

void _model_manager::generate_vertex_data(void) {
	Assimp::Importer importer;
	/* const aiScene* scene = importer.ReadFile( "wolf.dae", aiProcess_GenSmoothNormals ); */
	const aiScene* scene = aiImportFile( "circle.dae", aiProcess_Triangulate );
										/* aiProcess_Triangulate | */
										/* aiProcess_CalcTangentSpace | */
										/* aiProcess_FlipUVs ); */

	if( scene ) {
		_vertex_data.clear();
		_normal_data.clear();

		recursiveProcess( scene->mRootNode, scene );
	} else {
		std::cout<<"can't open *.dae file\n";
	}

	_data.clear();
	_data.insert( _data.end(), _vertex_data.begin(), _vertex_data.end() );
	_data.insert( _data.end(), _normal_data.begin(), _normal_data.end() );

	_vertex_data.clear();
	_normal_data.clear();

	/* _data.clear(); */
	/* cube a; a.generate_cube( glm::vec3( -0.5F, 0.5F, 0.5F ), 1.0F ); */
	/* /1* _data = a.get_data(); *1/ */
	/* a.generate_another_cube( CUBE_SIDE::RIGHT ); */
	/* a.move_to( CUBE_SIDE::LEFT ); */
	/* a.generate_another_cube( CUBE_SIDE::LEFT ); */
	/* a.move_to( CUBE_SIDE::RIGHT ); */
	/* a.generate_another_cube( CUBE_SIDE::BACK ); */
	/* _data = a.get_data(); */

	if( !_data.empty() ) {
		_triangle_number = _data.size()/2;
		_vertex_number = _triangle_number * 3;
		_float_number = _vertex_number * 3;
	} else {
		std::cerr<<"no model data generate!\n";
	}
}

void _model_manager::generate_normal_data (void) {
	/* if( !_data.empty() ) { */
	/* 	triangle temp_triangle; */
	/* 	auto iter = _data.begin(); */
	/* 	for( int i = 0; i < _triangle_number; ++i, ++iter) { */
	/* 		glm::vec3 const & a = iter->x; */
	/* 		glm::vec3 const & b = iter->y; */
	/* 		glm::vec3 const & c = iter->z; */
	/* 		temp_triangle.x = temp_triangle.y = temp_triangle.z = glm::normalize( glm::cross( c - a, b - a ) ); */
	/* 		_data.push_back( temp_triangle ); */
	/* 	} */
	/* } else { */
	/* 	std::cerr<<"normal can't be generated,there is no data in this model!"<<std::endl; */
	/* } */
}

