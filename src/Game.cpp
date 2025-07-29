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
	{"oldhag", OLDHAG_ROLE},
	{"oldman", OLDMAN_ROLE},
	{"pi", PI_ROLE},
	{"pacifist", PACIFIST_ROLE},
	{"priest", PRIEST_ROLE},
	{"prince", PRINCE_ROLE},
	{"seer", SEER_ROLE},
	{"spellcaster", SPELLCASTER_ROLE},
	{"toughguy", TOUGHGUY_ROLE},
	{"troublemaker", TROUBLEMAKER_ROLE},
	{"villager", VILLAGER_ROLE},
	{"witch", WITCH_ROLE},
	{"sorcerer", SORCERER_ROLE},
	{"minion", MINION_ROLE},
	{"cursed", CURSED_ROLE},
	{"doppelganger", DOPPELGANGER_ROLE},
	{"cultleader", CULTLEADER_ROLE},
	{"hoodlum", HOODLUM_ROLE},
	{"tanner", TANNER_ROLE}
};

void error_max()
{
#ifdef NICE
	system("clear");
#endif
	std::cout << "Maximum number already in game" << std::endl;
}

str get_input()
{
	str input;

	input = "";
	std::getline(std::cin, input);
	if (std::cin.eof())
	{
		std::cin.clear();
		exit(1);
	}
	if (input.empty())
		return "";
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
		return (number >= 1 && number <= 68);
	}
	catch (const std::exception&)
	{
		return false;
	}
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
		return (number >= 1 && number <= 68);
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
		return (getPlayerByIndex(number)->getLife());
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
		_diedInTheNight[i] = -1;
	for (int i = 0; i < 36; i++)
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
#ifdef NICE
		system("clear");
#endif
		std::cout << "Game is full. Resize to add more players" << std::endl;
		return ;
	}
	std::string lowerRole = role;
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
#ifdef NICE
			system("clear");
#endif
		}
	}
	else
	{
#ifdef NICE
		system("clear");
#endif
		std::cout << "Error: Invalid role '" << lowerRole << "'. Please use a valid role name." << std::endl;
	}
}

void Game::removePlayer(str role)
{
	std::string lowerRole = role;
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
#ifdef NICE
				system("clear");
#endif
				std::cout << lowerRole << " removed" << std::endl;
				return ;
			}
		}
	}
#ifdef NICE
	system("clear");
#endif
	std::cout << "Role " << lowerRole << " not in game" << std::endl;
}

void Game::nightPhase()
{
	int wolf = -1;
	std::cout << "Wake up the werewolves: ";
	for (int i = 0; i < _playerNo; i++)
	{
		if (_player[i]->getSide() == WEREWOLF && _player[i]->getLife() == ALIVE)
		{
			std::cout << _player[i]->getIndex() << " ";
			wolf = i + 1;
		}
	}
	std::cout << std::endl << std::endl << "Choose player to attack: ";
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
#ifdef NICE
	system("clear");
	printGameStatus();
#endif
	wakeAllActiveRoles();
}

void Game::firstNight()
{
	int seer;
	str input = "";
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i]->getRole() == SEER_ROLE)
			seer = i;
		else
		{
#ifdef NICE
			system("clear");
#endif
			std::cout << "Wake up " << _player[i]->getName() << std::endl;
			std::cout << "Enter player number: ";
			input = get_input();
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			_player[i]->setIndex(std::stoi(input));
		}
		_nightNo++;
	}
#ifdef NICE
	system("clear");
