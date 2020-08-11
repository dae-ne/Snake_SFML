#pragma once
#include <SFML/Graphics.hpp>
#include "AppData.h"

namespace RiA
{
	enum class State
	{
		MainMenu,
		SettingsMenu,
		ExitMenu,
		Game,
		GameContinue
	};

	class IState
	{
	public:
		IState() { appState = State::ExitMenu; }
		virtual ~IState() = default;

		virtual void control() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

		void setState(const State& state) { appState = state; }
		State getState() { return appState; }

	protected:
		State appState;
	};
}