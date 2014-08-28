#include "ogl.hpp"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

ShaderManage shadermanage;
GLuint shader;
vector<GLuint> attribute;

void init() {
        attribute.push_back(0);
        attribute.push_back(1);

        shader = shadermanage.CreateVFShaderProgram("testvert.vert", "testfrag.frag", attribute);

        cout<<glewGetString(GLEW_VERSION)<<" finish"<<endl;
}

int main(int argc, char** argv) {
        cout<<"begin testshadermanage:"<<endl;
        GLenum err = glewInit();

        if (err != GLEW_OK) {
                cout<<glewGetErrorString(err)<<endl;
                exit(1);
        }

        cout<<glewGetString(GLEW_VERSION)<<" finish"<<endl;
        init();

        return 0;
}

