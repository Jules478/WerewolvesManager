#pragma once

#include "Roles.hpp"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

#define NIGHT true
#define DAY false
#define ALIVE true
#define DEAD false

class Game
{
	private:
			int _playerNo = 0;
			int _wolfNo = 0;
			int _vampNo = 0;
			int _villagerNo = 0;
			std::vector<ACard*> _player;
			bool _wolfWin = false;
			bool _villageWin = false;
			bool _vampWin = false;
			bool _tannerWin = false;
			bool _loneWolfWin = false;
			bool _hoodlumWin = false;
			bool _cultWin = false;
			int _diedInTheNight[68];
			int _diedIndex = 0;
			int	_vampireVictim;
			bool _nighttime = true;
			int	_balance = 0;
			int _nightNo = 1;
			bool _whichRoles[MAX_ROLES];
			int _howManyRoles[MAX_ROLES];

	public:
			Game(int playerno);
			~Game();

			void addPlayer(str role);
			void removePlayer(str role);
			void nightPhase();
			void firstNight();
			void checkWin();
			bool tryStart();

			bool isValidPlayerEntry(const str& input);
			bool isValidPlayerNumber(const str& input);
			bool isValidAlivePlayer(const str& input);
			void resetNightlyDeaths();
			
			void setPlayerNo(int playerno);
			void setNightlyDeaths(int index);
			void setVampVictim(int index);
			void setWinStates(int wolf, int village, int vamp, int tanner, int lone, int hood, int cult);
			void setBalance(int value);
			
			ACard* getPlayerByIndex(int index);
			int* getNightlyDeaths();
			bool getTimeOfDay() const;
			int getWereNo() const;
			std::vector<ACard*>& getPlayers();
			int getBalance() const;
			int getPlayerNo() const;
			bool stopGame() const;
			int getCurrentNight() const;
};

str get_input();