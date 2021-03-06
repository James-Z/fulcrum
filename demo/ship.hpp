#ifndef _SHIP_HPP_
#define _SHIP_HPP_

#include "_object_base.hpp"
#include "masset_manage.hpp"

#include <bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>

class ship : public _object_base {
	std::shared_ptr<btTriangleMesh> triangle_mesh;
	std::shared_ptr<btGImpactMeshShape> tmpshape;
	/* std::shared_ptr<btConvexHullShape> tmpshape1; */

	void initial_ship (void);
public:
	ship (void);
	~ship (void);

};

class stone_a_l : public _object_base {
	std::shared_ptr<btTriangleMesh> triangle_mesh;
	std::shared_ptr<btGImpactMeshShape> tmpshape;
	std::string aaa;
	/* std::shared_ptr<btConvexHullShape> tmpshape1; */

	void initial_stone_a_l (void);
public:
	stone_a_l (void);
	~stone_a_l (void);
	void update (void) override;

};

#endif

