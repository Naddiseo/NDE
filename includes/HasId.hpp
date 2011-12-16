#pragma once
#include <cstddef>

class HasId {
	size_t id;
public:

	void setId(size_t _id) { id = _id; }
	size_t getId() const { return id; }
};
