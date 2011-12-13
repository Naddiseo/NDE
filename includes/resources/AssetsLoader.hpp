#pragma once

#include <string>

namespace nde
{

class Assets;

void LoadAssetsFromText(const std::string& file, Assets& assets);

}
