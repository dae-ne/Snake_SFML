#pragma once
#include "IState.h"
#include "Button.h"
#include <Windows.h>
#include <vector>

namespace RiA
{
	class ExitMenu : public IState
	{
	public:
		ExitMenu();

		void control() override;
		void update() override;
		void draw() override;

	private:
		void buttonInit();
		void textInit();

	private:
		std::vector<Button> buttons;
		const int numberOfButtons = 2;
		sf::Text text;
	};
}