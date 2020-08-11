#include "SettingsMenu.h"

void RiA::SettingsMenu::control()
{
	if (buttons[0].mouseLeftClickEvent())
	{
		switch (AppData::GetData().getDifficultyLevel())
		{
		case DifficultyLevel::Easy:
			AppData::GetData().setDifficultyLevel(DifficultyLevel::Normal);
			AppData::GetData().setUpdateTime(DifficultyLevel::Normal);
			break;

		case DifficultyLevel::Normal:
			AppData::GetData().setDifficultyLevel(DifficultyLevel::Hard);
			AppData::GetData().setUpdateTime(DifficultyLevel::Hard);
			break;

		case DifficultyLevel::Hard:
			AppData::GetData().setDifficultyLevel(DifficultyLevel::Easy);
			AppData::GetData().setUpdateTime(DifficultyLevel::Easy);
			break;
		}
	}

	if (buttons[1].mouseLeftClickEvent())
	{
		setState(RiA::State::MainMenu);
	}
}

void RiA::SettingsMenu::update()
{
	for (int i = 0; i < numberOfButtons; i++)
	{
		if (buttons[i].containsMouseEvent())
			buttons[i].text.setFillColor(sf::Color::Cyan);

		else buttons[i].text.setFillColor(sf::Color::White);
	}

	buttons[0].text.setString("Difficutly Level: " + AppData::GetData().getDifficultyLevelAsString());

	buttons[0].text.setOrigin(buttons[0].text.getGlobalBounds().width / 2, buttons[0].text.getGlobalBounds().height / 2);
	buttons[0].text.setPosition((float)AppData::GetData().getWindow().getSize().x / 2,
		(float)AppData::GetData().getWindow().getSize().y / 2);
}

void RiA::SettingsMenu::draw()
{
	for (int i = 0; i < numberOfButtons; i++)
		AppData::GetData().getWindow().draw(buttons[i]);
}

void RiA::SettingsMenu::buttonInit()
{
	Button button;

	std::string str[] = {
		"Difficutly Level: " + AppData::GetData().getDifficultyLevelAsString(),
		"Back"
	};

	for (int i = 0; i < numberOfButtons; i++)
	{
		if (i == numberOfButtons - 1)
			button.text.setFont(AppData::GetData().getFont(ButtonFont));

		else button.text.setFont(AppData::GetData().getFont(MainFont));

		button.text.setString(str[i]);
		button.text.setCharacterSize(50);
		button.text.setOrigin(button.text.getGlobalBounds().width / 2, button.text.getGlobalBounds().height / 2);
		button.text.setPosition((float)AppData::GetData().getWindow().getSize().x / 2,
			(float)AppData::GetData().getWindow().getSize().y / 2 + 100 * i);

		buttons.push_back(button);
	}
}