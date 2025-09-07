#pragma once

#include "Roles.hpp"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <fstream>
#include "../inih/ini.h"
#include "../inih/cpp/INIReader.h"
#include <filesystem>

#define NIGHT true
#define DAY false
#define ALIVE true
#define DEAD false
#define FIRST false
#define SECOND true

class Game
{
	private:
			bool _revealCards = true;
			int _playerNo = 0;
			int _wolfNo = 0;
			int _vampNo = 0;
			int _villagerNo = 0;
			std::vector<ACard*> _player;
			bool _wolfWin = false;
			bool _villageWin = false;
			bool _vampWin = false;
			int _diedInTheNight[68];
			int _diedIndex = 0;
			int	_vampireVictim = -1;
			bool _nighttime = true;
			int	_balance = 0;
			int _nightNo = 1;
			bool _secondWolfKill = false;
			bool _secondLynching = false;
			bool _wolfUpsetTummy = false;
			bool _whichRoles[MAX_ROLES];
			int _howManyRoles[MAX_ROLES];
			int _assignedPlayers[68];
			int _assignedIndex = 0;
			int _drunkRole = -1;
			bool _drunkInGame = false;
			bool _altGhostRule = false;
			bool _indexSet = false;

	public:
			Game(int playerno);
			~Game();

			void addPlayer(str role);
			void removePlayer(str role);
			void nightPhase();
			void firstNight();
			void dayPhase();
			bool checkWin();
			bool tryStart();

			bool isValidPlayerEntry(const str& input);
			bool isValidPlayerNumber(const str& input);
			bool isValidPlayerNumberAlt(const str& input, int index);
			bool isValidAlivePlayer(const str& input);
			bool isValidVoteNumber(const str& input);
			void resetNightlyDeaths();
			
			void killVillager();
			void killWolf();
			void killVampire();

			void setPlayerNo(int playerno);
			void setNightlyDeaths(int index);
			void setVampVictim(int index);
			void setBalance(int value);
			void setGameMode();
			void setDrunkMode();
			void setGhostMode();
			void setTimeOfDay();
			
			ACard* getPlayerByIndex(int index);
			ACard* getSeer(bool which);
			ACard* getPlayerByRole(int role);
			int* getNightlyDeaths();
			bool getTimeOfDay() const;
			int getWereNo() const;
			std::vector<ACard*>& getPlayers();
			int getBalance() const;
			int getPlayerNo() const;
			bool stopGame() const;
			int getCurrentNight() const;
			void wakeAllActiveRoles();
			bool getGameMode() const;
			bool getDrunkMode() const;
			bool getGhostMode() const;
			void wolfCubKilled();
			void printGameStatus();
			void checkSideWins();
			void updateVillageNumbers(int index);
			bool* getRoles();
			bool isAliveOrCopied(const ACard& player);
			void checkDoppelganger(const ACard& player);
			void displayDeath(int index);
			void saveToINI(std::ofstream& file);
			void loadFromINI(str& file);
			void printCommands();

			void closeProgram();
};

str get_input();
void printTitle();
void clearScreen();