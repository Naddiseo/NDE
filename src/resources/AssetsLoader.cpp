#include "resources/AssetsLoader.hpp"

#include <string>
#include <fstream>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "resources/Assets.hpp"
#include "resources/Material.hpp"
#include "resources/Mesh.hpp"
#include "game/Entity.hpp"
#include "game/Camera.hpp"
#include "math/vector.hpp"
#include "graphics/Face.hpp"

#include "proto.hpp"

namespace nde
{

Vector3f* V(pb::Vector3f& v) {
	return new Vector3f(v.x(), v.y(), v.z());
}

pb::Assets*
LoadPBAssetsFromText(const std::string& file)
{
	pb::Assets* assets = new nde::pb::Assets;
	
	std::fstream input(file.c_str(), std::ios::in | std::ios::binary);
	google::protobuf::io::IstreamInputStream input2(&input);
	
	if (!google::protobuf::TextFormat::Parse(&input2, assets)) {
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
		assets->allocMaterial(mat->id(), mat->file());
	}
	
	for (int i = 0; i < pbassets->uvmap_size(); ++i) {
		pb::Mesh* mesh = pbassets->mutable_mesh(i);
		
		Mesh* xmesh = assets->allocMesh();
		
		for (int j = 0; j < mesh->vertex_size(); ++j) {
			pb::Vector3f v = mesh->vertex(j);
			
			xmesh->vertices.push_back(V(v));
		}
		
		for (int j = 0; j < mesh->face_size(); ++j) {
			pb::Face f = mesh->face(j);
			
			Face* xf = new Face();
			xf->vertexes.push_back(xmesh->vertices[f.a()]);
			xf->vertexes.push_back(xmesh->vertices[f.b()]);
			xf->vertexes.push_back(xmesh->vertices[f.c()]);
			
			xmesh->faces.push_back(xf);
		}
		
		assets->meshes.push_back(xmesh);
	}

	for (int i = 0; i < pbassets->entity_size(); ++i) {
		pb::Entity* mod = pbassets->mutable_entity(i);
		
		Entity* e = new Entity();

		pb::Vector3f pos = mod->position();
		pb::Vector3f dir = mod->direction();
		
		Vector3f* tmppos = V(pos);
		Vector3f* tmpdir = V(pos);

		e->setOrigin(*tmppos);
		e->setOrientation(*tmpdir);

		delete tmppos;
		delete tmpdir;

		assets->entities.push_back(e);
	}


#if 0 // TODO implement these
	for (int i = 0; i < pbassets->camera_size(); ++i) {
		pb::Camera* cam = pbassets->mutable_camera(i);
		
		
	}
	
	for (int i = 0; i < pbassets->uvmap_size(); ++i) {
		pb::UVMap* uvm = pbassets->mutable_uvmap(i);
		// TODO: Merge this into the Faces; texture, uv coords
	}
#endif

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
