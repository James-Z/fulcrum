#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "MatrixStack.hpp"
#include "ShaderManage.hpp"
#include "ManageGraph.hpp"

#include <vector>
#include <stdio.h>
#include <iostream>

#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

GLfloat AxisX(0.0F), AxisZ(0.0F);
unsigned int shadertest;
ManageGraph shaderManage;
std::vector<GLuint> attributeInfo;
//Uniform
GLuint	tranUnif,
	persUnif,
	camUnif,
	norMaUnif,
	diffColorUnif,
	ambientColorUnif,
	specularColorUnif,
	lightPosUnif,
	lightPosMaUnif,
	diffMaterialUnif,
	lightColorUnif,
	cameraPosMaUnif;

MatrixStack trantest;

//Model
GLuint modelbuffer(0),
       vao(0);
GLfloat *triangle = new GLfloat [18];

GLfloat offsety(0.0F);
GLfloat offsetx(0.0F);
GLfloat offsetz(-3.0F);
GLfloat ration(0.0F);

void initprog (void);
void initmodel (void);
void drawtriangle (void);
void InitOGL (void);
void DrawAQuad (void);


