#pragma once

#include "Roles.hpp"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

class Game
{
	private:
			int _playerNo;
			int _wolfNo;
			int _vampNo;
			int _villagerNo;
			std::vector<ACard*> _player;
			bool _wolfWin = false;
			bool _villageWin = false;
			bool _vampWin = false;
			int _nightNo;
			bool _tannerWin = false;
			bool _loneWolfWin = false;
			bool _hoodlumWin = false;
			bool _cultLeaderWin = false;
			int _diedInTheNight[68];
			int _diedIndex = 0;

	public:
			Game(int playerno);
			~Game();

			void addPlayer(str role);
			void removePlayer(str role);
			void nightPhase();
			void firstNight();
			void checkWin();

			void setPlayerNo(int playerno);
			bool isValidPlayerEntry(const str& input);
			bool isValidPlayerNumber(const str& input);
			ACard* getPlayerByIndex(int index);
			int* getNightlyDeaths();
			void setNightlyDeaths(int index);
			void resetNightlyDeaths();
};

str get_input();