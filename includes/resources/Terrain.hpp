#pragma once
/*
 * Terrain.hpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

#include "common.hpp"
#include "game/Entity.hpp"

namespace nde {

#pragma pack(push, 1)
struct _col{
	char r;
	char b;
	char g;
};
#pragma pack(pop)

class Terrain : public Entity {
	scalar* heightmap;
	scalar scale;
	_col* colormap;
	size_t height, width;

	btHeightfieldTerrainShape* heightfieldShape;
public:
	Terrain(World* _world);
	virtual ~Terrain();

	virtual void tick();

};

} /* namespace nde */
