#include "../inc/Game.hpp"

/**
 * Prints the error for role limit in menu
 */
void error_max()
{
	clearScreen();
	printTitle();
	std::cout << "Maximum number already in game" << std::endl;
}

/**
 * Wrapper for getline. Will handle any errors with exit
 */
str get_input(Game* game, bool allowDebug)
{
	str input;

	if (!std::getline(std::cin, input))
		exit(0);
	if (game && allowDebug && input == "~")
		game->debugCommands();
	return input;
}

#define DEBUGCMDS "Commands\n\nkill [Player Index] | revive [Player Index] | exit\n\nEnter Command: "

/**
 * Debug tool for game management
 * Can kill or revive players
 * Can only be used on a "Press Enter" screen
 */
void Game::debugCommands()
{
	clearScreen();
	printGameStatus();
	std::cout << DEBUGCMDS << std::endl;
	str input;
	ACard* player;
	while (1)
	{
		input = get_input(this, false);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input.substr(0, 5) == "kill ")
		{
			str index = input.substr(5);
			if (isValidPlayerNumber(index))
			{
				int num = std::stoi(index);
				player = getPlayerByIndex(num);
				if (player->getLife() == DEAD)
				{
					clearScreen();
					printGameStatus();
					std::cout << "Player " << index << " is already dead\n";
					std::cout << DEBUGCMDS << std::endl;
				}
				else
				{
					player->setLife(DEAD);
					updateVillageNumbers(num);
					clearScreen();
					printGameStatus();
					std::cout << "Player " << index << " killed\n";
					std::cout << DEBUGCMDS << std::endl;
				}
				
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Invalid Player Index\n";
				std::cout << DEBUGCMDS << std::endl;
			}
		}
		else if (input.substr(0, 7) == "revive ")
		{
			str index = input.substr(7);
			if (isValidPlayerNumber(index))
			{
				player = getPlayerByIndex(std::stoi(index));
				if (player->getLife() == ALIVE)
				{
					clearScreen();
					printGameStatus();
					std::cout << "Player " << index << " is already alive\n";
					std::cout << DEBUGCMDS << std::endl;
				}
				else
				{
					player->setLife(ALIVE);
					if (player->getSide() == WEREWOLF && player->getRole() != SORCERER_ROLE && player->getRole() != MINION_ROLE)
						_wolfNo++;
					else if (player->getSide() == VAMPIRE)
						_vampNo++;
					else
						_villagerNo++;
					clearScreen();
					printGameStatus();
					std::cout << "Player " << index << " revived\n";
					std::cout << DEBUGCMDS << std::endl;
				}
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Invalid Player Index\n";
				std::cout << DEBUGCMDS << std::endl;
			}
		}
		else if (input.substr(0,4) == "exit")
		{
			break;
		}
		else
		{
			clearScreen();
			printGameStatus();
			std::cout << "Invalid Command\n";
			std::cout << DEBUGCMDS << std::endl;
		}
	}

}

/**
 * Checks if the given string represents a player index within the size of the game that is unique
 * 
 * @param input String received from getline
 * 
 * @returns False if non unique. True if unique
 */
bool Game::isValidPlayerEntry(const str& input)
{
	if (input.empty())
		return false;
	for (char c : input)
	{
		if (!std::isdigit(c))
			return false;
	}
	try
	{
		int number = std::stoi(input);
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i] && number == _player[i]->getIndex())
				return false;
		}
		return (number >= 1 && number <= _playerNo);
	}
	catch (const std::exception&)
	{
		return false;
	}
}

/**
 * Delete player array and then exit
 */
void Game::closeProgram()
{
	for (size_t i = 0; i < _player.size(); i++)
		delete _player[i];
	exit(0);
}

/**
 * Returns player with specified index
 * 
 * @param index Player index to fetch
 */
ACard* Game::getPlayerByIndex(int index)
{
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getIndex() == index)
			return _player[i];
	}
	return nullptr;
}

/**
 * Checks if player index can exist in the current game size
 * 
 * @param input String from getline of index to check
 */
bool Game::isValidPlayerNumber(const str& input)
{
	if (input.empty())
		return false;
	for (char c : input)
	{
		if (!std::isdigit(c))
			return false;
	}
	try
	{
		int number = std::stoi(input);
		return (number >= 1 && number <= _playerNo);
	}
	catch (const std::exception&)
	{
		return false;
	}
}

/**
 * Checks if player index can exist in the current game size excluding specified index
 * 
 * @param input String from getline of index to check
 * @param index Index to be considered invalid
 */
bool Game::isValidPlayerNumberAlt(const str& input, int index)
{
	if (input.empty())
		return false;
	for (char c : input)
	{
		if (!std::isdigit(c))
			return false;
	}
	try
	{
		size_t number = std::stoi(input);
		if (static_cast<int>(number) == index)
			return false;
		return (number >= 1 && number <= _player.size());
	}
	catch (const std::exception&)
	{
		return false;
	}
}

/**
 * Checks if the number of votes entered for a lynching exceeds current living player count
 * 
 * @param input String from getline to be checked
 */
