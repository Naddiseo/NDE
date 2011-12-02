#pragma once
/*
 * Renderer.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

namespace nde {

class Renderer {
public:
	static Renderer& getInstance() {
			static Renderer instance;
			return instance;
		}
		virtual ~Renderer();
	private:
		Renderer();
		Renderer(Renderer const&);
		void operator=(Renderer const&);
};

} /* namespace nde */
