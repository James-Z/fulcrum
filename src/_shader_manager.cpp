#include "_shader_manager.hpp"

_shader_manager::_shader_manager (void) : _shaderManage (), _shader (), _uniformNames () {}

_shader_manager::~_shader_manager (void) {}

/**
 * this shoudn't be here. be better in a function toolkit
**/
void _shader_manager::_extractNameFromString (std::vector<std::string>& extractNames, const std::string originNames) {
	std::string tempName = originNames;

	std::size_t found = tempName.find_first_of (" ");
	if (found != std::string::npos) {
		extractNames.push_back(std::string (tempName.begin (), tempName.begin () + found));
		_shader_manager::_extractNameFromString ( extractNames, std::string( tempName.begin() + ( found + 1 ), tempName.end() ) );
	} else {
		extractNames.push_back (originNames);
	}

}	//_extractShaderSourceName

void _shader_manager::_bind_uniform_variable_to_shader (void) {
#define CHANGE(name) #name
	object_transforms = glGetUniformLocation (_shader, CHANGE (object_transforms));
	camera_transforms = glGetUniformLocation (_shader, CHANGE (camera_transforms));
	normal_transforms = glGetUniformLocation (_shader, CHANGE (normal_transforms));
	light_transforms = glGetUniformLocation (_shader, CHANGE (light_transforms));
	perspective_transforms = glGetUniformLocation (_shader, CHANGE (perspective_transforms));
	light_position = glGetUniformLocation (_shader, CHANGE (light_position));
	light_color = glGetUniformLocation (_shader, CHANGE (light_color));
	diffuse_color = glGetUniformLocation (_shader, CHANGE (diffuse_color));
	ambient_color = glGetUniformLocation (_shader, CHANGE (ambient_color));
	specular_color = glGetUniformLocation (_shader, CHANGE (specular_color));
	lights_count = glGetUniformLocation (_shader, CHANGE (lights_count));
	material = glGetUniformLocation (_shader, CHANGE (material));
#undef CHANGE
}

void _shader_manager::set_uniform_location (const std::string names/**the max in string**/) {
	std::vector<std::string> uniformNamesInShader;
	_extractNameFromString (uniformNamesInShader, names);
	auto uniformNamesInShader_iter = uniformNamesInShader.begin ();

	for (; uniformNamesInShader_iter != uniformNamesInShader.end (); ++ uniformNamesInShader_iter) {
		 _uniformNames.insert (std::pair<std::string, GLuint> (*uniformNamesInShader_iter,
					 glGetUniformLocation ( _shader, uniformNamesInShader_iter->c_str() ) ) );
	}
}	//GetUniformLocation

//Create shader program and save shader name to "_shader", use Shader() get shader name
GLuint _shader_manager::create_shader (const std::string shaderSourceName) {
	std::vector<std::string> shaderNames;
	_extractNameFromString (shaderNames, shaderSourceName);

	std::vector<GLuint> attributeInfo;
	attributeInfo.push_back (ATTRIBUTE_INDEX_VERTEX);
	attributeInfo.push_back (ATTRIBUTE_INDEX_NORMAL);
	_shader = _shaderManage.CreateVFShaderProgram (shaderNames.at(0), shaderNames.at(1), attributeInfo);
	_bind_uniform_variable_to_shader();

	return _shader;
	//std::cout<<shaderNames.at(0)<<shaderNames.at(1)<<std::endl;
}	//CreateShader


