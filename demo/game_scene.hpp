#ifndef _GAME_SCENE_HPP_
#define _GAME_SCENE_HPP_

#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
/* #include <GL/gl.h> */
#include <GL/glx.h>

#include "_scene_base.hpp"
#include "_object_base.hpp"
#include "_shader_manager.hpp"
#include "_asset_manager.hpp"

#include <bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
//
#include "circle.hpp"

class game_scene : public _scene_base {
public:
	game_scene(void);
	~game_scene(void);

	void start (void) override;
	void update (void) override;
};

#endif