bool Game::isValidVoteNumber(const str& input)
{
	if (input.empty())
		return false;
	for (char c : input)
	{
		if (!std::isdigit(c))
			return false;
	}
	try
	{
		int number = std::stoi(input);
		return (number >= 0 && number <= _playerNo);
	}
	catch (const std::exception&)
	{
		return false;
	}
}

/**
 * Checks if given player index is alive and not poxxed by the Old Hag
 * 
 * @param input String from getline to be checked
 */
bool Game::isValidAlivePlayer(const str& input)
{
	if (input.empty())
		return false;
	for (char c : input)
	{
		if (!std::isdigit(c))
			return false;
	}
	try
	{
		int number = std::stoi(input);
		if (number > _playerNo || number < 1)
			return false;
		return (getPlayerByIndex(number)->getLife() && getPlayerByIndex(number)->getInVillage());
	}
	catch (const std::exception&)
	{
		return false;
	}
}

/**
 * Add player to the player vector
 * Will validate that the role exists
 * 
 * @param role String containing the case insensitive role name to add
 */
void Game::addPlayer(str role)
{
	if (static_cast<int>(_player.size()) == _playerNo)
	{
		clearScreen();
		printTitle();
		std::cout << "Game is full. Resize to add more players" << std::endl;
		return ;
	}
	str lowerRole = role;
	std::transform(lowerRole.begin(), lowerRole.end(), lowerRole.begin(), ::tolower);
	auto it = roleLookup.find(lowerRole);	
	if (it != roleLookup.end())
	{
		t_roles roleType = it->second;
		ACard* newPlayer = nullptr;
		switch (roleType)
		{
			case WEREWOLF_ROLE:
				if (_howManyRoles[WEREWOLF_ROLE] == 12)	
					return(error_max());
				_whichRoles[WEREWOLF_ROLE] = true;
				_howManyRoles[WEREWOLF_ROLE]++;
				newPlayer = new Werewolf(this);
				_balance -= 6;
				break;
			case WOLFCUB_ROLE:
				if (_howManyRoles[WOLFCUB_ROLE] == 1)	
					return(error_max());
				_whichRoles[WOLFCUB_ROLE] = true;
				_howManyRoles[WOLFCUB_ROLE]++;
				newPlayer = new WolfCub(this);
				_balance -= 8;
				break;
			case LONEWOLF_ROLE:
				if (_howManyRoles[LONEWOLF_ROLE] == 1)	
					return(error_max());
				_whichRoles[LONEWOLF_ROLE] = true;
				_howManyRoles[LONEWOLF_ROLE]++;
				newPlayer = new LoneWolf(this);
				_balance -= 5;
				break;
			case VAMPIRE_ROLE:
				if (_howManyRoles[VAMPIRE_ROLE] == 6)	
					return(error_max());
				_whichRoles[VAMPIRE_ROLE] = true;
				_howManyRoles[VAMPIRE_ROLE]++;
				newPlayer = new Vampire(this);
				_balance -= 8;
				break;
			case APPRENTICESEER_ROLE:
				if (_howManyRoles[APPRENTICESEER_ROLE] == 1)	
					return(error_max());
				_whichRoles[APPRENTICESEER_ROLE] = true;
				_howManyRoles[APPRENTICESEER_ROLE]++;
				newPlayer = new ApprenticeSeer(this);
				_balance += 4;
				break;
			case AURASEER_ROLE:
				if (_howManyRoles[AURASEER_ROLE] == 1)	
					return(error_max());
				_whichRoles[AURASEER_ROLE] = true;
				_howManyRoles[AURASEER_ROLE]++;
				newPlayer = new AuraSeer(this);
				_balance += 3;
				break;
			case BODYGUARD_ROLE:
				if (_howManyRoles[BODYGUARD_ROLE] == 1)	
					return(error_max());
				_whichRoles[BODYGUARD_ROLE] = true;
				_howManyRoles[BODYGUARD_ROLE]++;
				newPlayer = new Bodyguard(this);
				_balance += 3;
				break;
			case CUPID_ROLE:
				if (_howManyRoles[CUPID_ROLE] == 1)	
					return(error_max());
				_whichRoles[CUPID_ROLE] = true;
				_howManyRoles[CUPID_ROLE]++;
				newPlayer = new Cupid(this);
				_balance -= 3;
				break;
			case DISEASED_ROLE:
				if (_howManyRoles[DISEASED_ROLE] == 1)	
					return(error_max());
				_whichRoles[DISEASED_ROLE] = true;
				_howManyRoles[DISEASED_ROLE]++;
				newPlayer = new Diseased(this);
				_balance += 3;
				break;
			case GHOST_ROLE:
				if (_howManyRoles[GHOST_ROLE] == 1)	
					return(error_max());
				_whichRoles[GHOST_ROLE] = true;
				_howManyRoles[GHOST_ROLE]++;
				newPlayer = new Ghost(this);
				_balance += 2;
				break;
			case HUNTER_ROLE:
				if (_howManyRoles[HUNTER_ROLE] == 1)	
					return(error_max());
				_whichRoles[HUNTER_ROLE] = true;
				_howManyRoles[HUNTER_ROLE]++;
				newPlayer = new Hunter(this);
				_balance += 3;
				break;
			case IDIOT_ROLE:
				if (_howManyRoles[IDIOT_ROLE] == 1)	
					return(error_max());
				_whichRoles[IDIOT_ROLE] = true;
				_howManyRoles[IDIOT_ROLE]++;
				newPlayer = new Idiot(this);
				_balance += 2;
				break;
			case LYCAN_ROLE:
				if (_howManyRoles[LYCAN_ROLE] == 1)	
					return(error_max());
				_whichRoles[LYCAN_ROLE] = true;
				_howManyRoles[LYCAN_ROLE]++;
				newPlayer = new Lycan(this);
				_balance -= 1;
				break;
			case MAGICIAN_ROLE:
				if (_howManyRoles[MAGICIAN_ROLE] == 1)	
					return(error_max());
				_whichRoles[MAGICIAN_ROLE] = true;
				_howManyRoles[MAGICIAN_ROLE]++;
				newPlayer = new Magician(this);
				_balance += 4;
				break;
			case MARTYR_ROLE:
				if (_howManyRoles[MARTYR_ROLE] == 1)	
					return(error_max());
				_whichRoles[MARTYR_ROLE] = true;
				_howManyRoles[MARTYR_ROLE]++;
				newPlayer = new Martyr(this);
				_balance += 3;
				break;
			case MASON_ROLE:
				if (_howManyRoles[MASON_ROLE] == 3)	
					return(error_max());
				_whichRoles[MASON_ROLE] = true;
				_howManyRoles[MASON_ROLE]++;
				newPlayer = new Mason(this);
				_balance += 2;
				break;
			case MAYOR_ROLE:
				if (_howManyRoles[MAYOR_ROLE] == 1)	
					return(error_max());
				_whichRoles[MAYOR_ROLE] = true;
				_howManyRoles[MAYOR_ROLE]++;
				newPlayer = new Mayor(this);
				_balance += 2;
				break;
			case OLDHAG_ROLE:
				if (_howManyRoles[OLDHAG_ROLE] == 1)	
					return(error_max());
				_whichRoles[OLDHAG_ROLE] = true;
				_howManyRoles[OLDHAG_ROLE]++;
				newPlayer = new OldHag(this);
				_balance += 1;
				break;
			case OLDMAN_ROLE:
				if (_howManyRoles[OLDMAN_ROLE] == 1)	
					return(error_max());
				_whichRoles[OLDMAN_ROLE] = true;
				_howManyRoles[OLDMAN_ROLE]++;
				newPlayer = new OldMan(this);
				break;
			case PI_ROLE:
				if (_howManyRoles[PI_ROLE] == 1)	
					return(error_max());
				_whichRoles[PI_ROLE] = true;
				_howManyRoles[PI_ROLE]++;
				newPlayer = new PI(this);
				_balance += 3;
				break;
			case PACIFIST_ROLE:
				if (_howManyRoles[PACIFIST_ROLE] == 1)	
					return(error_max());
				_whichRoles[PACIFIST_ROLE] = true;
				_howManyRoles[PACIFIST_ROLE]++;
				newPlayer = new Pacifist(this);
				_balance -= 2;
				break;
			case PRIEST_ROLE:
				if (_howManyRoles[PRIEST_ROLE] == 1)	
					return(error_max());
				_whichRoles[PRIEST_ROLE] = true;
				_howManyRoles[PRIEST_ROLE]++;
				newPlayer = new Priest(this);
				_balance += 3;
				break;
			case PRINCE_ROLE:
				if (_howManyRoles[PRINCE_ROLE] == 1)	
					return(error_max());
				_whichRoles[PRINCE_ROLE] = true;
				_howManyRoles[PRINCE_ROLE]++;
				newPlayer = new Prince(this);
				_balance += 3;
				break;
			case SEER_ROLE:
				if (_howManyRoles[SEER_ROLE] == 2)	
					return(error_max());
				_whichRoles[SEER_ROLE] = true;
				_howManyRoles[SEER_ROLE]++;
				newPlayer = new Seer(this);
				if (_howManyRoles[SEER_ROLE] == 2)
					newPlayer->setAbilityUsed();
				_balance += 7;
				break;
			case SPELLCASTER_ROLE:
				if (_howManyRoles[SPELLCASTER_ROLE] == 1)	
					return(error_max());
				_whichRoles[SPELLCASTER_ROLE] = true;
				_howManyRoles[SPELLCASTER_ROLE]++;
				newPlayer = new Spellcaster(this);
				_balance += 1;
				break;
			case TOUGHGUY_ROLE:
				if (_howManyRoles[TOUGHGUY_ROLE] == 1)	
					return(error_max());
				_whichRoles[TOUGHGUY_ROLE] = true;
				_howManyRoles[TOUGHGUY_ROLE]++;
				newPlayer = new ToughGuy(this);
				_balance += 3;
				break;
			case TROUBLEMAKER_ROLE:
				if (_howManyRoles[TROUBLEMAKER_ROLE] == 1)	
					return(error_max());
				_whichRoles[TROUBLEMAKER_ROLE] = true;
				_howManyRoles[TROUBLEMAKER_ROLE]++;
				newPlayer = new TroubleMaker(this);
				_balance += 2;
				break;
			case VILLAGER_ROLE:
				if (_howManyRoles[VILLAGER_ROLE] == 20)	
					return(error_max());
				_whichRoles[VILLAGER_ROLE] = true;
				_howManyRoles[VILLAGER_ROLE]++;
				newPlayer = new Villager(this);
				_balance += 1;
				break;
			case WITCH_ROLE:
				if (_howManyRoles[WITCH_ROLE] == 1)	
					return(error_max());
				_whichRoles[WITCH_ROLE] = true;
				_howManyRoles[WITCH_ROLE]++;
				newPlayer = new Witch(this);
				_balance += 4;
				break;
			case SORCERER_ROLE:
				if (_howManyRoles[SORCERER_ROLE] == 1)	
					return(error_max());
				_whichRoles[SORCERER_ROLE] = true;
				_howManyRoles[SORCERER_ROLE]++;
				newPlayer = new Sorcerer(this);
				_balance -= 3;
				break;
			case MINION_ROLE:
				if (_howManyRoles[MINION_ROLE] == 1)	
					return(error_max());
				_whichRoles[MINION_ROLE] = true;
				_howManyRoles[MINION_ROLE]++;
				newPlayer = new Minion(this);
				_balance -= 6;
				break;
			case CURSED_ROLE:
				if (_howManyRoles[CURSED_ROLE] == 1)	
					return(error_max());
				_whichRoles[CURSED_ROLE] = true;
				_howManyRoles[CURSED_ROLE]++;
				newPlayer = new Cursed(this);
				_balance -= 3;
				break;
			case DOPPELGANGER_ROLE:
				if (_howManyRoles[DOPPELGANGER_ROLE] == 1)	
					return(error_max());
				_whichRoles[DOPPELGANGER_ROLE] = true;
				_howManyRoles[DOPPELGANGER_ROLE]++;
				newPlayer = new Doppelganger(this);
				_balance -= 2;
				break;
			case CULTLEADER_ROLE:
				if (_howManyRoles[CULTLEADER_ROLE] == 1)	
					return(error_max());
				_whichRoles[CULTLEADER_ROLE] = true;
				_howManyRoles[CULTLEADER_ROLE]++;
				newPlayer = new CultLeader(this);
				_balance += 1;
				break;
			case HOODLUM_ROLE:
				if (_howManyRoles[HOODLUM_ROLE] == 1)	
					return(error_max());
				_whichRoles[HOODLUM_ROLE] = true;
				_howManyRoles[HOODLUM_ROLE]++;
				newPlayer = new Hoodlum(this);
				break;
			case TANNER_ROLE:
				if (_howManyRoles[TANNER_ROLE] == 1)	
					return(error_max());
				_whichRoles[TANNER_ROLE] = true;
				_howManyRoles[TANNER_ROLE]++;
				newPlayer = new Tanner(this);
				_balance += 1;
				break;
			default:
				break;
		}		
		if (newPlayer)
		{
			_player.push_back(newPlayer);
			clearScreen();
			printTitle();
		}
	}
	else
	{
		clearScreen();
		printTitle();
		std::cout << "Error: Invalid role '" << lowerRole << "'. Please use a valid role name." << std::endl;
	}
}

