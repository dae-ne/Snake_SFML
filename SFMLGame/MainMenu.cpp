#include "MainMenu.h"
#include <fstream>

void RiA::MainMenu::control()
{
	if (buttons[0].mouseLeftClickEvent())
	{
		setState(RiA::State::Game);
	}
	
	if (buttons[1].mouseLeftClickEvent())
	{
		setState(RiA::State::GameContinue);
	}

	if (buttons[2].mouseLeftClickEvent())
	{
		setState(RiA::State::SettingsMenu);
	}

	if (buttons[3].mouseLeftClickEvent())
	{
		setState(RiA::State::ExitMenu);
	}
}

void RiA::MainMenu::update()
{
	for (int i = 0; i < numberOfButtons; i++)
	{
		if (buttons[i].containsMouseEvent())
			buttons[i].text.setFillColor(sf::Color::Cyan);

		else buttons[i].text.setFillColor(sf::Color::White);
	}
}

void RiA::MainMenu::draw()
{
	for (int i = 0; i < numberOfButtons; i++)
		AppData::GetData().getWindow().draw(buttons[i]);
}

void RiA::MainMenu::buttonInit()
{
	Button button;

	std::string str[] = {
		"Start Game",
		"Continue",
		"Settings",
		"Exit"
	};

	for (int i = 0; i < numberOfButtons; i++)
	{
		button.text.setString(str[i]);
		button.text.setFont(AppData::GetData().getFont(ButtonFont));
		button.text.setCharacterSize(50);
		button.text.setOrigin(button.text.getGlobalBounds().width / 2, button.text.getGlobalBounds().height / 2);
		button.text.setPosition((float)AppData::GetData().getWindow().getSize().x / 2,
			(float)AppData::GetData().getWindow().getSize().y / 2 + 70 * i);

		buttons.push_back(button);
	}

	std::ifstream file(SaveFileDirectory);

	if (!file.good())
		buttons[1].enable(false);
}