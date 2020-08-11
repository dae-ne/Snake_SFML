#include "ExitMenu.h"

RiA::ExitMenu::ExitMenu()
{
	buttonInit();
	textInit();
}

void RiA::ExitMenu::control()
{
	if (buttons[0].mouseLeftClickEvent())
	{
		AppData::GetData().getWindow().close();
	}

	if (buttons[1].mouseLeftClickEvent())
	{
		setState(RiA::State::MainMenu);
	}
}

void RiA::ExitMenu::update()
{
	for (int i = 0; i < numberOfButtons; i++)
	{
		if (buttons[i].containsMouseEvent())
			buttons[i].text.setFillColor(sf::Color::Cyan);

		else buttons[i].text.setFillColor(sf::Color::White);
	}
}

void RiA::ExitMenu::draw()
{
	AppData::GetData().getWindow().draw(text);

	for (int i = 0; i < numberOfButtons; i++)
		AppData::GetData().getWindow().draw(buttons[i]);
}

void RiA::ExitMenu::buttonInit()
{
	Button button;

	std::string str[] = {
		"Yes",
		"No"
	};

	for (int i = 0; i < numberOfButtons; i++)
	{
		button.text.setString(str[i]);
		button.text.setFont(AppData::GetData().getFont(ButtonFont));
		button.text.setCharacterSize(50);
		button.text.setOrigin(button.text.getGlobalBounds().width / 2, button.text.getGlobalBounds().height / 2);
		button.text.setPosition((float)AppData::GetData().getWindow().getSize().x / 2,
			(float)AppData::GetData().getWindow().getSize().y / 2 + 100 * i);

		buttons.push_back(button);
	}
}

void RiA::ExitMenu::textInit()
{
	text.setFont(AppData::GetData().getFont(MainFont));
	text.setString("Do you really want to exit?");
	text.setCharacterSize(65);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition((float)AppData::GetData().getWindow().getSize().x / 2, (float)AppData::GetData().getWindow().getSize().y / 4);
}