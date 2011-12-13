#pragma once

#include <map>
#include <vector>

#include "common.hpp"

namespace nde
{

class Material;
class UVMap;
class Model;
class Mesh;
class Camera;

class Assets {
public:
	std::vector<Material*> materials;
	std::vector<UVMap*> uvmaps;
	std::vector<Model*> models;
	std::vector<Mesh*> meshes;
	std::vector<Camera*> cameras;
	
	Assets();
	~Assets();
};

} // namespace nde