/**
 * Removes role from the game if present, otherwise prints error
 * 
 * @param role String containing role to be removed
 */
void Game::removePlayer(str role)
{
	str lowerRole = role;
	std::transform(lowerRole.begin(), lowerRole.end(), lowerRole.begin(), ::tolower);
	auto it = roleLookup.find(lowerRole);	
	if (it != roleLookup.end())
	{
		t_roles roleType = it->second;
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i] && _player[i]->getRole() == roleType)
			{
				int role = _player[i]->getRole();
				_howManyRoles[role]--;
				if (_howManyRoles[role] == 0)
					_whichRoles[role] = false;
				_balance -= _player[i]->getValue();
				delete _player[i];
				_player.erase(_player.begin() + i);
				clearScreen();
				printTitle();
				std::cout << lowerRole << " removed" << std::endl;
				return ;
			}
		}
	}
	clearScreen();
	printTitle();
	std::cout << "Role " << lowerRole << " not in game" << std::endl;
}

/**
 * Checks win conditions that will end the game
 * 
 * @returns True when conditions met
 */
bool Game::checkWin()
{
	if (_villagerNo <= _wolfNo && _vampNo == 0)
	{
		_wolfWin = true;
		return true;
	}
	else if (_wolfNo == 0 && _vampNo == 0)
	{
		_villageWin = true;
		return true;
	}
	else if (_vampNo >= _villagerNo && _wolfNo == 0)
	{
		_vampWin = true;
		return true;
	}
	else if (_villagerNo == 0 && _wolfNo != 0 && _vampNo != 0)
	{
		_vampWin = false;
		_wolfWin = false;
		return true;
	}
	return false;
}

