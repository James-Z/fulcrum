#ifndef _OBJECT_BASE_HPP_
#define _OBJECT_BASE_HPP_

#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <bullet/LinearMath/btDefaultMotionState.h>
#include <bullet/LinearMath/btTransform.h>

#include "_shader_manager.hpp"
#include "_model_manager.hpp"
struct control_message {
	int msg;
	int msg_info;

	control_message( int m, int m_i ) : msg(m), msg_info(m_i) {}
};
enum MOTION_STATE {	NO_MOSTION = 0,
			RIGHT_WARD, LEFT_WARD, X_MOVE_STOP,
			UP_WARD, DOWN_WARD, Y_MOVE_STOP,
			FORWORD, BACKWARD, Z_MOVE_STOP,
			UP_ROTATION, DOWN_ROTATION, X_TURN_STOP,
			LEFT_ROTATION, RIGHT_ROTATION, Y_TURN_STOP,
			CLOCK_WISE_ROTATION, ANTI_CLOCK_WISE_ROTATION, Z_TURN_STOP };

class _object_base {
protected:
	_model_manager _model;

	glm::mat4 _matrix_catch_camera_in_world;
	glm::mat4 _matrix_in_world;
	glm::mat4 _matrix_in_camera_world;
	glm::mat4 _matrix_follow_in_world;
	glm::vec4 _position_in_world;
	glm::vec4 _material_diffuse_color;
	glm::vec4 _material_specular_color;

	int _state;
	btVector3 _force;
	btVector3 _angular;
	btVector3 _angular_x;
	btVector3 _angular_y;
	btVector3 _angular_z;
	btScalar _mass;
	btVector3 _inertia;
	std::shared_ptr<btDefaultMotionState> _motion_state;
	std::shared_ptr<btCollisionShape> _shape;
	std::shared_ptr<btRigidBody> _rigid_body;

	int _ID;
	int _be_catched_camera_ID;
	int _be_catched_controller_ID;
	bool _is_destoried;
	bool _is_catch_camera;
	bool _is_be_controlled;

public:
	_object_base (void);
	virtual ~_object_base (void);
	virtual void destory (void);
	//
	void update_matrix_in_camera_world ( const glm::mat4& update_matrix );
	void update_matrix_catch_camera_in_world ( const glm::mat4& update_matrix );
	void multiply_matrix_in_world ( const glm::mat4& matrix );
	void multiply_matrix_follow_in_world ( const glm::mat4& matrix );
	virtual void translate ( const glm::vec3& direction );
	virtual void rotate ( const float& angle, const glm::vec3& rotate_axis );
	void set_position_in_world ( const glm::vec3& position );
	void init_rigid_body ( const btScalar mass, const btVector3 inertia, btCollisionShape* shape );
	//
	void draw (void);
	void update_gl_uniform ( const _shader_manager& be_using_shader );
	virtual void follow ( const _object_base* be_followed_object, bool is_rotate = false );
	virtual void update (void);
	//
	void apply_physics (void);
	void move_and_turn ( const std::vector<control_message>& msg );
	void apply_physics_transform_update (void);
	//
	inline void set_ID ( const unsigned int ID ) { _ID = ID; }
	inline void catch_camera ( const unsigned int camera_ID ) { _is_catch_camera = true; _be_catched_camera_ID = camera_ID; }
	inline void catch_contrtoller ( void ) { _is_be_controlled = true; }
	/* inline void catch_contrtoller ( const unsigned int controller_ID ) { _is_be_controlled = true; _be_catched_controller = controller_ID; } */
	inline void realse_camera (void) { _is_catch_camera = false; }
	inline void realse_controller (void) { _is_be_controlled = false; }
	inline void set_matrix_in_world ( const glm::mat4& matrix ) { _matrix_in_world = matrix; }
	inline glm::mat4 get_matrix_in_world (void) const { return _matrix_in_world * _matrix_follow_in_world; }
	inline glm::mat4 get_matrix_in_camera_world (void) const { return _matrix_in_camera_world; }
	inline glm::mat4 get_matrix_follow_in_world (void) const { return _matrix_follow_in_world; }
	inline glm::vec4 get_local_position_in_world (void) const { return glm::vec4( glm::vec3( _matrix_in_world[3] ), 1.0F ); }
	inline btRigidBody* get_rigidbody (void) const { return _rigid_body.get(); }
	inline int get_ID (void) const { return _ID; }
	inline int be_catched_camera_ID (void) const { return _be_catched_camera_ID; }
	inline bool is_destory (void) const { return _is_destoried; }
	inline bool is_catch_camera (void) const { return _is_catch_camera; }
	inline bool is_be_controlled (void) const { return _is_be_controlled; }
	inline void generate_model (void) { _model.generate_vertex_data(); _model.generate_normal_data(); _model.initialize_vbo(); _model.initialize_vao(); }
	/* inline void generate_model (void) { _model.generate_vertex_data(); _model.initialize_vbo(); _model.initialize_vao(); } */
	inline const std::vector<triangles>& get_model_data(void) const { _model.get_data(); }
	inline void set_material_diffuse_color ( const glm::vec4& color ) { _material_diffuse_color = color; }
	inline void set_material_specular_color ( const glm::vec4& color ) { _material_specular_color = color; }

};	// _object_base

#endif

