#include "../inc/Game.hpp"

static std::map<str, t_roles> roleLookup = 
{
	{"werewolf", WEREWOLF_ROLE},
	{"wolfcub", WOLFCUB_ROLE},
	{"lonewolf", LONEWOLF_ROLE},
	{"vampire", VAMPIRE_ROLE},
	{"apprenticeseer", APPRENTICESEER_ROLE},
	{"auraseer", AURASEER_ROLE},
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
	{"drunk", DRUNK_ROLE},
	{"cultleader", CULTLEADER_ROLE},
	{"hoodlum", HOODLUM_ROLE},
	{"tanner", TANNER_ROLE}
};

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
}

Game::~Game()
{
	for (size_t i = 0; i < _player.size(); i++)
		delete _player[i];
}

void Game::addPlayer(str role)
{
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
				newPlayer = new Werewolf(this);
				break;
			case WOLFCUB_ROLE:
				newPlayer = new WolfCub();
				break;
			case LONEWOLF_ROLE:
				newPlayer = new LoneWolf();
				break;
			case VAMPIRE_ROLE:
				newPlayer = new Vampire();
				break;
			case APPRENTICESEER_ROLE:
				newPlayer = new ApprenticeSeer();
				break;
			case AURASEER_ROLE:
				newPlayer = new AuraSeer();
				break;
			case BODYGUARD_ROLE:
				newPlayer = new Bodyguard();
				break;
			case CUPID_ROLE:
				newPlayer = new Cupid();
				break;
			case DISEASED_ROLE:
				newPlayer = new Diseased();
				break;
			case GHOST_ROLE:
				newPlayer = new Ghost();
				break;
			case HUNTER_ROLE:
				newPlayer = new Hunter();
				break;
			case IDIOT_ROLE:
				newPlayer = new Idiot();
				break;
			case LYCAN_ROLE:
				newPlayer = new Lycan();
				break;
			case MAGICIAN_ROLE:
				newPlayer = new Magician();
				break;
			case MARTYR_ROLE:
				newPlayer = new Martyr();
				break;
			case MASON_ROLE:
				newPlayer = new Mason();
				break;
			case MAYOR_ROLE:
				newPlayer = new Mayor();
				break;
			case OLDHAG_ROLE:
				newPlayer = new OldHag();
				break;
			case OLDMAN_ROLE:
				newPlayer = new OldMan();
				break;
			case PI_ROLE:
				newPlayer = new PI();
				break;
			case PACIFIST_ROLE:
				newPlayer = new Pacifist();
				break;
			case PRIEST_ROLE:
				newPlayer = new Priest();
				break;
			case PRINCE_ROLE:
				newPlayer = new Prince();
				break;
			case SEER_ROLE:
				newPlayer = new Seer();
				break;
			case SPELLCASTER_ROLE:
				newPlayer = new Spellcaster();
				break;
			case TOUGHGUY_ROLE:
				newPlayer = new ToughGuy();
				break;
			case TROUBLEMAKER_ROLE:
				newPlayer = new TroubleMaker();
				break;
			case VILLAGER_ROLE:
				newPlayer = new Villager();
				break;
			case WITCH_ROLE:
				newPlayer = new Witch();
				break;
			case SORCERER_ROLE:
				newPlayer = new Sorcerer();
				break;
			case MINION_ROLE:
				newPlayer = new Minion();
				break;
			case CURSED_ROLE:
				newPlayer = new Cursed();
				break;
			case DOPPELGANGER_ROLE:
				newPlayer = new Doppelganger();
				break;
			case DRUNK_ROLE:
				newPlayer = new Drunk();
				break;
			case CULTLEADER_ROLE:
				newPlayer = new CultLeader();
				break;
			case HOODLUM_ROLE:
				newPlayer = new Hoodlum();
				break;
			case TANNER_ROLE:
				newPlayer = new Tanner();
				break;
			default:
				break;
		}		
		if (newPlayer)
		{
			 _player.push_back(newPlayer);
			 std::cout << "Player added successfully!" << std::endl;
		}
	}
	else
	{
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
				delete _player[i];
				_player.erase(_player.begin() + i);
				return ;
			}
		}
	}
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
		std::cout << "Game already has " << playerno << " players" << std::endl;
		return ;
	}
	if (playerno < _player.size())
	{
		std::cout << "Cannot make game smaller than current number of players" << std::endl;
		return ;
	}
	_player.reserve(playerno);
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