/**
 * Reserve size in the player vector for specified number of players
 * If size <= current player number then error will be displayed
 * 
 * @param playerno Size to adjust game to
 */
void Game::setPlayerNo(int playerno)
{
	if (_playerNo == playerno)
	{
		clearScreen();
		printTitle();
		std::cout << "Game already has " << playerno << " players" << std::endl;
		return ;
	}
	if (playerno < static_cast<int>(_player.size()))
	{
		clearScreen();
		printTitle();
		std::cout << "Cannot make game smaller than current number of players (" << _player.size() << ")" << std::endl;
		return ;
	}
	_player.reserve(playerno);
	_playerNo = playerno;
	clearScreen();
	printTitle();
}

/**
 * Fetches array containing player deaths
 */
int* Game::getNightlyDeaths()
{
	return _diedInTheNight;
}

/**
 * Add player to death array
 * If player is already in the death array nothing happens
 * 
 * @param index Index to be added to the array
 */
void Game::setNightlyDeaths(int index)
{
	for (int i = 0; i < _diedIndex; i++)
	{
		if (_diedInTheNight[i] == index)
			return ;
	}
	_diedInTheNight[_diedIndex] = index;
	_diedIndex++;
}

/**
 * Reset the values of death array
 * Handles the death of any player contained within
 */
