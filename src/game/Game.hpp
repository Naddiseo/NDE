#pragma once
#include <string>
namespace nde {

/**
 * Main entry for the game engine.
 */
class Game {

	bool haserror;
	bool shutdown;
	std::string errorstring;
public:
	static Game& GetInstance() {
		static Game Instance;
		return Instance;
	}
	virtual ~Game();

	void setError(const std::string error);
	void stopGame(bool _error = false);

private:
	Game();
	Game(Game const&);
	void operator=(Game const&);
};

}


