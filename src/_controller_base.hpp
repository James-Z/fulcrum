#ifndef _CONTROLLER_BASE_HPP_
#define _CONTROLLER_BASE_HPP_

#include "_object_base.hpp"
#include "src/BulletDynamics/Dynamics/btRigidBody.h"
#include "src/LinearMath/btDefaultMotionState.h"
#include "src/LinearMath/btTransform.h"

class _controller_base : public _object_base {
private:
	glm::mat4 _object_controller_matrix;
	glm::mat4 _camera_controller_matrix;
	int _object_motion_state;
public:
	_controller_base (void);
	virtual ~_controller_base (void);

	void turn_camera ( const float angle, const glm::vec3& aix );
	void move_camera ( const glm::vec3& move_to );
	void move_object ( const int move );
	/* void left_rotation (void); */
	/* void right_rotation (void); */

	/* void clock_wise_rotation (void); */
	/* void anti_clock_wise_rotation (void); */

	/* void for_ward (void); */
	/* void back_ward (void); */

	/* void up_ward (void); */
	/* void down_ward (void); */

	inline glm::mat4 get_object_controller_matrix (void) const { return _object_controller_matrix; }
	inline glm::mat4 get_camera_controller_matrix (void) const { return _camera_controller_matrix; }
	inline int get_object_motion_state (void) const { return _object_motion_state; }
	inline void reset_object_motion_state (void) { _object_motion_state = 0; }
};

#endif