void Game::resetNightlyDeaths()
{
	_nighttime = true;
	for (int i = 0; i < 68; i++)
	{
		if (_diedInTheNight[i] == -1)
			continue;
		ACard* dead = getPlayerByIndex(_diedInTheNight[i]);
		if (dead->getSide() == WEREWOLF && dead->getRole() != MINION_ROLE && dead->getRole() != SORCERER_ROLE)
		{
			if (dead->getRole() == WOLFCUB_ROLE)
				wolfCubKilled();
			killWolf();
			dead->setLife(DEAD);
		}
		else if (dead->getSide() == VAMPIRE)
		{
			killVampire();
			dead->setLife(DEAD);
		}
		else if (dead->getRole() == CURSED_ROLE)
		{
			killVillager();
			_wolfNo++;
			dead->setSide(WEREWOLF);
		}
		else
		{
			killVillager();
			dead->setLife(DEAD);
			if (dead->getRole() == DISEASED_ROLE)
				_wolfUpsetTummy = true;
			else if (dead->getRole() == HUNTER_ROLE)
			{
				displayDeath(dead->getVictim());
			}
		}
		if (_whichRoles[CUPID_ROLE])
		{
			ACard* cupid = getPlayerByRole(CUPID_ROLE);
			ACard* player1 = getPlayerByIndex(cupid->getPlayer1());
			ACard* player2 = getPlayerByIndex(cupid->getPlayer2());
			if (cupid->getPlayer1() == _diedInTheNight[i] && player2->getLife() == ALIVE)
			{
				setNightlyDeaths(cupid->getPlayer2());
				std::cout << cupid->getPlayer2() << " ";
			}
			else if (cupid->getPlayer2() == _diedInTheNight[i] && player1->getLife() == ALIVE)
			{
				setNightlyDeaths(cupid->getPlayer1());
				std::cout << cupid->getPlayer1() << " ";
			}
		}
		checkDoppelganger(*dead);
		_diedInTheNight[i] = -1;
	}
	_diedIndex = 0;
	_nighttime = false;
}

/**
 * Sets vampire's target
 */
void Game::setVampVictim(int index)
{
	_vampireVictim = index;
}

/**
 * Returns boolean representing current time
 * DAY and NIGHT macros exist
 */
bool Game::getTimeOfDay() const
{
	return _nighttime;
}

/**
 * Fetch number of alive werewolves
 * Only true wolves count to this total
 */
int Game::getWereNo() const
{
	return _wolfNo;
}

/**
 * Fetches reference to player array
 */
std::vector<ACard*>& Game::getPlayers()
{
	return _player;
}

/**
 * Sets balance value on menu
 */
void Game::setBalance(int value)
{
	_balance = value;
}

/**
 * Fetches current balance
 * Adjusts value based on active rules
 */
int Game::getBalance() const
{
	return _balance + (_drunkInGame * -3) + (_altGhostRule * 2);
}

/**
 * Returns current player total
 */
int Game::getPlayerNo() const
{
	return _playerNo;
}

/**
 * Checks if all requirements are met for game to start
 * Requirements are 1 Werewolf/Vampire & 1 Seer
 * If game meets conditions but is not full it will ask to autopopulate game with Villagers
 */
