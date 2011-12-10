#include <map>
#include <string>
#include "Color.hpp"
typedef std::map<std::string, Color> colors_map_t;
static colors_map_t colors_map;

void add_color(std::string name, unsigned char r, unsigned char g, unsigned char b) {
	colors_map[name] = Color(r,g,b);
}
Color& get_color(std::string name) {
	return colors_map[name];
}
