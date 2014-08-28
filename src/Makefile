OBJS = s/*.o fulcrum.o math3d.o MatrixStack.o ShaderManage.o MatrixStack.o ManageGraph.o _scene_base.o _object_base.o _light_base.o _shader_manager.o _camera_base.o _controller_base.o _model_manager.o _light_base_set.o
HDRS = ogl.hpp MatrixStack.hpp ShaderManage.hpp math3d.h MatrixStack.hpp
SCRS = fulcrum.cpp math3d.cpp MatrixStack.cpp ShaderManage.cpp ogl.cpp MatrixStack.cpp
LS = -lGL -lX11 -lGLEW -lGLU -std=c++11
fulcrum : $(OBJS)
	g++ -g -o fulcrum $(OBJS) $(LS)

fulcrum.o : fulcrum.cpp fulcrum.hpp
	g++ -g -c fulcrum.cpp $(LS)

math3d.o : math3d.cpp math3d.h
	g++ -g -c math3d.cpp $(LS)

MatrixStack.o : MatrixStack.cpp MatrixStack.hpp
	g++ -g -c MatrixStack.cpp $(LS)

ShaderManage.o : ShaderManage.cpp ShaderManage.hpp
	g++ -g -c ShaderManage.cpp $(LS)

ManageGraph.o : ManageGraph.cpp ManageGraph.hpp
	g++ -g -c ManageGraph.cpp $(LS)

_scene_base.o : _scene_base.cpp _scene_base.hpp
	g++ -g -c _scene_base.cpp $(LS)

_object_base.o : _object_base.cpp _object_base.hpp
	g++ -g -c _object_base.cpp $(LS)

_camera_base.o : _camera_base.cpp _camera_base.hpp
	g++ -g -c _camera_base.cpp $(LS)

_shader_manager.o : _shader_manager.cpp _shader_manager.hpp
	g++ -g -c _shader_manager.cpp $(LS)

_controller_base.o : _controller_base.cpp _controller_base.hpp
	g++ -g -c _controller_base.cpp $(LS)

_model_manager.o : _model_manager.cpp _model_manager.hpp
	g++ -g -c _model_manager.cpp $(LS)

_light_base.o : _light_base.cpp _light_base.hpp
	g++ -g -c _light_base.cpp $(LS)
	
_light_base_set.o : _light_base_set.cpp _light_base_set.hpp
	g++ -g -c _light_base_set.cpp $(LS)

.PHONY : clean

clean :
	rm fulcrum *.o
