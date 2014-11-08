OBJS = fulcrum.o math3d.o ShaderManage.o _scene_base.o _object_base.o _light_base.o \
_shader_manager.o _camera_base.o _controller_base.o _model_manager.o \
_light_base_set.o _asset_manager.o
HDRS =
SCRS =
LS = -I/usr/local/include/bullet/ -lSDL2 -lassimp -Wl,-rpath=/usr/local/lib  -lGLEW \
-std=c++11 -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath
fulcrum : $(OBJS)
	g++ -g -o fulcrum $(OBJS) $(LS)

fulcrum.o : fulcrum.cpp
	g++ -g -c fulcrum.cpp $(LS)

math3d.o : math3d.cpp math3d.h
	g++ -g -c math3d.cpp $(LS)

ShaderManage.o : ShaderManage.cpp ShaderManage.hpp
	g++ -g -c ShaderManage.cpp $(LS)

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

_asset_manager.o : _asset_manager.cpp _asset_manager.hpp
	g++ -g -c _asset_manager.cpp $(LS)

_model_manager.o : _model_manager.cpp _model_manager.hpp
	g++ -g -c _model_manager.cpp $(LS)

_light_base.o : _light_base.cpp _light_base.hpp
	g++ -g -c _light_base.cpp $(LS)
	
_light_base_set.o : _light_base_set.cpp _light_base_set.hpp
	g++ -g -c _light_base_set.cpp $(LS)

.PHONY : clean

clean :
	rm fulcrum *.o
