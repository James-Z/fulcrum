#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "math3d.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "AttributeIndex.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SolidStone.hpp"

typedef struct
{
	float x, y, z;
}MyPOINT;

static SolidStone testStone01;
		

class ModelManage
{
public:
inline void ModelManage::DeleteModelManage(void)
{
	glDeleteBuffers(1, &vertexbufferobject);
	if (StoneData!= nullptr)
	{
		delete []StoneData;
		StoneData= nullptr;
	}
}

