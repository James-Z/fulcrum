#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <GL/glew.h>
#include "AttributeIndex.hpp"

class ShaderManage
{
private:
	GLuint program;
	GLuint shader;
	std::vector<GLuint> shaderList;
	std::map<GLuint, std::string> attributeIndex;
	std::string* attributeName;

protected:
	std::string FindFileOrThrow( const std::string &strBasename)
	{
		std::string strFilename= strBasename;
		std::ifstream testFile(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		
		//strFilename = strBasename;
		//testFile.open(strFilename.c_str());
		//if(testFile.is_open())
		//	return strFilename;

		//throw
		std::cerr<<"Could not find the file " <<strBasename;
	}

	inline GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
	{
		std::string strFilename = FindFileOrThrow(strShaderFile);
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();
		std::string shaderDataCopy= shaderData.str();
		const char *strFileData = shaderDataCopy.c_str();

		/* std::cout<<strFileData<<std::endl; */

		shader = glCreateShader(eShaderType);

		glShaderSource(shader, 1, &strFileData, nullptr);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);

			const char *strShaderType = nullptr;
			switch(eShaderType)
			{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}

			fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
			if(strInfoLog!= nullptr) strInfoLog= nullptr;
		}

		return shader;
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList, const std::vector<GLuint> attributeNum);

public:
	ShaderManage(void);
	~ShaderManage(void);

	inline void GetShader(GLenum eShaderType1, GLenum eShaderType2,const std::string &strVertexFile, const std::string &strFragmentFile)
	{
		shaderList.push_back(CreateShader(eShaderType1, strVertexFile));
		shaderList.push_back(CreateShader(eShaderType2, strFragmentFile));
	}

	inline void GetShader(GLenum eShaderType, const std::string &strVertexFile)
	{
		shaderList.push_back(CreateShader(eShaderType, strVertexFile));
	}

	inline GLuint CreateVFShaderProgram(const std::string &strVertexFile, const std::string &strFragmentFile, const std::vector<GLuint> attributeNum)
	{
		shaderList.push_back(CreateShader(GL_VERTEX_SHADER, strVertexFile));
		shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentFile));
		return CreateProgram(shaderList, attributeNum);
	}

	//inline GLuint CreateProgram(void)
	//{
	//	return CreateProgram(shaderList);
	//}
//
};

