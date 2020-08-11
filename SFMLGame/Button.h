#pragma once
#include <SFML/Graphics.hpp>
#include "AppData.h"

namespace RiA
{
	class Button : public sf::Drawable
	{
	public:
		Button() { isEnabled = true; }

		bool containsMouseEvent();
		bool mouseLeftClickEvent();

		void enable(bool isEnabled) { this->isEnabled = isEnabled; }

	public:
		sf::Text text;

	private:
		void draw(sf::RenderTarget&, sf::RenderStates) const;

	private:
		bool isEnabled;
	};
}