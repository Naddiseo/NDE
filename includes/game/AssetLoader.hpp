#pragma once

#include <string>

namespace nde {

class AssetLoader {
public:
	AssetLoader();
	virtual ~AssetLoader();

	void loadAsset(std::string path);

};

} // namespace nde
