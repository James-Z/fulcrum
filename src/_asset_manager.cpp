#include "_asset_manager.hpp"

_asset_manager::_asset_manager(void) {}

_asset_manager::~_asset_manager(void) {}

void _asset_manager::read_file ( const std::string& file_name, const unsigned int& format ) {
	switch ( format ) {
	case DAE:
		read_dae( file_name );
		if( !store_model_data( file_name ) ) {
			std::cerr<<"can't store "<<file_name<<" to model data\n";
		}
		break;
	default:
		std::cerr<<"can't read file "<<file_name<<"\n";
	}
}

void _asset_manager::read_dae ( const std::string& file_name ) {
	// Create an instance of the Importer class
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = aiImportFile( file_name.c_str(),
								aiProcess_CalcTangentSpace |
								aiProcess_Triangulate);

	if( scene ) {
		_vertex_data.clear();
		_normal_data.clear();

		recursiveProcess( scene->mRootNode, scene );
	} else {
		std::cout<<"can't open "<<file_name<<"\n";
	}
	if( scene != nullptr ) {
		delete scene;
		scene = nullptr;
	}
}

void _asset_manager::recursiveProcess( const aiNode* node, const aiScene* scene ) {
	/* std::cout<<"aiNode number : "<<node->mNumMeshes<<"\n"; */
	for( int i = 0; i < node->mNumMeshes; ++i ) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
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
	for( int i = 0; i < node->mNumChildren; ++i ) {
		recursiveProcess( node->mChildren[i], scene );
	}
}

bool _asset_manager::store_model_data ( const std::string& file_name ) {
	_model_data.insert( _model_data.end(), _vertex_data.begin(), _vertex_data.end() );
	_model_data.insert( _model_data.end(), _normal_data.begin(), _normal_data.end() );

	bool is_input = false;
	std::string file = file_name;
	if( _models_data.find( file ) == _models_data.end() ) {
		_models_data.insert( std::make_pair( file_name, _model_data ) );

		_model_data.clear();
		_vertex_data.clear();
		_normal_data.clear();
		return true;
	} else {
		std::cerr<<"can't store "<<file_name<<"\n";

		_model_data.clear();
		_vertex_data.clear();
		_normal_data.clear();
		return false;
	}
}

