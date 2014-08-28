#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "MatrixStack.hpp"
#include "ShaderManage.hpp"
#include "ManageGraph.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

class ManageGraph {

private:
	ShaderManage _shaderManage;
	GLuint _shader;
	std::unordered_map<std::string, GLuint> _uniformNames;

private:
	void _extractNameFromString (std::vector<std::string>& extractNames, const std::string originNames);
public:
	GLuint Shader (const std::string shaderSourceName);
	GLuint UniformName (const std::string uniformInShader);
public:
	ManageGraph (void);
	GLuint CreateShader (const std::string shaderSourceName);
	void GetUniformLocation (const std::string names);
	virtual void Draw (void);

};	//ManageGraph

