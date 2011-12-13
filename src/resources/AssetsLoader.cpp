#include "resources/AssetsLoader.hpp"

#include <string>
#include <fstream>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "resources/Assets.hpp"
#include "resources/Material.hpp"
#include "resources/Mesh.hpp"
#include "resources/Model.hpp"
#include "game/Camera.hpp"
#include "math/vector.hpp"
#include "graphics/Face.hpp"

#include "resources/resource.pb.h"

namespace nde
{

pb::Assets*
LoadPBAssetsFromText(const std::string& file)
{
	pb::Assets* assets = new nde::pb::Assets;
	
	std::fstream input(file.c_str(), std::ios::in | std::ios::binary);
	google::protobuf::io::IstreamInputStream input2(&input);
	
	if (!google::protobuf::TextFormat::Parse(&input2, &assets)) {
		delete assets;
		return 0;
	}
	
	return assets;
}

// TODO: Need a map to get Messages by id
void
ConvertPBAssets(pb::Assets* pbassets, Assets* assets)
{
	for (int i = 0; i < pbassets->material_size(); ++i) {
		pb::Material* mat = pbassets->mutable_material(i);
		Material* xmat = new Material(mat->id(), mat->file());
		assets->materials.push_back(xmat);
	}
	
	for (int i = 0; i < pbassets.uvmap_size(); ++i) {
		pb::Mesh* mesh = pbassets.mutable_mesh(i);
		
		Mesh* xmesh = new Mesh();
		xmesh->id = mesh->id();
		
		for (int j = 0; j < mesh->vertex_size(); ++j) {
			pb::Vector3f* v = mesh->vertex(j);
			
			Vector3f xv;
			xv.x = v->x();
			xv.y = v->y();
			xv.z = v->z();
			
			xmesh->vertices.push_back(xv);
		}
		
		for (int j = 0; j < mesh->face_size(); ++j) {
			pb::Face* f = mesh->face(j);
			
			Face xf;
			xf.vertexes.push_back(&xmesh->vertices[f->a()]);
			xf.vertexes.push_back(&xmesh->vertices[f->b()]);
			xf.vertexes.push_back(&xmesh->vertices[f->c()]);
			
			xmesh->faces.push_back(xf);
		}
		
		assets->meshes.push_back(xmesh);
	}
	
	for (int i = 0; i < pbassets->uvmap_size(); ++i) {
		pb::Model* mod = pbassets->mutable_model(i);
		
		
	}
	
	for (int i = 0; i < pbassets->uvmap_size(); ++i) {
		pb::Camera* cam = pbassets->mutable_camera(i);
		
		
	}
	
	for (int i = 0; i < pbassets->uvmap_size(); ++i) {
		pb::UVMap* uvm = pbassets->mutable_uvmap(i);
		// TODO: Merge this into the Faces; texture, uv coords
	}
}

void
LoadAssetsFromText(const std::string& file, Assets* assets)
{
	pb::Assets* pbassets = LoadPBAssetsFromText(file);
	
	if (pbassets == 0) {
		std::cerr << "Failed to parse assets." << std::endl;
		return;
	}
	
	ConvertPBAssets(pbassets, assets);
	
	delete pbassets;
}


}