bool Game::tryStart()
{
	for (int i = 0; i < static_cast<int>(_player.size()); i++)
	{
		if (_player[i]->getSide() == VILLAGER ||  _player[i]->getRole() == MINION_ROLE || _player[i]->getRole() == SORCERER_ROLE)
			_villagerNo++;
		else if (_player[i]->getSide() == WEREWOLF && _player[i]->getRole() != MINION_ROLE && _player[i]->getRole() != SORCERER_ROLE)
			_wolfNo++;
		else
			_vampNo++;
	}
	if (_wolfNo == 0 && _vampNo == 0)
	{
		clearScreen();
		printTitle();
		std::cout << "At least 1 Werewolf or Vampire required" << std::endl;
		_wolfNo = 0;
		_villagerNo = 0;
		_vampNo = 0;
		return false;
	}
	else if (_whichRoles[SEER_ROLE] == false)
	{
		clearScreen();
		printTitle();
		std::cout << "At least 1 Seer required" << std::endl;
		_wolfNo = 0;
		_villagerNo = 0;
		_vampNo = 0;
		return false;
	}
	else if (static_cast<int>(_player.size()) != _playerNo)
	{
		clearScreen();
		printTitle();
		std::cout << _playerNo - static_cast<int>(_player.size()) << " player(s) missing roles" << std::endl;
		std::cout << "Do you wish to autofill the game with Villagers?: (y/n): ";
		str input = get_input(this, false);
		while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
		{
			std::cout << "ERROR: Enter choice: ";
			input = get_input(this, false);
		}
		if (input == "y" || input == "Y")
		{
			for (int i = _villagerNo + _wolfNo + _vampNo; i < _playerNo; i++)
			{
				addPlayer("villager");
				_villagerNo++;
			}
			return true;
		}
		_wolfNo = 0;
		_villagerNo = 0;
		_vampNo = 0;
		return false;
	}
	return true;
}

bool Game::stopGame() const
{
	if (_villageWin == true || _wolfWin == true || _vampWin == true)
		return true;
	return false;
}


int Game::getCurrentNight() const
{
	return _nightNo;
}

void Game::killVillager()
{
	_villagerNo--;
}

void Game::killWolf()
{
	_wolfNo--;
}

void Game::killVampire()
{
	_vampNo--;
}

/**
 * Fetches the Seer
 * 
 * @param which Boolean to control whether first or second Seer is returned
 * FIRST and SECOND macros exist to differentiate
 */
ACard*	Game::getSeer(bool which)
{
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getRole() == SEER_ROLE && _player[i]->getAbilityUsed(true) == which)
			return _player[i];
	}
	return nullptr;
}

/**
 * Fetch player with specified role
 * If the doppelganger has copied the player to be retrieved they will be returned instead
 */
ACard*	Game::getPlayerByRole(int role)
{
	if (role == DOPPELGANGER_ROLE)
	{
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i] && _player[i]->getRole() == role)
				return _player[i];
		}
	}
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getRole() == role)
		{
			if (_whichRoles[DOPPELGANGER_ROLE])
			{
				ACard* doppel = getPlayerByRole(DOPPELGANGER_ROLE);
				if (_player[i]->getLife() == DEAD && doppel->getAbilityUsed(true) && doppel->getCopiedPlayer() == _player[i]->getIndex())
					return doppel;
				else
					return _player[i];
			}
			else
				return _player[i];
		}
	}
	return nullptr;
}

bool Game::getGameMode() const
{
	return _revealCards;
}

bool Game::getDrunkMode() const
{
	return _drunkInGame;
}

bool Game::getGhostMode() const
{
	return _altGhostRule;
}

void Game::setGameMode()
{
	_revealCards = !_revealCards;
}

void Game::setDrunkMode()
{
	_drunkInGame = !_drunkInGame;
}

void Game::setGhostMode()
{
	_altGhostRule = !_altGhostRule;
}

void Game::setTimeOfDay()
{
	_nighttime = !_nighttime;
}

void Game::wolfCubKilled()
{
	_secondWolfKill = true;
}

bool* Game::getRoles()
{
	return _whichRoles;
}

bool Game::isAliveOrCopied(const ACard& player)
{
	if (player.getLife() == ALIVE)
		return true;
	ACard* dopp = getPlayerByRole(DOPPELGANGER_ROLE);
	if (_whichRoles[DOPPELGANGER_ROLE] && dopp->getLife() == ALIVE && dopp->getAbilityUsed(false) == true && dopp->getCopiedRole() == player.getIndex())
		return true;
	return false;
}

void Game::checkDoppelganger(const ACard& player)
{
	if (!_whichRoles[DOPPELGANGER_ROLE])
		return ;
	ACard* doppel = getPlayerByRole(DOPPELGANGER_ROLE);
	if (player.getIndex() == doppel->getCopiedPlayer())
		doppel->setAbilityUsed();
}

void Game::displayDeath(int index)
{
	ACard *dead = getPlayerByIndex(index);
	std::cout << dead->getName() << " (" << dead->getIndex() << ") | Side: ";
	switch (dead->getSide())
	{
		case VILLAGER:
			if (dead->getRole() == LYCAN_ROLE)
				std::cout << YELLOW "Werewolf" RESET << std::endl;
			else
				std::cout << BLUE "Villager" RESET << std::endl;
			return;
		case WEREWOLF:
			if (dead->getRole() == MINION_ROLE || dead->getRole() == SORCERER_ROLE)
				std::cout << BLUE "Villager" RESET << std::endl;
			else
				std::cout << YELLOW "Werewolf" RESET << std::endl;
			return;
		case VAMPIRE:
			std::cout << PURPLE "Vampire" RESET << std::endl;
			return;
	}
}

