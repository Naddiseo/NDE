#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>
#include "game/Scene.hpp"

namespace nde {

Scene::Scene() : scene(NULL), sceneMin(1e10f, 1e10f, 1e10f), sceneMax(-1e10f,-1e10f,-1e10f), sceneCenter() {
}

Scene::~Scene() {
	if (scene) {
		aiReleaseImport(scene);
	}
}

bool
Scene::loadScene(const std::string& path) {
	Assimp::Importer importer;

	scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast);

	if (!scene) {
		return false;
	}

	getBoundingBox();

	sceneCenter.x = (sceneMin.x + sceneMax.x) / 2.0f;
	sceneCenter.y = (sceneMin.y + sceneMax.y) / 2.0f;
	sceneCenter.z = (sceneMin.z + sceneMax.z) / 2.0f;

	return true;
}

void
Scene::getBoundingBox() {
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	getBoundingBoxForNode(scene->mRootNode, &trafo);
}

void
Scene::getBoundingBoxForNode(const aiNode* nd, aiMatrix4x4* trafo) {
	aiMatrix4x4 prev;

	prev = *trafo;

	aiMultiplyMatrix4(trafo, &nd->mTransformation);

	for (unsigned int n = 0; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		for (unsigned int t = 0; t < mesh->mNumVertices; ++t) {
			aiVector3D tmp = mesh->mVertices[t];

			aiTransformVecByMatrix4(&tmp, trafo);

			sceneMin.x = std::min(sceneMin.x, tmp.x);
			sceneMin.y = std::min(sceneMin.y, tmp.y);
			sceneMin.z = std::min(sceneMin.z, tmp.z);

			sceneMax.x = std::max(sceneMax.x, tmp.x);
			sceneMax.y = std::max(sceneMax.y, tmp.y);
			sceneMax.z = std::max(sceneMax.z, tmp.z);
		}

		for (unsigned int n = 0; n < nd->mNumChildren; ++n) {
			getBoundingBoxForNode(nd->mChildren[n], trafo);
		}
		*trafo = prev;
	}
}

} //namespace nde
