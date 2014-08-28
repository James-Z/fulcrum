#pragma once
#include "math3d.h"
#include <iostream>
#include <stack>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace glm;
using namespace std;

class MatrixStack
{
public:
	MatrixStack(void)
	{
		m3dLoadIdentity44(_currentMatrix);
		_front= vec3(0.0, 0.0, 1.0);
		_up= vec3(0.0, 1.0, 0.0);
		_cameraMatrix= mat4(1.0);
		_cameraRotationMatrix= mat4(1.0);
		_cameraTranslateMatrix= mat4(1.0);
	}

	~MatrixStack(void)
	{}

	inline void PushMatrix(void)
	{
		_matrixStack.push(_currentMatrix);
	}

	inline void PopMatrix(void)
	{
		if(!_matrixStack.empty())
		{
			_matrixStack.pop();
			if (!_matrixStack.empty())
			{
				memcpy(_currentMatrix, _matrixStack.top(), sizeof(M3DMatrix44f));
			}
			else
			{
				m3dLoadIdentity44(_currentMatrix);
			}
		}
		else
		{
			m3dLoadIdentity44(_currentMatrix);
			std::cout<<"The MatrixStack has been Clear"<<std::endl;
		}
	}

	inline void Scale(float x, float y, float z)
	{
		M3DMatrix44f mScale;
		m3dScaleMatrix44(mScale, x, y, z);
		m3dMatrixMultiply44(_currentMatrix, _currentMatrix, mScale);
	}

	inline void Translate(float x, float y, float z) 
	{
		M3DMatrix44f mTran;
		m3dTranslationMatrix44(mTran, x, y, z);
		m3dMatrixMultiply44(_currentMatrix, _currentMatrix, mTran);
	}

	void Rotate(float angle, float x, float y, float z)
	{
		M3DMatrix44f mRotate;
		m3dRotationMatrix44(mRotate, float(m3dDegToRad(angle)), x, y, z);
		//m3dCopyMatrix44(mTemp, _currentMatrix);
		m3dMatrixMultiply44(_currentMatrix, _currentMatrix, mRotate);
	}

	inline M3DMatrix44f &GetCurrentMatrix(void)
	{
		return _currentMatrix;
	}

	inline M3DMatrix33f &GetNormalMatrix(void)
	{
		m3dExtractRotationMatrix33(_normalMatrix, _currentMatrix);
		m3dNormalizeVector3(&_normalMatrix[0]);
		m3dNormalizeVector3(&_normalMatrix[3]);
		m3dNormalizeVector3(&_normalMatrix[6]);
		return _normalMatrix;
	}


	inline M3DMatrix44f &GetPerspectiveMatrix(void)
	{
		return _perspectiveMatrix;
	}

	inline void Frustum(float *matrix, float left, float right, float bottom, float top, float znear, float zfar)
	{
		float temp, temp2, temp3, temp4;
		temp = 2.0 * znear;
		temp2 = right - left;
		temp3 = top - bottom;
		temp4 = zfar - znear;
		matrix[0] = temp / temp2;
		matrix[1] = 0.0;
		matrix[2] = 0.0;
		matrix[3] = 0.0;
		matrix[4] = 0.0;
		matrix[5] = temp / temp3;
		matrix[6] = 0.0;
		matrix[7] = 0.0;
		matrix[8] = (right + left) / temp2;
		matrix[9] = (top + bottom) / temp3;
		matrix[10] = (-zfar - znear) / temp4;
		matrix[11] = -1.0;
		matrix[12] = 0.0;
		matrix[13] = 0.0;
		matrix[14] = (-temp * zfar) / temp4;
		matrix[15] = 0.0;
	}

	inline void Perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar)
	{
		M3DMatrix44f mProjection, testMat44;
		m3dLoadIdentity44(testMat44);
		float ymax, xmax;
		float PI= 3.1415926;
		float temp, temp2, temp3, temp4;
		ymax = znear * tanf(fovyInDegrees * PI / 360.0);
		//ymin = -ymax;
		//xmin = -ymax * aspectRatio;
		xmax = ymax * aspectRatio;
		Frustum(mProjection, -xmax, xmax, -ymax, ymax, znear, zfar);
		
		m3dMatrixMultiply44(mProjection, mProjection, testMat44);

		m3dCopyMatrix44(_perspectiveMatrix, mProjection);
	}

	inline void ApplyCameraTransform(float x, float y, float z)
	{
		Translate(x, y, z);
	}

	inline void LeftRotation(float angleLeft) {
		_angleUp= -angleLeft;

		_cameraRotationMatrix= rotate(mat4(1.0), _angleUp, _up);
		_cameraMatrix= _cameraRotationMatrix* _cameraMatrix;
	}
	inline void RightRotation(float angleRight) {
		_angleUp= angleRight;

		_cameraRotationMatrix= rotate(mat4(1.0), _angleUp, _up);
		_cameraMatrix= _cameraRotationMatrix* _cameraMatrix;
	}

	inline void ClockWiseRotation(float angleClockWise) {
		_angleFront= angleClockWise;

		_cameraRotationMatrix= rotate(mat4(1.0), _angleFront, _front);
		_cameraMatrix= _cameraRotationMatrix* _cameraMatrix;
	}
	inline void AntiClockWiseRotation(float angleAntiClock) {
		_angleFront= -angleAntiClock;

		_cameraRotationMatrix= rotate(mat4(1.0), _angleFront, _front);
		_cameraMatrix= _cameraRotationMatrix* _cameraMatrix;
	}

	inline void ForWard(float forwardSpeed) {
		_speedFront= forwardSpeed;

		//vec3 _right= cross(_up, _front);

		_cameraTranslateMatrix= translate(mat4(1.0), vec3(0.0, 0.0, _speedFront));
		_cameraMatrix= _cameraTranslateMatrix * _cameraMatrix;

	}
	inline void BackWard(float BackwardSpeed) {
		_speedFront= -BackwardSpeed;

		_cameraTranslateMatrix= translate(mat4(1.0), vec3(0.0, 0.0, _speedFront));
		_cameraMatrix= _cameraTranslateMatrix* _cameraMatrix;
	}

	inline void UpWard(float UpWardSpeed) {
		_speedUp= -UpWardSpeed;

		_cameraTranslateMatrix= translate(mat4(1.0), vec3(0.0, _speedUp, 0.0));
		_cameraMatrix= _cameraTranslateMatrix* _cameraMatrix;
	}
	inline void DownWard(float DownWardSpeed) {
		_speedUp= DownWardSpeed;

		_cameraTranslateMatrix= translate(mat4(1.0), vec3(0.0, _speedUp, 0.0));
		_cameraMatrix= _cameraTranslateMatrix* _cameraMatrix;
	}

	inline void Camera() {
		m3dMatrixMultiply44(_currentMatrix, _currentMatrix, value_ptr(_cameraMatrix));
	}

private:
        M3DMatrix44f _currentMatrix;
	M3DMatrix44f _perspectiveMatrix;
	M3DMatrix33f _normalMatrix;
	vec3 _front;
	vec3 _up;
	float _angleUp;
	float _angleFront;
	float _speedFront;
	float _speedUp;
	mat4 _cameraRotationMatrix;
	mat4 _cameraTranslateMatrix;
	mat4 _cameraMatrix;
	std::stack<float*> _matrixStack;
};
