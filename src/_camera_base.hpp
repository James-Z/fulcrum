#ifndef _CAMERA_BASE_HPP_
#define _CAMERA_BASE_HPP_

#include <iostream>

#include "_object_base.hpp"
#include "_shader_manager.hpp"
#include "MatrixStack.hpp"
#include <vector>
#include <unordered_map>
#include <list>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class _camera_base : public _object_base {
private:
	glm::mat4 _perspective_matrix;
public:
	_camera_base (void);
	virtual ~_camera_base (void);

	void perspective (float fovy, float aspect, float zNear, float zFar);
	virtual void update_camera_matrix_from_object ( const glm::mat4& object_matrix );
	virtual void update_camera_matrix ( const glm::mat4& update_matrix );
	void update_camera_matrix_follow_in_world_gl_uniform ( const _shader_manager& be_using_shader );
	void update_camera_perspective_matrix_gl_uniform ( const _shader_manager& be_using_shader );
	void translate ( const glm::vec3& direction ) override;
	void rotate ( const float& angle, const glm::vec3& rotate_axis ) override;

	void follow ( const _object_base* be_followed_object, bool only_position = false ) override;
	void update (void) override;

	/* virtual inline glm::mat4 get_camera_matrix (void) const { return _camera_matrix; } */
	inline glm::mat4 get_perspective (void) const { return _perspective_matrix; }
};

#endif

