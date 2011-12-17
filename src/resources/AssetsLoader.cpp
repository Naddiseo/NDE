#include "resources/AssetsLoader.hpp"

#include <string>
#include <fstream>
#include <cstdint>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "resources/Assets.hpp"
#include "resources/Material.hpp"
#include "resources/Mesh.hpp"
#include "game/Camera.hpp"
#include "math/vector.hpp"
#include "graphics/Face.hpp"

#include "proto.hpp"

namespace nde {

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
message_list_t
ConvertPBAssets(pb::Assets* pbassets, Assets& assets)
{
	message_list_t ret;
	for (int i = 0; i < pbassets->material_size(); ++i) {
		pb::Material* mat = pbassets->mutable_material(i);
		Material* m = assets.allocMaterial(mat->file());
		ret.push_back(m);
	}
	
	for (int i = 0; i < pbassets->mesh_size(); ++i) {
		pb::Mesh* mesh = pbassets->mutable_mesh(i);
		
		Mesh* xmesh = assets.allocMesh();
		
		for (int j = 0; j < mesh->vertex_size(); ++j) {
			pb::Vector3f v = mesh->vertex(j);
			
			xmesh->vertices.push_back(V(v));
		}
		
		for (int j = 0; j < mesh->face_size(); ++j) {
			pb::Face f = mesh->face(j);
			
			Face* xf = xmesh->allocFace();
			xf->vertexes.push_back((Vector3f*)xmesh->vertices[f.a()]);
			xf->vertexes.push_back((Vector3f*)xmesh->vertices[f.b()]);
			xf->vertexes.push_back((Vector3f*)xmesh->vertices[f.c()]);
		}
		
		pb::Vector3f pos = mesh->position();
		pb::Vector3f dir = mesh->direction();
		
		Vector3f* tmppos = V(pos);
		Vector3f* tmpdir = V(pos);

		xmesh->setOrigin(*tmppos);
		xmesh->setOrientation(*tmpdir);

		ret.push_back(xmesh);
	}

	for (int i = 0; i < pbassets->color_size(); ++i) {
		pb::Color* c = pbassets->mutable_color(i);
		Color* col;

		if (c->has_a()) {
			col = assets.allocColor(c->name(), c->r(), c->g(), c->b(), c->a());
		}
		else {
			col = assets.allocColor(c->name(), c->r(), c->g(), c->b());
		}

		ret.push_back(col);
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

	return ret;
}

message_list_t
LoadAssetsFromText(const std::string& file, Assets& assets) {
	pb::Assets* pbassets = LoadPBAssetsFromText(file);
	message_list_t ret;
	
	if (pbassets == 0) {
		std::cerr << "Failed to parse assets." << std::endl;
		return ret;
	}
	
	ret = ConvertPBAssets(pbassets, assets);
	
	delete pbassets;
	google::protobuf::ShutdownProtobufLibrary();

	return ret;
}


}
