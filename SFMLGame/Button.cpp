#include "Button.h"

bool RiA::Button::containsMouseEvent()
{
	if (!isEnabled)
		return false;

	sf::Vector2i mousePosition = sf::Mouse::getPosition(AppData::GetData().getWindow());
	sf::Vector2f mousePositionf;
	mousePositionf.x = (float)mousePosition.x;
	mousePositionf.y = (float)mousePosition.y;

	if (text.getGlobalBounds().contains(mousePositionf))
		return true;

	return false;
}

bool RiA::Button::mouseLeftClickEvent()
{
	if (!isEnabled)
		return false;

	std::vector<sf::Event> events = AppData::GetData().getEvents();

	if (containsMouseEvent())
	{
		for (auto event : events)
		{
			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
				return true;
		}
	}	

	return false;
}

void RiA::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}
