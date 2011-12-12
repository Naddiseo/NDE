#pragma once

#include <string>

namespace nde {

class AssetLoader {
public:
	AssetLoader();
	virtual ~AssetLoader();

	bool loadAsset(const std::string& path);

};

} // namespace nde
