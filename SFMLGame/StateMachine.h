#pragma once
#include "AppData.h"
#include "IState.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "ExitMenu.h"
#include "Game.h"

namespace RiA
{
	class StateMachine
	{
	public:
		StateMachine(State state);
		~StateMachine();

		IState* switchStates();

	private:
		void deleteState();

	private:
		IState* pState;
		State state;
	};
}