#endif
	std::cout << "Wake up seer" << std::endl;
	std::cout << "Enter player number: ";
	input = get_input();
	while (!isValidPlayerEntry(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input();
	}
	_player[seer]->setIndex(std::stoi(input));
	input = "";
	std::cout << "Player number to see: ";
	input = get_input();
	while (!isValidPlayerNumber(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input();
	}
	int res = _player[seer]->See(std::stoi(input));
	std::cout << "Player " << input << " is " << (res ? "a werewolf" : "not a werewolf") << std::endl;
	std::cout << "Press Enter to continue...";
	get_input();
#ifdef NICE
	system("clear");
	printGameStatus();
#endif

}

bool Game::checkWin()
{
	if (_villagerNo == _wolfNo && _vampNo == 0)
	{
		_wolfWin = true;
		std::cout << "WEREWOLVES WIN" << std::endl;
		return true;
	}
	else if (_wolfNo == 0 && _vampNo == 0)
	{
		_villageWin = true;
		std::cout << "VILLAGERS WIN" << std::endl;
		return true;
	}
	else if (_vampNo == _villagerNo && _wolfNo == 0)
	{
		_vampWin = true;
		std::cout << "VAMPIRES WIN" << std::endl;
		return true;
	}
	else if (_villagerNo == 0 && _wolfNo != 0 && _vampNo != 0)
	{
		_vampWin = true;
		_wolfWin = true;
		std::cout << "WEREWOLVES AND VAMPIRES WIN" << std::endl;
		return true;
	}
	return false;
}

void Game::setPlayerNo(int playerno)
{
	if (_playerNo == playerno)
	{
#ifdef NICE
		system("clear");
#endif
		std::cout << "Game already has " << playerno << " players" << std::endl;
		return ;
	}
	if (playerno < static_cast<int>(_player.size()))
	{
#ifdef NICE
		system("clear");
#endif
		std::cout << "Cannot make game smaller than current number of players (" << _player.size() << ")" << std::endl;
		return ;
	}
	_player.reserve(playerno);
	_playerNo = playerno;
#ifdef NICE
	system("clear");
#endif
}

int* Game::getNightlyDeaths()
{
	return _diedInTheNight;
}

void Game::setNightlyDeaths(int index)
{
	_diedInTheNight[_diedIndex] = index;
	_diedIndex++;
}

void Game::resetNightlyDeaths()
{
	for (int i = 0; i < 68; i++)
	{
		if (_diedInTheNight[i] == -1)
			continue;
		if (getPlayerByIndex(_diedInTheNight[i])->getSide() == WEREWOLF)
		{
			killWolf();
			getPlayerByIndex(_diedInTheNight[i])->setLife(DEAD);
		}
		else if (getPlayerByIndex(_diedInTheNight[i])->getSide() == VAMPIRE)
		{
			killVampire();
			getPlayerByIndex(_diedInTheNight[i])->setLife(DEAD);
		}
		else if (getPlayerByIndex(_diedInTheNight[i])->getRole() == CURSED_ROLE)
		{
			killVillager();
			_wolfNo++;
			getPlayerByIndex(_diedInTheNight[i])->setSide(WEREWOLF);
		}
		else
		{
			killVillager();
			getPlayerByIndex(_diedInTheNight[i])->setLife(DEAD);
		}
		_diedInTheNight[i] = -1;
	}
	_diedIndex = 0;
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
	return _balance;
}

int Game::getPlayerNo() const
{
	return _playerNo;
}

void Game::setWinStates(int wolf, int village, int vamp, int tanner, int lone, int hood, int cult)
{
	if (wolf == 1)
		_wolfWin = true;
	else if (wolf == 0)
		_wolfWin = false;
	if (village == 1)
		_villageWin = true;
	else if (village == 0)
		_villageWin = false;
	if (vamp == 1)
		_vampWin = true;
	else if (vamp == 0)
		_vampWin = false;
	if (tanner == 1)
		_tannerWin = true;
	else if (tanner == 0)
		_tannerWin = false;
	if (lone == 1)
		_loneWolfWin = true;
	else if (lone == 0)
		_loneWolfWin = false;
	if (hood == 1)
		_hoodlumWin = true;
	else if (hood == 0)
		_hoodlumWin = false;
	if (cult == 1)
		_cultWin = true;
	else if (cult == 0)
		_cultWin = false;
}

bool Game::tryStart()
{
	for (int i = 0; i < static_cast<int>(_player.size()); i++)
	{
		if (_player[i]->getSide() == VILLAGER)
			_villagerNo++;
		else if (_player[i]->getSide() == WEREWOLF)
			_wolfNo++;
		else
			_vampNo++;
	}
	if (static_cast<int>(_player.size()) != _playerNo)
	{
#ifdef NICE
		system("clear");
#endif
		std::cout << _playerNo - static_cast<int>(_player.size()) << " player(s) missing roles" << std::endl;
		return false;
	}
	else if ((_wolfNo == 0) && _vampNo == 0)
	{
#ifdef NICE
		system("clear");
#endif
		std::cout << "At least 1 Werewolf or Vampire required" << std::endl;
		return false;
	}
	else if (_whichRoles[SEER_ROLE] == false)
	{
#ifdef NICE
		system("clear");
#endif
		std::cout << "At least 1 Seer required" << std::endl;
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
	int i = -1;
#ifdef NICE
	system("clear");
	printGameStatus();
#endif
	std::cout << "DAY PHASE" << std::endl << "Wake up all players" << std::endl << std::endl;
	std::cout << "The following players died in the night: ";
	while (_diedInTheNight[++i] != -1)
	{
		if (getPlayerByIndex(_diedInTheNight[i])->getRole() != CURSED_ROLE)
			std::cout << _diedInTheNight[i] << " ";
	}
	std::cout << std::endl << std::endl;
	resetNightlyDeaths();
	if (checkWin())
		exit(0);
	std::cout << "Press enter to continue..." << std::endl;
	get_input();
#ifdef NICE
	system("clear");
	printGameStatus();
#endif
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
	if (index != -1)
		getPlayerByIndex(index)->beLynched();
	std::cout << "Press enter to contine..." << std::endl;
	get_input();
#ifdef NICE
	system("clear");
	printGameStatus();
#endif
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

ACard*	Game::getPlayerByName(str name)
{
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getName() == name)
			return _player[i];
	}
	return nullptr;
}

ACard*	Game::getPlayerByRole(int role)
{
	for (size_t i = 0; i < _player.size(); i++)
	{
		if (_player[i] && _player[i]->getRole() == role)
			return _player[i];
	}
	return nullptr;
}

bool Game::getGameMode() const
{
	return _revealCards;
}

void Game::wolfCubKilled()
{
	_secondWolfKill = true;
}

void Game::wakeAllActiveRoles()
{
	if (_whichRoles[APPRENTICESEER_ROLE])
	{
		if (getPlayerByRole(APPRENTICESEER_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Apprentice Seer" << std::endl << std::endl;
			if (getPlayerByRole(SEER_ROLE)->getLife() == DEAD)
			{
				std::cout << "The Apprentice Seer is now the Seer" << std::endl;
				_seerReplaced = true;
			}
			else
				std::cout << "The Apprentice Seer is NOT the Seer" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Apprentice Seer is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[AURASEER_ROLE])
	{
		if (getPlayerByRole(AURASEER_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Aura Seer" << std::endl << std::endl;
			std::cout << "Player number to see: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int res = getPlayerByRole(AURASEER_ROLE)->See(std::stoi(input));
			std::cout << "Player " << input << " has " << (res ? "a special role" : "no special role") << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Aura Seer is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[BODYGUARD_ROLE])
	{
		if (getPlayerByRole(BODYGUARD_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Bodyguard" << std::endl << std::endl;
			std::cout << "Player to protect: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			getPlayerByRole(BODYGUARD_ROLE)->Protect(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Bodyguard is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[HUNTER_ROLE])
	{
		if (getPlayerByRole(HUNTER_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Hunter" << std::endl << std::endl;
			std::cout << "Player to target if the Hunter dies: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			getPlayerByRole(HUNTER_ROLE)->setVictim(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Bodyguard is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[MAGICIAN_ROLE])
	{
		if (getPlayerByRole(MAGICIAN_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Magician" << std::endl << std::endl;
			if (getPlayerByRole(MAGICIAN_ROLE)->getSpellUsed("heal") == false)
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
				int num = std::stol(input);
				if (num != -1)
				{
					getPlayerByRole(MAGICIAN_ROLE)->Protect(num);
					getPlayerByRole(MAGICIAN_ROLE)->setSpellUsed("heal");
				}
			}
			else
				std::cout << "The Magician has used their heal spell. Call for it to conceal this fact" << std::endl;
			if (getPlayerByRole(MAGICIAN_ROLE)->getSpellUsed("kill") == false)
			{
				std::cout << "Player to kill (Enter -1 to not use heal): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stol(input);
				if (num != -1)
				{
					getPlayerByIndex(num)->beAttacked(getPlayerByRole(MAGICIAN_ROLE)->getIndex());
					getPlayerByRole(MAGICIAN_ROLE)->setSpellUsed("kill");
				}
			}
			else
				std::cout << "The Magician has used their kill spell. Call for it to conceal this fact" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Magician is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[OLDHAG_ROLE])
	{
		if (getPlayerByRole(OLDHAG_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Old Hag" << std::endl << std::endl;
			std::cout << "Player number to exile for the next day phase: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			getPlayerByRole(OLDHAG_ROLE)->Pox(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Old Hag is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[PI_ROLE])
	{
		if (getPlayerByRole(PI_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the PI" << std::endl << std::endl;
			if (getPlayerByRole(PI_ROLE)->getAbilityUsed() == false)
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
					int res = getPlayerByRole(PI_ROLE)->See(num);
					std::cout << "The player " << input << " or their neighbour is " << (res ? "a werewolf" : "not a werewolf") << std::endl;
				}
			}
			else
				std::cout << "The PI has used their ability. Call for them to conceal this fact" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The PI is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[PRIEST_ROLE])
	{
		if (getPlayerByRole(PRIEST_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Priest" << std::endl << std::endl;
			if (getPlayerByRole(PRIEST_ROLE)->getAbilityUsed() == false)
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
					getPlayerByRole(PRIEST_ROLE)->Protect(num);
			}
			else
				std::cout << "The Priest has used their ability. Call for them to conceal this fact" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Priest is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[SEER_ROLE])
	{
		if (getPlayerByRole(SEER_ROLE)->getLife() == ALIVE || (getPlayerByRole(SEER_ROLE)->getLife() == DEAD && _whichRoles[APPRENTICESEER_ROLE] && getPlayerByRole(APPRENTICESEER_ROLE)->getLife() == ALIVE))
		{
			std::cout << "Wake the Seer" << std::endl << std::endl;
			std::cout << "Player number to see: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int res = getPlayerByRole(SEER_ROLE)->See(std::stoi(input));
			std::cout << "Player " << input << " is " << (res ? "a werewolf" : "not a werewolf") << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Seer is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[SPELLCASTER_ROLE])
	{
		if (getPlayerByRole(SPELLCASTER_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Spellcaster" << std::endl << std::endl;
			std::cout << "Choose a player to silence" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Spellcaster is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[TROUBLEMAKER_ROLE])
	{
		if (getPlayerByRole(TROUBLEMAKER_ROLE)->getAbilityUsed() == false)
		{
			if (getPlayerByRole(TROUBLEMAKER_ROLE)->getLife() == ALIVE)
			{
				std::cout << "Wake the Troublemaker" << std::endl << std::endl;
				std::cout << "Ask if there will be two lynching the next day (1 for yes, 0 for no): " << std::endl;
				str input = get_input();
				if (input == "1")
				_secondLynching = true;
				getPlayerByRole(TROUBLEMAKER_ROLE)->setAbilityUsed();
			}
			else
			{
				if (_revealCards == false)
				std::cout << "The Troublemaker is dead. Call for them to conceal this fact" << std::endl;
			}
			std::cout << "Press Enter to continue...";
			get_input();
#ifdef NICE
			system("clear");
			printGameStatus();
#endif
		}
	}
if (_whichRoles[WITCH_ROLE])
	{
		if (getPlayerByRole(WITCH_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Witch" << std::endl << std::endl;
			if (getPlayerByRole(WITCH_ROLE)->getSpellUsed("heal") == false)
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
				int num = std::stol(input);
				if (num != -1)
				{
					getPlayerByRole(WITCH_ROLE)->Protect(num);
					getPlayerByRole(WITCH_ROLE)->setSpellUsed("heal");
				}
			}
			else
				std::cout << "The Witch has used their heal spell. Call for it to conceal this fact" << std::endl;
			if (getPlayerByRole(WITCH_ROLE)->getSpellUsed("kill") == false)
			{
				std::cout << "Player to kill (Enter -1 to not use heal): ";
				str input = get_input();
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input();
				}
				int num = std::stol(input);
				if (num != -1)
				{
					getPlayerByIndex(num)->beAttacked(getPlayerByRole(WITCH_ROLE)->getIndex());
					getPlayerByRole(WITCH_ROLE)->setSpellUsed("kill");
				}
			}
			else
				std::cout << "The Witch has used their kill spell. Call for it to conceal this fact" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Witch is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[SORCERER_ROLE])
	{
		if (getPlayerByRole(SORCERER_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Sorcerer" << std::endl << std::endl;
			std::cout << "Player number to see: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			int res = getPlayerByRole(SORCERER_ROLE)->SorcSee(std::stoi(input));
			std::cout << "Player " << input << " is " << (res ? "the Seer" : "not the Seer") << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Sorcerer is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[CURSED_ROLE])
	{
		if (getPlayerByRole(CURSED_ROLE)->getLife() == ALIVE)
		{
			bool turned = false;
			std::cout << "Wake the Cursed" << std::endl << std::endl;
			if (getPlayerByRole(CURSED_ROLE)->getSide() == VILLAGER)
			{
				std::cout << "The Cursed is ";
				int index = getPlayerByRole(CURSED_ROLE)->getIndex();
				for (int i = 0; i < 68; i++)
				{
					if (_diedInTheNight[i] == index)
					{
						turned = true;
						break;
					}
				}
				std::cout << (turned ? "now a werewolf" : "still a villager") << std::endl;
			}
			else
				std::cout << "The Cursed is already a werewolf. Call for them to conceal this fact" << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Cursed is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[DOPPELGANGER_ROLE])
	{
		if (getPlayerByRole(DOPPELGANGER_ROLE)->getLife() == ALIVE)
		{
			bool steal = false;
			int index = getPlayerByRole(DOPPELGANGER_ROLE)->getStolenIdentity()->getIndex();
			std::cout << "Wake the Doppelganger" << std::endl << std::endl;
			for (int i = 0; i < 68; i++)
			{
				if (_diedInTheNight[i] == index)
				{
					steal = true;
					break;
				}
			}
			std::cout << (steal ? "Their target is dead. Show the doppelganger their new role" : "Their target is alive") << std::endl;
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Doppelganger is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
	}
	if (_whichRoles[CULTLEADER_ROLE])
	{
		if (getPlayerByRole(CULTLEADER_ROLE)->getLife() == ALIVE)
		{
			std::cout << "Wake the Cult Leader" << std::endl << std::endl;
			std::cout << "Player to convert: ";
			str input = get_input();
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input();
			}
			getPlayerByRole(CULTLEADER_ROLE)->Convert(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
				std::cout << "The Cult Leader is dead. Call for them to conceal this fact" << std::endl;
		}
		std::cout << "Press Enter to continue...";
		get_input();
#ifdef NICE
		system("clear");
		printGameStatus();
#endif
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
		std::cout << "+" << std::endl;
		
	std::cout << "| " << std::setw(col1Width) << std::left << "Player No" << " | ";
	std::cout << std::setw(col2Width) << std::left << "Role" << " | ";
	std::cout << std::setw(col3Width) << std::left << "Status" << " | ";
	std::cout << std::setw(col4Width) << std::left << "Side" << " |" << std::endl;
		
	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col4Width + 2; i++) std::cout << "-";
		std::cout << "+" << std::endl;
		
	for (size_t i = 0; i < _player.size(); i++)
	{
		std::cout << "| " << std::setw(col1Width) << std::left << _player[i]->getIndex() << " | ";
		std::cout << std::setw(col2Width) << std::left << _player[i]->getName() << " | ";
		bool life = _player[i]->getLife();
		std::cout << (life ? GREEN : RED) << std::setw(col3Width) << std::left << (life ? "Alive" : "Dead") << RESET << " | ";
		
		int side = _player[i]->getSide();
		if (side == VILLAGER)
			std::cout << BLUE << std::setw(col4Width) << std::left << "Villager" << RESET << " |" << std::endl;
		else if (side == WEREWOLF)
			std::cout << YELLOW << std::setw(col4Width) << std::left << "Werewolf" << RESET << " |" << std::endl;
		else if (side == VAMPIRE)
			std::cout << PURPLE << std::setw(col4Width) << std::left << "Vampire" << RESET << " |" << std::endl;
	}
		
	std::cout << "+";
	for (int i = 0; i < col1Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col2Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col3Width + 2; i++) std::cout << "-";
		std::cout << "+";
	for (int i = 0; i < col4Width + 2; i++) std::cout << "-";
		std::cout << "+" << std::endl;

	std::cout << "Alive Villagers: (" << _villagerNo << ")" << std::endl;
	std::cout << "Alive Werewolves: (" << _wolfNo << ")" << std::endl;
	std::cout << "Alive Vampires: (" << _vampNo << ")" << std::endl;
	std::cout << "Total Alive Players: (" << _villagerNo + _wolfNo + _vampNo << "/" << _playerNo << ")" << std::endl << std::endl;
}