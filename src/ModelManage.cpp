#include "ModelManage.hpp"

ModelManage::ModelManage():
	StoneData(nullptr)
{}

ModelManage::ModelManage(int i)
{
	generateTestStone();
}

ModelManage::~ModelManage(void)
{
	DeleteModelManage();
}

void ModelManage::InitializeVAO(void)
{
	glGenVertexArrays(1, &lastVAO);
	glBindVertexArray(lastVAO);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbufferobject);

		glEnableVertexAttribArray(ATTRIBUTE_INDEX_VERTEX);
		glVertexAttribPointer(ATTRIBUTE_INDEX_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(ATTRIBUTE_INDEX_NORMAL);
		glVertexAttribPointer(ATTRIBUTE_INDEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(*StoneData)* allFloatDataNum));

	glBindVertexArray(0);
}

void ModelManage::InitializeVertexBuffer(void)
{
	glGenBuffers(1, &vertexbufferobject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferobject);
	glBufferData(GL_ARRAY_BUFFER,  (sizeof(*StoneData)* allFloatDataNum* 2), StoneData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelManage::generateTestStone(void)
{
	testStone01.generateData(6, 5);

	testStone01.generateTriangleData();
	StoneData= new float[testStone01.allfloatDataCount* 2];
	allFloatDataNum= testStone01.allfloatDataCount;

	memcpy(StoneData, testStone01.returnUltimateData(), sizeof(float)* testStone01.allfloatDataCount);

	M3DVector3d temp1, temp2 ,temp3;
	GLuint temp= testStone01.allfloatDataCount;
	for (int i = 0; i < temp; i+= 9)
	{
		temp1[0]= StoneData[i+ 3]- StoneData[i];
		temp1[1]= StoneData[i+ 4]- StoneData[i+ 1];
		temp1[2]= StoneData[i+ 5]- StoneData[i+ 2];

		temp2[0]= StoneData[i+ 6]- StoneData[i];
		temp2[1]= StoneData[i+ 7]- StoneData[i+ 1];
		temp2[2]= StoneData[i+ 8]- StoneData[i+ 2];

		m3dCrossProduct3(temp3, temp2, temp1);
		m3dNormalizeVector3(temp3);
		StoneData[i+ allFloatDataNum]= StoneData[i+ allFloatDataNum+ 3]= StoneData[i+ allFloatDataNum+ 6]= -temp3[0];
		StoneData[i+ allFloatDataNum+ 1]= StoneData[i+ allFloatDataNum+ 3+ 1]= StoneData[i+ allFloatDataNum+ 6+ 1]= -temp3[1];
		StoneData[i+ allFloatDataNum+ 2]= StoneData[i+ allFloatDataNum+ 3+ 2]= StoneData[i+ allFloatDataNum+ 6+ 2]= -temp3[2];
	}
}
