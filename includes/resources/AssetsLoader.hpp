#pragma once

#include <string>
#include <vector>
#include "resources/Material.hpp"
#include "resources/Mesh.hpp"
#include "resources/Color.hpp"

namespace nde {

class Assets;

enum class MessageType : char {
	Material,
	Mesh,
	Color,
};

struct Message {
	MessageType type;
	size_t id;
	std::string name;

	Message(Material* m) : type(MessageType::Material), id(m->getId()), name()        {}

	Message(Mesh* m)     : type(MessageType::Mesh),     id(m->getId()), name()        {}

	Message(Color* c)    : type(MessageType::Color),    id(0),          name(c->name) {}
};

typedef std::vector<Message> message_list_t;

message_list_t LoadAssetsFromText(const std::string& file, Assets& assets);

}
