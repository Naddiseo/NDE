#pragma once
#include <functional>
#include <vector>
#include <SDL/SDL.h>

namespace nde {

typedef std::function<void(const SDL_MouseMotionEvent&)> mousemove_callback_t;
typedef std::function<void(const SDL_MouseButtonEvent&)> mouseclick_callback_t;


class MouseMap {
	enum mouse_button {
		NONE,
		LEFT = SDL_BUTTON_LEFT,
		MIDDLE = SDL_BUTTON_MIDDLE,
		RIGHT = SDL_BUTTON_RIGHT,
	} last_clicked;
	size_t last_click;

	std::vector<mousemove_callback_t> move_callbacks;

	mouseclick_callback_t left_mouse_down;
	mouseclick_callback_t middle_mouse_down;
	mouseclick_callback_t right_mouse_down;

	mouseclick_callback_t left_mouse_up;
	mouseclick_callback_t middle_mouse_up;
	mouseclick_callback_t right_mouse_up;

	mouseclick_callback_t left_mouse_click;
	mouseclick_callback_t middle_mouse_click;
	mouseclick_callback_t right_mouse_click;

	mouseclick_callback_t left_mouse_dblclick;
	mouseclick_callback_t middle_mouse_dblclick;
	mouseclick_callback_t right_mouse_dblclick;

public:
	MouseMap();
	virtual ~MouseMap();

	void installOnMove(mousemove_callback_t callback);

	void installOnLeftMouseDown(mouseclick_callback_t callback);
	void installOnMiddleMouseDown(mouseclick_callback_t callback);
	void installOnRightMouseDown(mouseclick_callback_t callback);

	void installOnLeftMouseUp(mouseclick_callback_t callback);
	void installOnMiddleMouseUp(mouseclick_callback_t callback);
	void installOnRightMouseUp(mouseclick_callback_t callback);

	void installOnLeftClick(mouseclick_callback_t callback);
	void installOnMiddleClick(mouseclick_callback_t callback);
	void installOnRightClick(mouseclick_callback_t callback);

	void installOnLeftDblClick(mouseclick_callback_t callback);
	void installOnMiddleDblClick(mouseclick_callback_t callback);
	void installOnRightDblClick(mouseclick_callback_t callback);


	void dispatchMove(const SDL_MouseMotionEvent& event);
	void dispatchClick(const SDL_MouseButtonEvent& event);
};

}


