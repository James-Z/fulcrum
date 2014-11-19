#ifndef _CIRCLE_HPP_
#define _CIRCLE_HPP_

#include "_object_base.hpp"
#include "masset_manage.hpp"

#include <bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>

class circle : public _object_base {
	std::shared_ptr<btTriangleMesh> triangle_mesh;
	std::shared_ptr<btGImpactMeshShape> tmpshape;
	/* std::shared_ptr<btConvexHullShape> tmpshape1; */

	void initial_circle (void);
public:
	circle (void);

	~circle (void);

};

#endif

