#ifndef _SCENE_BASE_HPP_
#define _SCENE_BASE_HPP_


#include "_object_base.hpp"
#include "_camera_base.hpp"
#include "_shader_manager.hpp"
#include "_light_base.hpp"
#include "_light_base_set.hpp"
#include "_controller_base.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <string>
#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "bullet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.h"
#include "bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "bullet/LinearMath/btQuickprof.h"

enum {NORMAL_SHADER, LIGHT_SOURCE_SHADER};

class _scene_base {
private:
	std::unordered_map<unsigned int, std::shared_ptr<_shader_manager>> _shaders;
	std::list<std::shared_ptr<_camera_base>> _cameras_in_scene;
	std::unordered_map<unsigned int, std::list<std::shared_ptr<_object_base>>> _shaders_and_objects_in_scene;
	std::shared_ptr<_light_base_set> _light_base_set_in_scene;
	std::shared_ptr<_shader_manager> _current_shader;
	std::shared_ptr<_controller_base> _controller_in_scene;

	std::shared_ptr<btDefaultCollisionConfiguration> _collision_configuration;
	std::shared_ptr<btCollisionDispatcher> _dispatcher;
	std::shared_ptr<btDbvtBroadphase> _broadphase;
	std::shared_ptr<btSequentialImpulseConstraintSolver> _solver;
	std::shared_ptr<btDiscreteDynamicsWorld> _physics_world;
	btClock _clock;

	std::list<std::shared_ptr<_camera_base>>::iterator _cameras_in_scene_iter;
	std::unordered_map<unsigned int, std::list<std::shared_ptr<_object_base>>>::iterator _shaders_and_objects_in_scene_iter;
	std::list<std::shared_ptr<_object_base>>::iterator _objects_in_scene_iter;

	glm::vec4 _ambient_color_in_scene;

public:
	_scene_base (void);
	virtual ~_scene_base (void);
	virtual void initilize_scene (void);
	void shader_load ( const std::string shader_file_names, const unsigned int shader_name );
	void add_camera ( _camera_base* camera );
	void add_light ( _light_base* light );
	void add_object ( _object_base* object, const unsigned int shader_name );
	void set_ambient_color ( const glm::vec4 color );
	void load_scene (void);
	void update_scene (void);
	void render_scene (void);
	virtual void edit_scene (void);

	inline glm::vec4 get_ambient_color (void) const { return _ambient_color_in_scene; }
	inline _shader_manager* get_test_shader (void) { return _current_shader.get(); }
	inline _controller_base* get_controller (void) const { return _controller_in_scene.get(); }
	inline btDiscreteDynamicsWorld* get_physics_world (void) const { return _physics_world.get(); }

};	// _scene_base

#endif

