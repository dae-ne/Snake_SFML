#pragma once
#include "IState.h"
#include "Button.h"
#include <Windows.h>
#include <vector>

namespace RiA
{
	class SettingsMenu : public IState
	{
	public:
		SettingsMenu() { buttonInit(); }

		void control() override;
		void update() override;
		void draw() override;

	private:
		void buttonInit();

	private:
		std::vector<Button> buttons;
		const int numberOfButtons = 2;
	};
}