void Game::saveToINI(std::ofstream& file)
{
	file << "[Settings]\n";
	file << "revealCards=" << _revealCards << "\n";
	file << "drunkInGame=" << _drunkInGame << "\n";
	file << "altGhostRule=" << _altGhostRule << "\n\n";

	file << "[Game Size]\n";
	file << "playerNo=" << _playerNo << "\n\n";

	file << "[Player]\n";
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i])
		{
			file << "role" << std::setw(2) << std::setfill('0') << i << "=" << _player[i]->getName() << "\n";
		}
	}
	file.close();
}

void Game::loadFromINI(str& file)
{
	INIReader reader(file);

	if (reader.ParseError() < 0)
	{
		clearScreen();
		printTitle();
		std::cout << "Failed to load INI file" << std::endl;
		return ; 
	}
	_wolfNo = 0;
	_vampNo = 0;
	_villagerNo = 0;
	_balance = 0;
	for (int i = 0; i < MAX_ROLES; i++)
	{
		_whichRoles[i] = false;
		_howManyRoles[i] = 0;
	}
	_revealCards = reader.GetBoolean("Settings", "revealCards", false);
	_drunkInGame = reader.GetBoolean("Settings", "drunkInGame", false);
	_altGhostRule = reader.GetBoolean("Settings", "altGhostRule", false);
	_playerNo = reader.GetInteger("Game Size", "playerNo", 0);
	size_t size = _player.size();
	for (size_t i = 0; i < size; i++)
		delete _player[i];
	_player.clear();
	_player.reserve(_playerNo);
	for (int i = 0; ; i++)
	{
		std::ostringstream keyStream;
		keyStream << "role" << std::setw(2) << std::setfill('0') << i;
		str key = keyStream.str();
		if (!reader.HasValue("Player", key))
			break;
		str role = reader.Get("Player", key, "");
		addPlayer(role);
		clearScreen();
		printTitle();
		std::cout << "Game imported" << std::endl;
	}
}

void Game::updateVillageNumbers(int index)
{
	ACard* player = getPlayerByIndex(index);
	if (player->getSide() == WEREWOLF && player->getRole() != SORCERER_ROLE && player->getRole() != MINION_ROLE)
		killWolf();
	else if (player->getSide() == VAMPIRE)
		killVampire();
	else
		killVillager();
}

void Game::checkSideWins()
{
	clearScreen();
	printGameStatus();
	if (_whichRoles[CULTLEADER_ROLE])
	{
		int cult = 0;
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i]->getInCult() && _player[i]->getLife() == ALIVE)
				cult++;
		}
		if (cult == _villagerNo + _wolfNo + _vampNo)
			std::cout << "CULT LEADER WINS" << std::endl;
	}
	if (_whichRoles[HOODLUM_ROLE])
	{
		ACard* hoodlum = getPlayerByRole(HOODLUM_ROLE);
		ACard* player1 = getPlayerByIndex(hoodlum->getPlayer1());
		ACard* player2 = getPlayerByIndex(hoodlum->getPlayer2());
		if (hoodlum->getLife() == ALIVE && player1->getLife() == DEAD && player2->getLife() == DEAD)
			std::cout << "HOODLUM WINS" << std::endl;
	}
	if (_villageWin)
		std::cout << "VILLAGERS WIN" << std::endl;
	if (_vampWin)
		std::cout << "VAMPIRES WIN" << std::endl;
	
	if (_whichRoles[LONEWOLF_ROLE])
	{
		if (getPlayerByRole(LONEWOLF_ROLE)->getLife() == ALIVE && _wolfNo == 1)
			std::cout << "LONE WOLF WINS" << std::endl;
		else if (_vampWin == true && _wolfWin == true)
			std::cout << "WEREWOLVES AND VAMPIRES WIN" << std::endl;
		else if (_wolfWin)
			std::cout << "WEREWOLVES WIN" << std::endl;
	}
	else if (_vampWin == true && _wolfWin == true)
		std::cout << "WEREWOLVES AND VAMPIRES WIN" << std::endl;
	else if (_wolfWin)
		std::cout << "WEREWOLVES WIN" << std::endl;
	if (_whichRoles[TANNER_ROLE])
	{
		if (getPlayerByRole(TANNER_ROLE)->getLife() == DEAD)
			std::cout << "TANNER WINS" << std::endl;
	}
	if (!_villageWin && !_vampWin && !_wolfWin)
		std::cout << "NO ONE WINS" << std::endl;
}

void Game::printDebugMenu()
{
}

