#pragma once

namespace nde {
class Game;
class Camera;
class Input;
class World;
class iGraphicsLibrary;

class EngineModule {
protected:
	Game* game;
	Camera* camera;
	Input* input;
	World* world;
	iGraphicsLibrary* graphics;

public:
	EngineModule();
	virtual ~EngineModule();

	virtual bool init() = 0;

	void setGame(Game* _game) { game = _game; }
	void setCamera(Camera* _c) { camera = _c; }
	void setInput(Input* _i) { input = _i; }
	void setWorld(World* _w) { world = _w; }
	void setGraphics(iGraphicsLibrary* _l) { graphics = _l; }
};

}


