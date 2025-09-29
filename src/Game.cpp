#include "../inc/Game.hpp"

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
					get_input(this, true);
				}
				else
				{
					if (_revealCards == false)
					{
						std::cout << "The Drunk is already dead. Call for the Drunk to conceal this fact" << std::endl;
						std::cout << "\n\n" << "Press enter to continue..." << std::endl;
						get_input(this, true);
					}
				}
				_drunkRole = -1;
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
		if ((_drunkRole == WEREWOLF_ROLE || _drunkRole == WOLFCUB_ROLE || _drunkRole == LONEWOLF_ROLE ) && _wolfNo == 1)
		{
			std::cout << "The Werewolf is drunk. Call for them to conceal this fact" << std::endl;
			std::cout << "\nPress enter to continue..." << std::endl;
			get_input(this, true);
			clearScreen();
			printGameStatus();
		}
		else if (_wolfUpsetTummy == false)
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
				str input = get_input(this, false);
				while (!isValidAlivePlayer(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
					str input = get_input(this, false);
					while (!isValidAlivePlayer(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input(this, false);
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
			get_input(this, true);
			clearScreen();
			printGameStatus();
		}
	}
	_wolfUpsetTummy = false;
	_secondWolfKill = false;
	int vamp = -1;
	if (_vampNo > 0)
	{
		if (_drunkRole == VAMPIRE_ROLE && _vampNo == 1)
		{
			std::cout << "The Vampire is drunk. Call for them to conceal this fact" << std::endl;
			std::cout << "\nPress enter to continue..." << std::endl;
			get_input(this, true);
			clearScreen();
			printGameStatus();
		}
		else
		{
			std::cout << "Wake up the vampires: \n";
			for (int i = 0; i < _playerNo; i++)
			{
				if (_player[i]->getSide() == VAMPIRE && _player[i]->getDrunk() == false && _player[i]->getLife() == ALIVE)
				{
					vamp = _player[i]->getIndex();
					std::cout <<_player[i]->getName() << " (" << vamp << ") \n";
				}
			}
			if (vamp != -1)
			{
				std::cout << "\n\n" << "Choose player to attack: ";
				str input = get_input(this, false);
				while (!isValidAlivePlayer(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
				}
				getPlayerByIndex(std::stoi(input))->beAttacked(vamp);
			}
			clearScreen();
			printGameStatus();
		}
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
		str input = get_input(this, false);
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter role number: ";
			input = get_input(this, false);
		}
		int index = std::stoi(input) - 1;
		_player[index]->setDrunk();
		_drunkRole = _player[index]->getRole();
		clearScreen();
		printGameStatus();
		std::cout << "Wake up the Drunk" << std::endl;
		std::cout << "Enter player number: ";
		input = get_input(this, false);
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input(this, false);
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
			get_input(this, true);
		}
		else
		{
			std::cout << "Wake up the Wolf Cub" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input(this, false);
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
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
			get_input(this, true);
		}
		else
		{
			std::cout << "Wake up the Lone Wolf" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input(this, false);
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
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
		for (size_t i = 0; i < _player.size(); i++)
		{
			if ((_drunkRole == WEREWOLF_ROLE || _drunkRole == WOLFCUB_ROLE || _drunkRole == LONEWOLF_ROLE ) && _wolfNo == 1)
			{
				std::cout << "A Werewolf is drunk. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input(this, true);
				break;
			}
			else
			{
				if (!_player[i]->getDrunk())
				{
					clearScreen();
					printGameStatus();
					std::cout << "Wake up all the Werewolves" << std::endl;
					if (_player[i]->getRole() == WEREWOLF_ROLE)
					{
						std::cout << "Enter player number: ";
						input = get_input(this, false);
						while (!isValidPlayerEntry(input))
						{
							std::cout << "ERROR: Enter player number: ";
							input = get_input(this, false);
						}
						int index = std::stoi(input);
						_player[i]->setIndex(index);
						_assignedPlayers[_assignedIndex++] = index;
					}
				}
			}
		}
		if (_whichRoles[MINION_ROLE])
		{
			if (_drunkRole == MINION_ROLE)
			{
				std::cout << "The Minion is drunk. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input(this, true);
			}
			else
			{
				std::cout << "Wake up the Minion" << std::endl;
				std::cout << "Enter player number: ";
				input = get_input(this, false);
				while (!isValidPlayerEntry(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
				get_input(this, true);
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Wake up the Vampires" << std::endl;
				if (_player[i]->getRole() == VAMPIRE_ROLE)
				{
					std::cout << "Enter player number: ";
					input = get_input(this, false);
					while (!isValidPlayerEntry(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input(this, false);
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
				get_input(this, true);
			}
			else
			{
				clearScreen();
				printGameStatus();
				std::cout << "Wake up the Masons" << std::endl;
				if (_player[i]->getRole() == MASON_ROLE)
				{
					std::cout << "Enter player number: ";
					input = get_input(this, false);
					while (!isValidPlayerEntry(input))
					{
						std::cout << "ERROR: Enter player number: ";
						input = get_input(this, false);
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
			get_input(this, true);
		}
		else
		{
			ACard* hoodlum = getPlayerByRole(HOODLUM_ROLE);
			std::cout << "Wake up the Hoodlum" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input(this, false);
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			int index = std::stoi(input);
			hoodlum->setIndex(index);
			_assignedPlayers[_assignedIndex++] = index;
			clearScreen();
			printGameStatus();
			std::cout << "Which players does the Hoodlum want to be dead by the end of the Game?" << std::endl;
			std::cout << "Enter first player: ";
			input = get_input(this, false);
			while (!isValidPlayerNumberAlt(input, hoodlum->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			hoodlum->setPlayer1(std::stoi(input));
			clearScreen();
			printGameStatus();
			std::cout << "Which players does the Hoodlum want to be dead by the end of the Game?" << std::endl;
			std::cout << "Enter second player: ";
			input = get_input(this, false);
			while (!isValidPlayerNumberAlt(input, hoodlum->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
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
				get_input(this, true);
			}
			else
			{
				std::cout << "Wake up " << _player[i]->getName() << std::endl;
				std::cout << "Enter player number: ";
				input = get_input(this, false);
				while (!isValidPlayerEntry(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
			get_input(this, true);
		}
		else
		{
			ACard* cupid = getPlayerByRole(CUPID_ROLE);
			std::cout << "Wake up Cupid" << std::endl;
			std::cout << "Enter player number: ";
			input = get_input(this, false);
			while (!isValidPlayerEntry(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			int index = std::stoi(input);
			cupid->setIndex(index);
			_assignedPlayers[_assignedIndex++] = index;
			clearScreen();
			printGameStatus();
			std::cout << "Which players does Cupid want to fall in love?" << std::endl;
			std::cout << "Enter first player: ";
			input = get_input(this, false);
			while (!isValidPlayerNumberAlt(input, cupid->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			cupid->setPlayer1(std::stoi(input));
			clearScreen();
			printGameStatus();
			std::cout << "Which players does Cupid want to fall in love?" << std::endl;
			std::cout << "Enter second player: ";
			input = get_input(this, false);
			while (!isValidPlayerNumberAlt(input, cupid->getIndex()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			cupid->setPlayer2(std::stoi(input));
			clearScreen();
			printGameStatus();
			std::cout << "Wake up the Lovers (" << cupid->getPlayer1() << " & " << cupid->getPlayer2() << ")" << std::endl;
			std::cout << "\nPress Enter to continue..." << std::endl;
			get_input(this, true);
		}
	}
	clearScreen();
	printGameStatus();
	if (_whichRoles[DOPPELGANGER_ROLE])
	{
		ACard* dopp = getPlayerByRole(DOPPELGANGER_ROLE);
		std::cout << "Wake up the Doppelganger" << std::endl;
		std::cout << "Enter player number: ";
		input = get_input(this, false);
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input(this, false);
		}
		int index = std::stoi(input);
		dopp->setIndex(index);
		_assignedPlayers[_assignedIndex++] = index;
		clearScreen();
		printGameStatus();
		std::cout << "Which player does the Doppelganger wish to mirror?: ";
		input = get_input(this, false);
		while (!isValidPlayerNumberAlt(input, dopp->getIndex()))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input(this, false);
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
	input = get_input(this, false);
	while (!isValidPlayerEntry(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input(this, false);
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
		input = get_input(this, false);
		while (!isValidPlayerEntry(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input(this, false);
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
	input = get_input(this, false);
	while (!isValidPlayerNumber(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input(this, false);
	}
	int res = _player[seer1]->See(std::stoi(input));
	std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
	std::cout << "\n\n" << "Press Enter to continue...";
	get_input(this, true);
	clearScreen();
	printGameStatus();
	if (seer2 != -1)
	{
		input = "";
		std::cout << "Wake up Male Seer" << std::endl;
		std::cout << "Player number to see: ";
		input = get_input(this, false);
		while (!isValidPlayerNumber(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input(this, false);
		}
		int res = _player[seer2]->See(std::stoi(input));
		std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
		std::cout << "\n\n" << "Press Enter to continue...";
		get_input(this, true);
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
	get_input(this, true);
	setTimeOfDay();
	_nightNo++;
	clearScreen();
	printGameStatus();
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
				displayDeath(dead->getIndex(), false);
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
	get_input(this, true);
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
				get_input(this, true);
				break ;
			}
		}
	}
	while (1)
	{
		if (_secondLynching)
			std::cout << "The Troublemaker has called for two lynchings today" << std::endl;
		std::cout << "Enter index of lynched player (if no player was lynched enter -1): ";
		str input = get_input(this, false);
		while (!isValidAlivePlayer(input))
		{
			if (input == "-1")
				break;
			std::cout << "ERROR: Enter index: ";
			input = get_input(this, false);
		}
		int index = std::stoi(input);
		ACard *lynch = getPlayerByIndex(index);
		if (index != -1)
		{
			if (_vampireVictim != -1 && getPlayerByIndex(_vampireVictim)->getLife() == ALIVE)
			{
				if (_vampireVictim == _blessedPlayer)
					_blessedPlayer = -1;
				else
				{
					ACard *vamp = getPlayerByIndex(_vampireVictim);
					if (vamp->getRole() == HUNTER_ROLE)
					std::cout << "The Hunter has died to the Vampires. ";
					vamp->setLife(DEAD);
					if (vamp->getRole() == WOLFCUB_ROLE)
					wolfCubKilled();
					std::cout << "\nThe Vampires have killed ";
					displayDeath(_vampireVictim, false);
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
				}
				if (_vampireVictim == index)
				{
					_vampireVictim = -1;
					continue;
				}
				_vampireVictim = -1;
			}
			std::cout << "Enter number of votes for lynching: ";
			input = get_input(this, false);
			while (!isValidVoteNumber(input))
			{
				std::cout << "ERROR: Enter vote count: ";
				input = get_input(this, false);
			}
			int votes = std::stoi(input);
			if (_whichRoles[MAYOR_ROLE])
			{
				ACard* mayor = getPlayerByRole(MAYOR_ROLE);
				if (mayor->getLife() == ALIVE)
				{
					std::cout << "Did the Mayor (" << mayor->getIndex() << ") vote for the lynching? (y/n): ";
					input = get_input(this, false);
					while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
					{
						std::cout << "ERROR: Enter vote: ";
						input = get_input(this, false);
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
						input = get_input(this, false);
						while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
						{
							std::cout << "ERROR: Enter vote: ";
							input = get_input(this, false);
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
							get_input(this, true);
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
					displayDeath(lynch->getIndex(), true);
				}
				lynch->beLynched();
				if (lynch->getRole() == HUNTER_ROLE)
						displayDeath(lynch->getVictim(), true);
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
				get_input(this, true);
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

/**
 * This is for all roles that need to wake up.
 * 
 * Exceptions being Werewolves, Vampires, and Drunk (if applicable)
 */
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
			get_input(this, true);
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Apprentice Seer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press enter to continue..." << std::endl;
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			int res = aura->See(std::stoi(input));
			std::cout << "Player " << input << " has " << (res ? "a special role" : "no special role") << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input(this, true);
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Aura Seer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumberAlt(input, bodyg->getPlayer1()))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
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
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			hunter->setVictim(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Hunter is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
				get_input(this, true);
			}
			clearScreen();
			printGameStatus();
			std::cout << "Wake the Magician (" << magi->getIndex() << ")\n" << std::endl;
			if (magi->getSpellUsed("kill") == false)
			{
				std::cout << "Player to kill (Enter -1 to not use kill): ";
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
				get_input(this, true);
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Magician is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			hag->Pox(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Old Hag is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
				}
				int num = std::stoi(input);
				if (num != -1)
				{
					int res = pi->See(num);
					std::cout << "Player " << input << (res ? " or their neighbour is NOT a Villager" : " and their neighbours are Villagers") << std::endl;
					std::cout << "\n\n" << "Press Enter to continue...";
					get_input(this, true);
				}
			}
			else
			{
				std::cout << "The PI has used their ability. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The PI is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
				}
				int num = std::stoi(input);
				if (num != -1)
					priest->Protect(num);
			}
			else
			{
				std::cout << "The Priest has used their ability. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Priest is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			int res = seer->See(std::stoi(input));
			std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input(this, true);
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The" << (_howManyRoles[SEER_ROLE] == 2 ? " Female" : "") << " Seer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
				}
				int res = seer->See(std::stoi(input));
				std::cout << "Player " << input << " is " << (res ? "NOT a Villager" : "a Villager") << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
			}
			else
			{
				if (_revealCards == false)
				{
					std::cout << "The Male Seer is dead. Call for them to conceal this fact" << std::endl;
					std::cout << "\n\n" << "Press Enter to continue...";
					get_input(this, true);
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
			get_input(this, true);
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
				str input = get_input(this, false);
				while ((input != "y" && input != "Y") && (input != "n" && input != "N"))
				{
					std::cout << "ERROR: Enter choice: ";
					input = get_input(this, false);
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
				get_input(this, true);
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
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
				get_input(this, true);
			}
			clearScreen();
			printGameStatus();
			std::cout << "Wake the Witch (" << witch->getIndex() << ")\n" << std::endl;
			if (witch->getSpellUsed("kill") == false)
			{
				std::cout << "Player to kill (Enter -1 to not use kill): ";
				str input = get_input(this, false);
				while (!isValidPlayerNumber(input))
				{
					if (input == "-1")
						break;
					std::cout << "ERROR: Enter player number: ";
					input = get_input(this, false);
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
				get_input(this, true);
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Witch is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			int res = sorc->SorcSee(std::stoi(input));
			std::cout << "Player " << input << " is " << (res ? "the Seer" : "not the Seer") << std::endl;
			std::cout << "\n\n" << "Press Enter to continue...";
			get_input(this, true);
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Sorcerer is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
				get_input(this, true);
			}
			else
			{
				std::cout << "The Cursed is already a werewolf. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Cursed is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
				get_input(this, true);
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
				get_input(this, true);
			}
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Doppelganger is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
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
			str input = get_input(this, false);
			while (!isValidPlayerNumber(input))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(this, false);
			}
			cult->Convert(std::stoi(input));
		}
		else
		{
			if (_revealCards == false)
			{
				std::cout << "The Cult Leader is dead. Call for them to conceal this fact" << std::endl;
				std::cout << "\n\n" << "Press Enter to continue...";
				get_input(this, true);
			}
		}
		clearScreen();
		printGameStatus();
	}
	if (_whichRoles[GHOST_ROLE] || (_altGhostRule && _villagerNo + _wolfNo + _vampNo < _playerNo))
	{
		std::cout << "Ask the Ghost for the letter they wish to give to the Village" << std::endl;
		std::cout << "\n\n" << "Press Enter to continue...";
		get_input(this, true);
		clearScreen();
		printGameStatus();
	}
}
