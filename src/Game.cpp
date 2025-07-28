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

Game::Game(int playerno) : _playerNo(playerno), _nightNo(0)
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
	}
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
	std::cout << "Player " << input << " is " << (res ? "is a werewolf" : "not a werewolf") << std::endl;
	std::cout << "FIRST NIGHT OVER" << std::endl;
}

void Game::checkWin()
{
	if (_wolfWin == true)
		std::cout << "WEREWOLVES WIN" << std::endl;
	else if (_villageWin == true)
		std::cout << "VILLAGERS WIN" << std::endl;
	else if (_vampWin == true)
		std::cout << "VAMPIRES WIN" << std::endl;
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
		_diedInTheNight[i] = -1;
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

int Game::getCurrentNight() const
{
	return _nightNo;
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
