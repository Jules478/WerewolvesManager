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
			int _blessedPlayer = -1;
			std::map<str, str> _logHold;
			std::ofstream _logOutput;

	public:
			Game(int playerno);
			~Game();

			bool openLog();
			void writeToHold(str name, str line);
			void writeToLog();

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
			void setBlessedPlayer(int index);
			
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
			void displayDeath(int index, bool lynch);
			void saveToINI(std::ofstream& file);
			void loadFromINI(str& file);
			void printCommands();
			void printDebugMenu();

			void closeProgram();
			void debugCommands();
};

str get_input(Game* game, bool allowDebug);
void printTitle();
void clearScreen();
void error_max();

static std::map<str, t_roles> roleLookup = 
{
	{"werewolf", WEREWOLF_ROLE},
	{"wolf cub", WOLFCUB_ROLE},
	{"lone wolf", LONEWOLF_ROLE},
	{"vampire", VAMPIRE_ROLE},
	{"apprentice seer", APPRENTICESEER_ROLE},
	{"aura seer", AURASEER_ROLE},
	{"bodyguard", BODYGUARD_ROLE},
	{"cupid", CUPID_ROLE},
	{"diseased", DISEASED_ROLE},
	{"ghost", GHOST_ROLE},
	{"hunter", HUNTER_ROLE},
	{"idiot", IDIOT_ROLE},
	{"lycan", LYCAN_ROLE},
	{"magician", MAGICIAN_ROLE},
	{"martyr", MARTYR_ROLE},
	{"mason", MASON_ROLE},
	{"mayor", MAYOR_ROLE},
	{"old hag", OLDHAG_ROLE},
	{"old man", OLDMAN_ROLE},
	{"pi", PI_ROLE},
	{"pacifist", PACIFIST_ROLE},
	{"priest", PRIEST_ROLE},
	{"prince", PRINCE_ROLE},
	{"seer", SEER_ROLE},
	{"spellcaster", SPELLCASTER_ROLE},
	{"tough guy", TOUGHGUY_ROLE},
	{"troublemaker", TROUBLEMAKER_ROLE},
	{"villager", VILLAGER_ROLE},
	{"witch", WITCH_ROLE},
	{"sorcerer", SORCERER_ROLE},
	{"minion", MINION_ROLE},
	{"cursed", CURSED_ROLE},
	{"doppelganger", DOPPELGANGER_ROLE},
	{"cult leader", CULTLEADER_ROLE},
	{"hoodlum", HOODLUM_ROLE},
	{"tanner", TANNER_ROLE}
};
