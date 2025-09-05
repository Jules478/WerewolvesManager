#include "../inc/Game.hpp"

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

void error_max()
{
	clearScreen();
	printTitle();
	std::cout << "Maximum number already in game" << std::endl;
}

str get_input()
{
	str input;

	if (!std::getline(std::cin, input))
		exit(0);
	return input;
}


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

void Game::closeProgram()
{
	for (size_t i = 0; i < _player.size(); i++)
		delete _player[i];
	exit(0);
}

ACard* Game::getPlayerByIndex(int index)
{
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getIndex() == index)
			return _player[i];
	}
	return nullptr;
}

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
		return (number >= 0 && number <= 68);
	}
	catch (const std::exception&)
	{
		return false;
	}
}

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

Game::Game(int playerno) : _playerNo(playerno)
{
	_player.reserve(playerno);
	for (int i = 0; i < 68; i++)
	{
		_diedInTheNight[i] = -1;
		_assignedPlayers[i] = -1;
	}
	for (int i = 0; i < MAX_ROLES; i++)
	{
		_whichRoles[i] = false;
		_howManyRoles[i] = 0;
	}
}

Game::~Game()
{
	for (size_t i = 0; i < _player.size(); i++)
		delete _player[i];
}

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

void Game::nightPhase()
{
	clearScreen();
	printGameStatus();
	if (_whichRoles[TOUGHGUY_ROLE])
	{
		ACard* tough = getPlayerByRole(TOUGHGUY_ROLE);
		if (tough->getAbilityUsed(false) && tough->getLife() == ALIVE)
			setNightlyDeaths(tough->getIndex());
	}
	if (_nightNo == 4 && _drunkInGame)
	{
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i]->getDrunk())
			{
				_player[i]->setDrunk();
				if (_player[i]->getLife())
				{
					std::cout << "Wake up the Drunk (" << _player[i]->getIndex() << ")\nGive the Drunk their new role" << std::endl;
					std::cout << "\n\n" << "Press enter to continue..." << std::endl;
					get_input();
				}
				else
				{
					if (_revealCards == false)
					{
						std::cout << "The Drunk is already dead. Call for the Drunk to conceal this fact" << std::endl;
						std::cout << "\n\n" << "Press enter to continue..." << std::endl;
						get_input();
					}
				}
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[OLDMAN_ROLE])
	{
		getPlayerByRole(OLDMAN_ROLE)->Dies();
	}
	int wolf = -1;
	if (_wolfNo > 0)
	{
		if (_wolfUpsetTummy == false)
		{
			std::cout << "Wake up the werewolves: \n";
			for (int i = 0; i < _playerNo; i++)
			{
				if (_player[i]->getSide() == WEREWOLF && _player[i]->getDrunk() == false && _player[i]->getLife() == ALIVE && _player[i]->getRole() != SORCERER_ROLE && _player[i]->getRole() != MINION_ROLE)
				{
					wolf = _player[i]->getIndex();
					std::cout <<_player[i]->getName() << " (" << wolf << ") \n";
				}
			}
			if (_secondWolfKill == true)
			{
				std::cout << "\nThe Wolf Cub has been killed. The Werewolves will attack twice tonight" << std::endl;
				std::cout << "\n\n" << "Choose first player to attack: ";
			}
			else
			std::cout << "\n\n" << "Choose player to attack: ";
			if (wolf != -1)
			{
				str input = get_input();
				while (!isValidAlivePlayer(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				getPlayerByIndex(std::stoi(input))->beAttacked(wolf);
			}
			clearScreen();
			printGameStatus();
			if (_secondWolfKill == true)
			{
				std::cout << "Wake up the werewolves: \n";
				for (int i = 0; i < _playerNo; i++)
				{
					if (_player[i]->getSide() == WEREWOLF && _player[i]->getDrunk() == false && _player[i]->getLife() == ALIVE && _player[i]->getRole() != SORCERER_ROLE && _player[i]->getRole() != MINION_ROLE)
					{
						wolf = _player[i]->getIndex();
						std::cout <<_player[i]->getRole() << " (" << wolf << ") \n";
					}
				}
				std::cout << "\nThe Wolf Cub has been killed. The Werewolves will attack twice tonight" << std::endl;
				std::cout << "\n\n" << "Choose second player to attack: ";
				if (wolf != -1)
				{
					str input = get_input();
					while (!isValidAlivePlayer(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input();
					}
					getPlayerByIndex(std::stoi(input))->beAttacked(wolf);
				}
				clearScreen();
				printGameStatus();
			}
		}
		else
		{
			clearScreen();
			printGameStatus();
			std::cout << "The Werewolves ate the Diseased last night. They will not feed tonight" << std::endl;
			if (_revealCards == false)
				std::cout << "Call for the Werewolves and ask for a kill to conceal this fact" << std::endl;
			std::cout << "\nPress enter to continue..." << std::endl;
			get_input();
			clearScreen();
			printGameStatus();
		}
	}
	_wolfUpsetTummy = false;
	_secondWolfKill = false;
	int vamp = -1;
	if (_vampNo > 0)
	{
		std::cout << "Wake up the vampires: \n";
			for (int i = 0; i < _playerNo; i++)
			{
				if (_player[i]->getSide() == VAMPIRE && _player[i]->getLife() == ALIVE)
				{
					vamp = _player[i]->getIndex();
					std::cout <<_player[i]->getName() << " (" << vamp << ") \n";
				}
			}
			if (vamp != -1)
			{
				std::cout << "\n\n" << "Choose player to attack: ";
				str input = get_input();
				while (!isValidAlivePlayer(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				getPlayerByIndex(std::stoi(input))->beAttacked(vamp);
			}
			clearScreen();
			printGameStatus();
	}
	wakeAllActiveRoles();
}

void Game::firstNight()
{
	int seer1 = -1;
	int seer2 = -1;
	str input = "";
	clearScreen();
	printGameStatus();
	if (_drunkInGame)
	{
		for (size_t i = 0; i < _player.size(); i++)
			std::cout << std::setw(2) << i + 1 << " | " << _player[i]->getName() << std::endl;
		std::cout << "\nEnter role removed from the game: ";
		str input = get_input();
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter role number: ";
			input = get_input();
		}
		int index = std::stoi(input) - 1;
		_player[index]->setDrunk();
		_drunkRole = _player[index]->getRole();
		clearScreen();
		printGameStatus();
		std::cout << "Wake up the Drunk" << std::endl;
		std::cout << "Enter player number: ";
		input = get_input();
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input();
		}
		index = std::stoi(input);
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i]->getDrunk())
			{
				_player[i]->setIndex(index);
				break;
			}	
		}
		_assignedPlayers[_assignedIndex++] = index;
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[WOLFCUB_ROLE])
	{
		if (_drunkRole == WOLFCUB_ROLE)
		{
			std::cout << "The Wolf Cub is drunk. Call for them to conceal this fact" << std::endl;
			std::cout << "\n\n" << "Press enter to continue..." << std::endl;
			get_input();
		}
		else
		{
			std::cout << "Wake up the Wolf Cub" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input();
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int index = std::stoi(input);
			getPlayerByRole(WOLFCUB_ROLE)->setIndex(index);
			_assignedPlayers[_assignedIndex++] = index;
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[LONEWOLF_ROLE])
	{
		if (_drunkRole == LONEWOLF_ROLE)
		{
			std::cout << "The Lone Wolf is drunk. Call for them to conceal this fact" << std::endl;
			std::cout << "\n\n" << "Press enter to continue..." << std::endl;
			get_input();
		}
		else
		{
			std::cout << "Wake up the Lone Wolf" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input();
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int index = std::stoi(input);
			getPlayerByRole(LONEWOLF_ROLE)->setIndex(index);
			_assignedPlayers[_assignedIndex++] = index;
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[WEREWOLF_ROLE])
	{
		bool drunkWolf = false;
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_drunkRole == WEREWOLF_ROLE && drunkWolf == false)
			{
				drunkWolf = true;
				if (_wolfNo == 1)
				{
					std::cout << "A Werewolf is drunk. Call for them to conceal this fact" << std::endl;
					std::cout << "\n\n" << "Press enter to continue..." << std::endl;
					get_input();
				}
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Wake up all the Werewolves" << std::endl;
				if (_player[i]->getRole() == WEREWOLF_ROLE)
				{
					std::cout << "Enter player number: ";
					input = get_input();
					while (!isValidPlayerEntry(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input();
					}
					int index = std::stoi(input);
					_player[i]->setIndex(index);
					_assignedPlayers[_assignedIndex++] = index;
				}
			}
		}
		if (_whichRoles[MINION_ROLE])
		{
			if (_drunkRole == MINION_ROLE)
			{
				std::cout << "The Minion is drunk. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input();
			}
			else
			{
				std::cout << "Wake up the Minion" << std::endl;
				std::cout << "Enter player number: ";
				input = get_input();
				while (!isValidPlayerEntry(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int index = std::stoi(input);
				getPlayerByRole(MINION_ROLE)->setIndex(index);
				_assignedPlayers[_assignedIndex++] = index;
			}

		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[VAMPIRE_ROLE])
	{
		bool drunkVamp = false;
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_drunkRole == VAMPIRE_ROLE && drunkVamp == false)
			{
				drunkVamp = true;
				i++;
				std::cout << "A Vampire is drunk. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input();
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Wake up the Vampires" << std::endl;
				if (_player[i]->getRole() == VAMPIRE_ROLE)
				{
					std::cout << "Enter player number: ";
					input = get_input();
					while (!isValidPlayerEntry(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input();
					}
					int index = std::stoi(input);
					_player[i]->setIndex(index);
					_assignedPlayers[_assignedIndex++] = index;
				}
			}
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[MASON_ROLE])
	{
		bool drunkMason = false;
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_drunkRole == MASON_ROLE && drunkMason == false)
			{
				drunkMason = true;
				i++;
				std::cout << "A Mason is drunk. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input();
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Wake up the Masons" << std::endl;
				if (_player[i]->getRole() == MASON_ROLE)
				{
					std::cout << "Enter player number: ";
					input = get_input();
					while (!isValidPlayerEntry(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input();
					}
					int index = std::stoi(input);
					_player[i]->setIndex(index);
					_assignedPlayers[_assignedIndex++] = index;
				}
			}
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[HOODLUM_ROLE])
	{
		if (_drunkRole == HOODLUM_ROLE)
		{
			std::cout << "The Hoodlum is drunk. Call for them to conceal this fact" << std::endl;
			std::cout << "\n\n" << "Press enter to continue..." << std::endl;
			get_input();
		}
		else
		{
			ACard* hoodlum = getPlayerByRole(HOODLUM_ROLE);
			std::cout << "Wake up the Hoodlum" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input();
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int index = std::stoi(input);
			hoodlum->setIndex(index);
			_assignedPlayers[_assignedIndex++] = index;
			clearScreen();
			printGameStatus();
			std::cout << "Which players does the Hoodlum want to be dead by the end of the Game?" << std::endl;
			std::cout << "Enter first player: ";
			input = get_input();
			while (!isValidPlayerNumberAlt(input, hoodlum->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			hoodlum->setPlayer1(std::stoi(input));
			clearScreen();
			printGameStatus();
			std::cout << "Which players does the Hoodlum want to be dead by the end of the Game?" << std::endl;
			std::cout << "Enter second player: ";
			input = get_input();
			while (!isValidPlayerNumberAlt(input, hoodlum->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			hoodlum->setPlayer2(std::stoi(input));
		}
	}
	clearScreen();
	printGameStatus();
	for (size_t i = 0; i < _player.size(); i++)
	{
		int role = _player[i]->getRole();
		if (role == SEER_ROLE)
		{
			if (_player[i]->getAbilityUsed(true) == false)
				seer1 = i;
			else
				seer2 = i;
		}
		else if (role == CUPID_ROLE || role == DOPPELGANGER_ROLE || role == HOODLUM_ROLE || role == MINION_ROLE || role == MASON_ROLE || role == VILLAGER_ROLE || role == WOLFCUB_ROLE || role == LONEWOLF_ROLE || role == WEREWOLF_ROLE || role == VAMPIRE_ROLE)
			continue;
		else
		{
			clearScreen();
			printGameStatus();
			if (_drunkRole == role)
			{
				std::cout << _player[i]->getName() << " is drunk. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input();
			}
			else
			{
				std::cout << "Wake up " << _player[i]->getName() << std::endl;
				std::cout << "Enter player number: ";
				input = get_input();
				while (!isValidPlayerEntry(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int index = std::stoi(input);
				_player[i]->setIndex(index);
				_assignedPlayers[_assignedIndex++] = index;
			}
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[CUPID_ROLE])
	{
		if (_drunkRole == CUPID_ROLE)
		{
			std::cout << "Cupid is drunk. Call for them to conceal this fact" << std::endl;
			std::cout << "\n\n" << "Press enter to continue..." << std::endl;
			get_input();
		}
		else
		{
			ACard* cupid = getPlayerByRole(CUPID_ROLE);
			std::cout << "Wake up Cupid" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input();
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int index = std::stoi(input);
			cupid->setIndex(index);
			_assignedPlayers[_assignedIndex++] = index;
			clearScreen();
			printGameStatus();
			std::cout << "Which players does Cupid want to fall in love?" << std::endl;
			std::cout << "Enter first player: ";
			input = get_input();
			while (!isValidPlayerNumberAlt(input, cupid->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			cupid->setPlayer1(std::stoi(input));
			clearScreen();
			printGameStatus();
			std::cout << "Which players does Cupid want to fall in love?" << std::endl;
			std::cout << "Enter second player: ";
			input = get_input();
			while (!isValidPlayerNumberAlt(input, cupid->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			cupid->setPlayer2(std::stoi(input));
			clearScreen();
			printGameStatus();
			std::cout << "Wake up the Lovers (" << cupid->getPlayer1() << " & " << cupid->getPlayer2() << ")" << std::endl;
			std::cout << "\nPress Enter to continue..." << std::endl;
			get_input();
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[DOPPELGANGER_ROLE])
	{
		ACard* dopp = getPlayerByRole(DOPPELGANGER_ROLE);
		std::cout << "Wake up the Doppelganger" << std::endl;
		std::cout << "Enter player number: ";
		input = get_input();
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input();
		}
		int index = std::stoi(input);
		dopp->setIndex(index);
		_assignedPlayers[_assignedIndex++] = index;
		clearScreen();
		printGameStatus();
		std::cout << "Which player does the Doppelganger wish to mirror?: ";
		input = get_input();
		while (!isValidPlayerNumberAlt(input, dopp->getIndex()))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input();
		}
		dopp->setCopiedPlayer(std::stoi(input));
	}
	clearScreen();
	printGameStatus();
	std::cout << "Wake up";
	if (seer2 != -1)
		std::cout << " Female";
	std::cout << " Seer" << std::endl;
	std::cout << "Enter player number: ";
	input = get_input();
	while (!isValidPlayerEntry(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input();
	}
	int index = std::stoi(input);
	_player[seer1]->setIndex(index);
	_assignedPlayers[_assignedIndex++] = index;
	clearScreen();
	printGameStatus();
	if (seer2 != -1)
	{
		std::cout << "Wake up Male Seer" << std::endl;
		std::cout << "Enter player number: ";
		input = get_input();
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input();
		}
		int index = std::stoi(input);
		_player[seer2]->setIndex(index);
		_assignedPlayers[_assignedIndex++] = index;
		clearScreen();
		printGameStatus();
	}
	for (size_t i = 0; i < _player.size(); i++)
	{
		int index = 1;
		while (_player[i]->getIndex() == -1 && _player[i]->getRole() != SEER_ROLE)
		{
			for (int j = 0; j < 68; j++)
			{
				if (_assignedPlayers[j] == index)
					break;
				else if (_assignedPlayers[j] == -1)
				{
					_assignedPlayers[j] = index;
					_player[i]->setIndex(index);
					break;
				}
			}
			index++;
		}
	}
	_indexSet = true;
	clearScreen();
	printGameStatus();
	input = "";
	std::cout << "Wake up";
	if (seer2 != -1)
		std::cout << " Female";
	std::cout << " Seer" << std::endl;
	std::cout << "Player number to see: ";
	input = get_input();
	while (!isValidPlayerNumber(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input();
	}
	int res = _player[seer1]->See(std::stoi(input));
	std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
	std::cout << "\n\n" << "Press Enter to continue...";
	get_input();
	clearScreen();
	printGameStatus();
	if (seer2 != -1)
	{
		input = "";
		std::cout << "Wake up Male Seer" << std::endl;
		std::cout << "Player number to see: ";
		input = get_input();
		while (!isValidPlayerNumber(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input();
		}
		int res = _player[seer2]->See(std::stoi(input));
		std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
		std::cout << "\n\n" << "Press Enter to continue...";
		get_input();
	}
	setTimeOfDay();
	clearScreen();
	printGameStatus();
	std::cout << "Let the villagers talk amongst themselves. There are no lynchings today" << std::endl;
	if (_whichRoles[GHOST_ROLE])
	{
		ACard* ghost = getPlayerByRole(GHOST_ROLE);
		ghost->setLife(DEAD);
		updateVillageNumbers(ghost->getIndex());
		std::cout << "The Ghost (" << ghost->getIndex() << ") has died. They will stay awake during the night phase" << std::endl;
		if (_whichRoles[CUPID_ROLE])
		{
			ACard* cupid = getPlayerByRole(CUPID_ROLE);
			ACard* player1 = getPlayerByIndex(cupid->getPlayer1());
			ACard* player2 = getPlayerByIndex(cupid->getPlayer2());
			if (cupid->getPlayer1() == ghost->getIndex() && player2->getLife() == ALIVE)
			{
				std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
				player2->setLife(DEAD);
				updateVillageNumbers(cupid->getPlayer2());
				checkDoppelganger(*player2);
			}
			else if (cupid->getPlayer2() == ghost->getIndex() && player1->getLife() == ALIVE)
			{
				std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
				player1->setLife(DEAD);
				updateVillageNumbers(cupid->getPlayer1());
				checkDoppelganger(*player1);
			}
		}
	}
	std::cout << "\nPress Enter to continue..." << std::endl;
	get_input();
	setTimeOfDay();
	_nightNo++;
	clearScreen();
	printGameStatus();
}

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
		_vampWin = true;
		_wolfWin = true;
		return true;
	}
	return false;
}

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

int* Game::getNightlyDeaths()
{
	return _diedInTheNight;
}

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
				// ACard* hunter = getPlayerByRole(HUNTER_ROLE);
				// str input;
				// int victim;
				// if (_revealCards)
				// {
				// 	std::cout << "Enter player to kill: ";
				// 	input = get_input();
				// 	while (!isValidAlivePlayer(input))
				// 	{
				// 		std::cout << "ERROR: Enter index: ";
				// 		input = get_input();
				// 	}
				// 	victim = std::stoi(input);
				// }
				// else
				// {
				// 	victim = hunter->getVictim();
				// }
				// hunter->takePlayerWith(victim);
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

void Game::setVampVictim(int index)
{
	_vampireVictim = index;
}

bool Game::getTimeOfDay() const
{
	return _nighttime;
}

int Game::getWereNo() const
{
	return _wolfNo;
}

std::vector<ACard*>& Game::getPlayers()
{
	return _player;
}

void Game::setBalance(int value)
{
	_balance = value;
}

int Game::getBalance() const
{
	return _balance + (_drunkInGame * -3) + (_altGhostRule * 2);
}

int Game::getPlayerNo() const
{
	return _playerNo;
}

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
		str input = get_input();
		while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
		{
			std::cout << "ERROR: Enter choice: ";
			input = get_input();
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

void Game::dayPhase()
{
	clearScreen();
	printGameStatus();
	std::cout << "Wake up all players\n" << std::endl;
	std::cout << "The following players died in the night: " << std::endl;
	for (int i = 0; i < 68; i++)
	{
		if (_diedInTheNight[i] == -1)
			continue;
		ACard *dead = getPlayerByIndex(_diedInTheNight[i]);
		if (dead->getRole() != CURSED_ROLE)
		{
			if (_whichRoles[CURSED_ROLE] && dead->getRole() == CURSED_ROLE && dead->getAbilityUsed(true) == true)
			{
				dead->setAbilityUsed();
				continue;
			}
			else
			{
				displayDeath(dead->getIndex());
			}
		}
	}
	resetNightlyDeaths();
	std::cout << std::endl;
	if (checkWin())
	{
		checkSideWins();
		closeProgram();
	}
	std::cout << "\n\n" << "Press Enter to continue...";
	get_input();
	clearScreen();
	printGameStatus();
	if (_whichRoles[OLDHAG_ROLE])
	{
		for (size_t i = 0; i < _player.size(); i++)
		{
			if (_player[i]->getInVillage() == false)
			{
				std::cout << "Player " << _player[i]->getIndex() << " (" << _player[i]->getName() << ") has been exiled. They cannot participate in this day phase" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input();
				break ;
			}
		}
	}
	while (1)
	{
		if (_secondLynching)
			std::cout << "The Troublemaker has called for two lynchings today" << std::endl;
		std::cout << "Enter index of lynched player (if no player was lynched enter -1): ";
		str input = get_input();
		while (!isValidAlivePlayer(input))
		{
			if (input == "-1")
				break;
			std::cout << "ERROR: Enter index: ";
			input = get_input();
		}
		int index = std::stoi(input);
		ACard *lynch = getPlayerByIndex(index);
		if (index != -1)
		{
			if (_vampireVictim != -1)
			{
				ACard *vamp = getPlayerByIndex(_vampireVictim);
				if (vamp->getRole() == HUNTER_ROLE)
					std::cout << "The Hunter has died to the Vampires. ";
				vamp->setLife(DEAD);
				if (vamp->getRole() == WOLFCUB_ROLE)
					wolfCubKilled();
				std::cout << "\nThe Vampires have killed ";
				displayDeath(_vampireVictim);
				if (_whichRoles[CUPID_ROLE])
				{
					ACard* cupid = getPlayerByRole(CUPID_ROLE);
					ACard* player1 = getPlayerByIndex(cupid->getPlayer1());
					ACard* player2 = getPlayerByIndex(cupid->getPlayer2());
					if (cupid->getPlayer1() == _vampireVictim && player2->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
						player2->setLife(DEAD);
						if (player2->getRole() == WOLFCUB_ROLE)
							wolfCubKilled();
						updateVillageNumbers(cupid->getPlayer2());
						checkDoppelganger(*player2);
					}
					else if (cupid->getPlayer2() == _vampireVictim && player1->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
						player1->setLife(DEAD);
						if (player1->getRole() == WOLFCUB_ROLE)
							wolfCubKilled();
						updateVillageNumbers(cupid->getPlayer1());
						checkDoppelganger(*player1);
					}
				}
				updateVillageNumbers(_vampireVictim);
				if (_vampireVictim == index)
				{
					_vampireVictim = -1;
					continue;
				}
				_vampireVictim = -1;
			}
			std::cout << "Enter number of votes for lynching: ";
			input = get_input();
			while (!isValidVoteNumber(input))
			{
				std::cout << "ERROR: Enter vote count: ";
				input = get_input();
			}
			int votes = std::stoi(input);
			if (_whichRoles[MAYOR_ROLE])
			{
				ACard* mayor = getPlayerByRole(MAYOR_ROLE);
				if (mayor->getLife() == ALIVE)
				{
					std::cout << "Did the Mayor (" << mayor->getIndex() << ") vote for the lynching? (y/n): ";
					input = get_input();
					while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
					{
						std::cout << "ERROR: Enter vote: ";
						input = get_input();
					}
					if (input == "y" || input == "Y")
						votes++;
				}
			}
			if (votes > (_villagerNo + _vampNo + _wolfNo) / 2)
			{
				if (_whichRoles[MARTYR_ROLE])
				{
					ACard* martyr = getPlayerByRole(MARTYR_ROLE);
					if (martyr->getLife() == ALIVE)
					{
						std::cout << "Does the Martyr (" << martyr->getIndex() << ") wish to take the place of the lynched player? (y/n): ";
						input = get_input();
						while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
						{
							std::cout << "ERROR: Enter vote: ";
							input = get_input();
						}
						if (input == "y" || input == "Y")
						{
							lynch = martyr;
							martyr->setAbilityUsed();
						}
					}
					else
					{
						if (_revealCards == false && martyr->getAbilityUsed(true) == false)
						{
							std::cout << "The Martyr is dead. Call for them to conceal this fact" << std::endl;
							std::cout << "\n\n" << "Press Enter to continue...";
							get_input();
							clearScreen();
							printGameStatus();
						}
					}
				}
				if (lynch->getRole() == PRINCE_ROLE && lynch->getAbilityUsed(false) == false)
					std::cout << "\nThe Prince (" << lynch->getIndex() << ") has been lynched. Reveal their role. The Prince does not die" << std::endl;
				else
				{
					std::cout << "\nVote was successful. The village has lynched "; // << lynch->getName() << " (" << index << ") | Side: ";
					displayDeath(lynch->getIndex());
				}
				lynch->beLynched();
				if (lynch->getRole() == HUNTER_ROLE)
						displayDeath(lynch->getVictim());
				std::cout << std::endl;
				if (_whichRoles[CUPID_ROLE])
				{
					ACard* cupid = getPlayerByRole(CUPID_ROLE);
					ACard* player1 = getPlayerByIndex(cupid->getPlayer1());
					ACard* player2 = getPlayerByIndex(cupid->getPlayer2());
					if (cupid->getPlayer1() == index && player2->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
						player2->setLife(DEAD);
						updateVillageNumbers(cupid->getPlayer2());
						checkDoppelganger(*player2);
					}
					else if (cupid->getPlayer2() == index && player1->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
						player1->setLife(DEAD);
						updateVillageNumbers(cupid->getPlayer1());
						checkDoppelganger(*player1);
					}
				}
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
				if (_secondLynching)
				{
					_secondLynching = false;
					continue;
				}
				else
					break;
			}
			clearScreen();
			printGameStatus();
			std::cout << "Vote was unsuccessful" << std::endl;
		}
		else
			break;
	}
	_nightNo++;
	clearScreen();
	printGameStatus();
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

ACard*	Game::getSeer(bool which)
{
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getRole() == SEER_ROLE && _player[i]->getAbilityUsed(true) == which)
			return _player[i];
	}
	return nullptr;
}

// ACard*	Game::getPlayerByRole(int role)
// {
// 	for (size_t i = 0; i < _player.size(); i++)
// 	{
// 		if (_player[i] && _player[i]->getRole() == role)
// 			return _player[i];
// 	}
// 	return nullptr;
// }

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
				{
					i = 0;
					role = DOPPELGANGER_ROLE;
				}
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

void Game::wakeAllActiveRoles()
{
	if (_whichRoles[APPRENTICESEER_ROLE])
	{
		ACard* apseer = getPlayerByRole(APPRENTICESEER_ROLE);
		if (apseer->getLife() == ALIVE)
		{
			std::cout << "Wake the Apprentice Seer (" << apseer->getIndex() << ")\n" << std::endl;
			if (getSeer(FIRST)->getLife() == DEAD || (_howManyRoles[SEER_ROLE] == 2 && getSeer(SECOND)->getLife() == DEAD))
				std::cout << "The Apprentice Seer is now the Seer" << std::endl;
			else
				std::cout << "The Apprentice Seer is NOT the Seer" << std::endl;
			std::cout << "\n\n" << "Press enter to continue..." << std::endl;
			get_input();
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Apprentice Seer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[AURASEER_ROLE])
	{
		ACard* aura = getPlayerByRole(AURASEER_ROLE);
		if (aura->getLife() == ALIVE)
		{
			std::cout << "Wake the Aura Seer (" << aura->getIndex() << ")\n" << std::endl;
			std::cout << "Player number to see: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int res = aura->See(std::stoi(input));
			std::cout << "Player " << input << " has " << (res ? "a special role" : "no special role") << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input();
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Aura Seer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[BODYGUARD_ROLE])
	{
		ACard* bodyg = getPlayerByRole(BODYGUARD_ROLE);
		if (bodyg->getLife() == ALIVE)
		{
			std::cout << "Wake the Bodyguard (" << bodyg->getIndex() << ")\n" << std::endl;
			std::cout << "Player to protect: ";
			str input = get_input();
			while (!isValidPlayerNumberAlt(input, bodyg->getPlayer1()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int plyr = std::stoi(input);
			bodyg->Protect(plyr);
			bodyg->setPlayer1(plyr);
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Bodyguard is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[HUNTER_ROLE] && !_revealCards)
	{
		ACard* hunter = getPlayerByRole(HUNTER_ROLE);
		if (hunter->getLife() == ALIVE)
		{
			std::cout << "Wake the Hunter (" << hunter->getIndex() << ")\n" << std::endl;
			std::cout << "Player to target if the Hunter dies: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			hunter->setVictim(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Hunter is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[MAGICIAN_ROLE])
	{
		ACard* magi = getPlayerByRole(MAGICIAN_ROLE);
		if (magi->getLife() == ALIVE)
		{
			std::cout << "Wake the Magician (" << magi->getIndex() << ")\n" << std::endl;
			if (magi->getSpellUsed("heal") == false)
			{
				std::cout << "Player to protect (Enter -1 to not use heal): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stoi(input);
				if (num != -1)
				{
					magi->Protect(num);
					magi->setSpellUsed("heal");
				}
			}
			else
			{
				std::cout << "The Magician has used their heal spell. Call for it to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
			clearScreen();
			printGameStatus();
			std::cout << "Wake the Magician (" << magi->getIndex() << ")\n" << std::endl;
			if (magi->getSpellUsed("kill") == false)
			{
				std::cout << "Player to kill (Enter -1 to not use kill): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stoi(input);
				if (num != -1)
				{
					getPlayerByIndex(num)->beAttacked(magi->getIndex());
					magi->setSpellUsed("kill");
				}
			}
			else
			{
				std::cout << "The Magician has used their kill spell. Call for it to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Magician is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[OLDHAG_ROLE])
	{
		ACard* hag = getPlayerByRole(OLDHAG_ROLE);
		if (hag->getLife() == ALIVE)
		{
			std::cout << "Wake the Old Hag (" << hag->getIndex() << ")\n" << std::endl;
			std::cout << "Player number to exile for the next day phase: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			hag->Pox(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Old Hag is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[PI_ROLE])
	{
		ACard* pi = getPlayerByRole(PI_ROLE);
		if (pi->getLife() == ALIVE)
		{
			std::cout << "Wake the PI (" << pi->getIndex() << ")\n" << std::endl;
			if (pi->getAbilityUsed(false) == false)
			{
				std::cout << "Player number to see (enter -1 to not use ability): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stoi(input);
				if (num != -1)
				{
					int res = pi->See(num);
					std::cout << "Player " << input << (res ? " or their neighbour is NOT a Villager" : " and their neighbours are Villagers") << std::endl;
					std::cout << "\n\n" << "Press Enter to continue...";
					get_input();
				}
			}
			else
			{
				std::cout << "The PI has used their ability. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The PI is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[PRIEST_ROLE])
	{
		ACard* priest = getPlayerByRole(PRIEST_ROLE);
		if (priest->getLife() == ALIVE)
		{
			std::cout << "Wake the Priest (" << priest->getIndex() << ")\n" << std::endl;
			if (priest->getAbilityUsed(false) == false)
			{
				std::cout << "Player number to protect (enter -1 to not use ability): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stoi(input);
				if (num != -1)
					priest->Protect(num);
			}
			else
			{
				std::cout << "The Priest has used their ability. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Priest is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[SEER_ROLE])
	{
		ACard* seer = getSeer(FIRST);
		if (seer->getLife() == ALIVE || (seer->getLife() == DEAD && _whichRoles[APPRENTICESEER_ROLE] && getPlayerByRole(APPRENTICESEER_ROLE)->getLife() == ALIVE))
		{
			std::cout << "Wake the" << (_howManyRoles[SEER_ROLE] == 2 ? " Female" : "") << " Seer (" << seer->getIndex() << ")\n" << std::endl;
			std::cout << "Player number to see: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int res = seer->See(std::stoi(input));
			std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input();
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The" << (_howManyRoles[SEER_ROLE] == 2 ? " Female" : "") << " Seer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
		if (_howManyRoles[SEER_ROLE] == 2)
		{
			ACard* seer = getSeer(SECOND);
			if (seer->getLife() == ALIVE || (seer->getLife() == DEAD && _whichRoles[APPRENTICESEER_ROLE] && getPlayerByRole(APPRENTICESEER_ROLE)->getLife() == ALIVE))
			{
				std::cout << "Wake the Male Seer (" << seer->getIndex() << ")\n" << std::endl;
				std::cout << "Player number to see: ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int res = seer->See(std::stoi(input));
				std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
			else
			{
				if (_revealCards == false)
				{
					std::cout << "The Male Seer is dead. Call for them to conceal this fact" << std::endl;
					std::cout << "\n\n" << "Press Enter to continue...";
					get_input();
				}
			}
			clearScreen();
			printGameStatus();
		}
	}
	if (_whichRoles[SPELLCASTER_ROLE])
	{
		ACard* spell = getPlayerByRole(SPELLCASTER_ROLE);
		if (spell->getLife() == ALIVE)
		{
			std::cout << "Wake the Spellcaster (" << spell->getIndex() << ")\n" << std::endl;
			std::cout << "Choose a player to silence" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Spellcaster is dead. Call for them to conceal this fact" << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input();
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[TROUBLEMAKER_ROLE])
	{
		ACard* trouble = getPlayerByRole(TROUBLEMAKER_ROLE);
		if (trouble->getLife() == ALIVE)
		{
			if (trouble->getAbilityUsed(false) == false)
			{
				std::cout << "Wake the Troublemaker (" << trouble->getIndex() << ")\n" << std::endl;
				std::cout << "Ask if there will be two lynchings the next day (y/n): " << std::endl;
				str input = get_input();
				while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
				{
					std::cout << "ERROR: Enter choice: ";
					input = get_input();
				}
				if (input == "y" || input == "Y")
				{
					_secondLynching = true;
					trouble->setAbilityUsed();
				}
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Troublemaker is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[WITCH_ROLE])
	{
		ACard* witch = getPlayerByRole(WITCH_ROLE);
		if (witch->getLife() == ALIVE)
		{
			std::cout << "Wake the Witch (" << witch->getIndex() << ")\n" << std::endl;
			if (witch->getSpellUsed("heal") == false)
			{
				std::cout << "Player to protect (Enter -1 to not use heal): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stoi(input);
				if (num != -1)
				{
					witch->Protect(num);
					witch->setSpellUsed("heal");
				}
			}
			else
			{
				std::cout << "The Witch has used their heal spell. Call for it to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
			clearScreen();
			printGameStatus();
			std::cout << "Wake the Witch (" << witch->getIndex() << ")\n" << std::endl;
			if (witch->getSpellUsed("kill") == false)
			{
				std::cout << "Player to kill (Enter -1 to not use kill): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stoi(input);
				if (num != -1)
				{
					getPlayerByIndex(num)->beAttacked(witch->getIndex());
					witch->setSpellUsed("kill");
				}
			}
			else
			{
				std::cout << "The Witch has used their kill spell. Call for it to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Witch is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[SORCERER_ROLE])
	{
		ACard* sorc = getPlayerByRole(SORCERER_ROLE);
		if (sorc->getLife() == ALIVE)
		{
			std::cout << "Wake the Sorcerer (" << sorc->getIndex() << ")\n" << std::endl;
			std::cout << "Player number to see: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int res = sorc->SorcSee(std::stoi(input));
			std::cout << "Player " << input << " is " << (res ? "the Seer" : "not the Seer") << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input();
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Sorcerer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[CURSED_ROLE])
	{
		ACard* curse = getPlayerByRole(CURSED_ROLE);
		if (curse->getLife() == ALIVE)
		{
			bool turned = false;
			std::cout << "Wake the Cursed (" << curse->getIndex() << ")\n" << std::endl;
			if (curse->getSide() == VILLAGER)
			{
				std::cout << "The Cursed is ";
				int index = curse->getIndex();
				for (int i = 0; i < 68; i++)
				{
					if (_diedInTheNight[i] == index)
					{
						turned = true;
						break;
					}
				}
				std::cout << (turned ? "now a werewolf" : "still a villager") << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
			else
			{
				std::cout << "The Cursed is already a werewolf. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Cursed is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[DOPPELGANGER_ROLE])
	{
		ACard* dopp = getPlayerByRole(DOPPELGANGER_ROLE);
		if (dopp->getLife() == ALIVE)
		{
			if (dopp->getAbilityUsed(true) == true)
			{
				std::cout << "The Doppelganger has already replaced their target" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
			else
			{
				bool steal = false;
				int index = dopp->getCopiedPlayer();
				std::cout << "Wake the Doppelganger (" << dopp->getIndex() << ")\n" << std::endl;
				for (int i = 0; i < 68; i++)
				{
					if (_diedInTheNight[i] == index)
					{
						steal = true;
						break;
					}
				}
				if (steal == false)
					steal = !getPlayerByIndex(index)->getLife();
				std::cout << (steal ? "Their target is dead. Show the doppelganger their new role" : "Their target is alive") << std::endl;
				if (steal)
					dopp->setAbilityUsed();
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Doppelganger is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[CULTLEADER_ROLE])
	{
		ACard* cult = getPlayerByRole(CULTLEADER_ROLE);
		if (cult->getLife() == ALIVE)
		{
			std::cout << "Wake the Cult Leader (" << cult->getIndex() << ")\n" << std::endl;
			std::cout << "Player to convert: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			cult->Convert(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Cult Leader is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input();
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[GHOST_ROLE] || (_altGhostRule && _villagerNo + _wolfNo + _vampNo < _playerNo))
	{
		std::cout << "Ask the Ghost for the letter they wish to give to the Village" << std::endl;
		std::cout << "\n\n" << "Press Enter to continue...";
		get_input();
		clearScreen();
		printGameStatus();
	}
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
