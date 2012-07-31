#pragma once
#include "game/Camera.hpp"
#include "game/Entity.hpp"

namespace nde {

class Player : public Entity {
	Camera cam;
public:
	Player();
	virtual ~Player();
};

} // namespace nde


