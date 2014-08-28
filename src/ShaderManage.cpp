#include "ShaderManage.hpp"

GLuint ShaderManage::CreateProgram(const std::vector<GLuint> &shaderList, const std::vector<GLuint> attributeNum)
{
	program = glCreateProgram();

	for(size_t iLoop = 0; iLoop < shaderList.size(); ++iLoop)
		glAttachShader(program, shaderList[iLoop]);

	std::map<GLuint, std::string>::const_iterator mit;
	std::vector<GLuint>::const_iterator vit= attributeNum.begin();
	for(; vit!= attributeNum.end(); ++vit)
	{
		mit= attributeIndex.begin();
		for(; mit!= attributeIndex.end(); ++mit)
		{
			if(mit->first== *vit)
			{
				glBindAttribLocation(program, mit->first, mit->second.c_str());
			}
		}
	}


	glLinkProgram(program);
	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		if(strInfoLog!= nullptr) strInfoLog= nullptr;
	}
	for(size_t iLoop = 0; iLoop < shaderList.size(); ++iLoop)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}

ShaderManage::ShaderManage()
{
	attributeName= new std::string[8];
	attributeName[0]= "vertex";
	attributeName[1]= "color";
	attributeName[2]= "normal";
	attributeName[3]= "texturecoord0";
	attributeName[4]= "texturecoord1";
	attributeName[5]= "texturecoord2";
	attributeName[6]= "texturecoord3";
	attributeName[7]= "attributeIndexLast";
	for(GLint i= 0; i< ATTRIBUTE_INDEX_LAST; ++i)
	{
		attributeIndex[i]= attributeName[i];
	}

}


ShaderManage::~ShaderManage(void)
{
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}


