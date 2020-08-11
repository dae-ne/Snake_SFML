#pragma once
#include "IState.h"
#include "Button.h"
#include <Windows.h>
#include <vector>

namespace RiA
{
	class MainMenu : public IState
	{
	public:
		MainMenu() { buttonInit(); }

		void control() override;
		void update() override;
		void draw() override;

	private:
		void buttonInit();

	private:
		std::vector<Button> buttons;
		const int numberOfButtons = 4;
	};
}