#include "ManageGraph.hpp"

ManageGraph::ManageGraph (void) : _shaderManage(), _shader(), _uniformNames() {}

/**
 * this shoudn't be here. be better in a function toolkit
**/
void ManageGraph::_extractNameFromString (std::vector<std::string>& extractNames, const std::string originNames) {
	std::string tempName = originNames;

	std::size_t found = tempName.find_first_of(" ");
	if(found != std::string::npos) {
		extractNames.push_back(std::string(tempName.begin(), tempName.begin() + found));
		ManageGraph::_extractNameFromString(extractNames, std::string(tempName.begin() + (found + 1), tempName.end()));
	} else {
		extractNames.push_back(originNames);
	}

}	//_extractShaderSourceName

GLuint ManageGraph::Shader (const std::string shaderSourceName) {
	return _shader;
}

GLuint ManageGraph::UniformName (const std::string uniformNamesInShader) {
	return _uniformNames.at(uniformNamesInShader.c_str());
}

//Create shader program and save shader name to "_shader", use Shader() get shader name
GLuint ManageGraph::CreateShader (const std::string shaderSourceName) {
	std::vector<std::string> shaderNames;
	_extractNameFromString (shaderNames, shaderSourceName);

	std::vector<GLuint> attributeInfo;
	attributeInfo.push_back (ATTRIBUTE_INDEX_VERTEX);
	attributeInfo.push_back (ATTRIBUTE_INDEX_NORMAL);
	_shader = _shaderManage.CreateVFShaderProgram (shaderNames.at(0), shaderNames.at(1), attributeInfo);

	return _shader;
	//std::cout<<shaderNames.at(0)<<shaderNames.at(1)<<std::endl;
}	//CreateShader

void ManageGraph::GetUniformLocation (const std::string names/**the max in string**/) {
	std::vector<std::string> uniformNamesInShader;
	_extractNameFromString(uniformNamesInShader, names);
	auto uniformNamesInShader_iter = uniformNamesInShader.begin();
	for (; uniformNamesInShader_iter != uniformNamesInShader.end(); ++uniformNamesInShader_iter) {
		 _uniformNames.insert (std::pair<std::string, GLuint> (*uniformNamesInShader_iter, 
					 glGetUniformLocation (_shader, (*uniformNamesInShader_iter).c_str())));
	}
}	//GetUniformLocation

void ManageGraph::Draw (void) {}