void Game::printGameStatus()
{
	const int col1Width = 12;
	const int col2Width = 16;
	const int col3Width = 10;
	const int col4Width = 10;

	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col4Width + 2; i++) std::cout << "-";
		std::cout << "+\n";
	std::cout << "| " << std::setw(col1Width) << std::left << "Player No" << " | ";
	std::cout << std::setw(col2Width) << std::left << "Role" << " | ";
	std::cout << std::setw(col3Width) << std::left << "Status" << " | ";
	std::cout << std::setw(col4Width) << std::left << "Side" << " |\n";
	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col4Width + 2; i++) std::cout << "-";
		std::cout << "+\n";
	if (!_indexSet)
	{
		for (size_t i = 0; i < _player.size(); i++)
		{
			std::cout << "| " << (_player[i]->getDrunk() || !_player[i]->getInVillage() ? GREY : RESET) << std::setw(col1Width) << std::left << _player[i]->getIndex() << RESET << " | ";
			std::cout << (_player[i]->getDrunk() || !_player[i]->getInVillage() ? GREY : RESET) << std::setw(col2Width) << std::left << _player[i]->getName() << RESET << " | ";
			bool life = _player[i]->getLife();
			std::cout << (life ? GREEN : RED) << std::setw(col3Width) << std::left << (life ? "Alive" : "Dead") << RESET << " | ";
			int side = _player[i]->getSide();
			if (side == VILLAGER)
				std::cout << BLUE << std::setw(col4Width) << std::left << "Villager" << RESET << " |\n";
			else if (side == WEREWOLF)
				std::cout << YELLOW << std::setw(col4Width) << std::left << "Werewolf" << RESET << " |\n";
			else if (side == VAMPIRE)
				std::cout << PURPLE << std::setw(col4Width) << std::left << "Vampire" << RESET << " |\n";
		}
	}
	else
	{
		for (size_t i = 0; i < _player.size(); i++)
		{
			ACard* player = getPlayerByIndex(i + 1);
			std::cout << "| " << (player->getDrunk() || !player->getInVillage() ? GREY : RESET) << std::setw(col1Width) << std::left << player->getIndex() << RESET << " | ";
			std::cout << (player->getDrunk() || !player->getInVillage() ? GREY : RESET) << std::setw(col2Width) << std::left << player->getName() << RESET << " | ";
			bool life = player->getLife();
			std::cout << (life ? GREEN : RED) << std::setw(col3Width) << std::left << (life ? "Alive" : "Dead") << RESET << " | ";
			int side = player->getSide();
			if (side == VILLAGER)
				std::cout << BLUE << std::setw(col4Width) << std::left << "Villager" << RESET << " |\n";
			else if (side == WEREWOLF)
				std::cout << YELLOW << std::setw(col4Width) << std::left << "Werewolf" << RESET << " |\n";
			else if (side == VAMPIRE)
				std::cout << PURPLE << std::setw(col4Width) << std::left << "Vampire" << RESET << " |\n";
		}
	}
	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col4Width + 2; i++) std::cout << "-";
		std::cout << "+\n";
	std::cout << "| " << (_nighttime ? "Night " : "Day " ) << std::setw((_nighttime ? 52 : 54)) << _nightNo << "|\n";
	std::cout << std::setw(60) << "|" << "|\n";
	std::cout << "| " << "Alive Villagers: " << std::setw(41) << _villagerNo << "|\n";
	std::cout << "| " << "Alive Werewolves: " << std::setw(40) << _wolfNo << "|\n";
	std::cout << "| " << "Alive Vampires: " << std::setw(42) << _vampNo << "|\n";
	int len = 35;
	if (_villagerNo + _wolfNo + _vampNo > 9)
		len--;
	std::cout << "| " << "Total Alive Players: " << _villagerNo + _wolfNo + _vampNo << "/" << std::setw(len) << _playerNo << "|\n";
	std::cout << "+--------------+------------------+-------------------------+\n";
	std::cout << "| Drunk: " << (_drunkInGame ? GREEN : RED) << std::setw(3) << (_drunkInGame ? "ON" : "OFF") << RESET;
	std::cout << "   | Role Reveal: " << (_revealCards ? GREEN : RED) << std::setw(3) << (_revealCards ? "ON" : "OFF") << RESET;
	std::cout << " | Alt Ghost Rule: " << (_altGhostRule ? GREEN : RED) << std::setw(3) << (_altGhostRule ? "ON" : "OFF") << RESET << "     |\n";
	std::cout << "+--------------+------------------+-------------------------+\n";
	std::cout << std::endl;
}

void Game::printCommands()
{
	const int col1Width = 12;
	const int col2Width = 16;
	const int col3Width = 10;
	const char *commands[10] = { "add", "remove", "resize", "start", "set reveal", "set drunk", "set ghost", "import", "export", "quit" };

	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+\n";
	std::cout << "| " << std::setw(col1Width) << std::left << "Commands" << " | ";
	std::cout << std::setw(col2Width) << std::left << "Roles" << " | ";
	std::cout << std::setw(col3Width) << std::left << "Game Rules" << " |\n ";
	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+\n";
	for (size_t i = 0; i < _player.size(); i++)
	{
		std::cout << "| " << (commands[i] ? commands[i] : "") << "| " << (_player[i] ? _player[i]->getName() : "");
	}
	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+\n";
}
