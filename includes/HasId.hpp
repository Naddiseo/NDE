#pragma once
#include <cstddef>

class HasId {
	static size_t creationCounter ;
	size_t id;
public:

	HasId() { id = ++creationCounter; }

	size_t getId() const { return id; }
};
