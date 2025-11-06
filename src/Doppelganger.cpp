#include "../inc/Roles.hpp"
#include "../inc/Game.hpp"

/// Doppelganger Native Functions

Doppelganger::Doppelganger(Game* game) : ACard(DOPPELGANGER_ROLE, "Doppelganger", VILLAGER, false, game, -2)
{
}

Doppelganger::~Doppelganger()
{
}
void Doppelganger::copy(int index)
{
	_copiedPlayer = index;
	ACard* copy = _game->getPlayerByIndex(index);
	if (copy->getRole() == MINION_ROLE || copy->getRole() == SORCERER_ROLE)
		_copiedSide = VILLAGER;
	else
		_copiedSide = copy->getSide();
}

int Doppelganger::getCopiedRole() const
{
	return _copiedRole;
}

int Doppelganger::getCopiedPlayer() const
{
	return _copiedPlayer;
}

void Doppelganger::setCopiedPlayer(int index)
{
	_copiedPlayer = index;
}

bool Doppelganger::getAbilityUsed(bool checkIfCopied) const
{
	if (checkIfCopied)
		return _abilityUsed;
	if (_abilityUsed)
		return _copiedAbilityUsed;
	else
		return _abilityUsed;
}

void Doppelganger::setAbilityUsed()
{
	if (_abilityUsed)
		_copiedAbilityUsed = true;
	else
		_abilityUsed = true;
}

int Doppelganger::getSide() const
{
	if (_abilityUsed == false)
		return _side;
	return _copiedSide;
}

/// Basic Function Overrides

void Doppelganger::beAttacked(int attacker)
{
	if (!_abilityUsed)
	{
		ACard::beAttacked(attacker);
		return;
	}
	switch (_copiedRole)
	{
		case HUNTER_ROLE:
			hunterBeAttacked(attacker);
			break;
		case TOUGHGUY_ROLE:
			toughguyBeAttacked(attacker);
			break;
		case CURSED_ROLE:
			cursedBeAttacked(attacker);
			break;
		case WEREWOLF_ROLE:
			werewolfBeAttacked(attacker);
			break;
		case WOLFCUB_ROLE:
			wolfcubBeAttacked(attacker);
			break;
		case LONEWOLF_ROLE:
			lonewolfBeAttacked(attacker);
			break;
		case VAMPIRE_ROLE:
			vampireBeAttacked(attacker);
			break;
		default:
			ACard::beAttacked(attacker);
	}
}

void Doppelganger::beLynched()
{
	if (!_abilityUsed)
	{
		ACard::beLynched();
		return;
	}
	switch (_copiedRole)
	{
		case HUNTER_ROLE:
			hunterBeLynched();
			break;
		case WOLFCUB_ROLE:
			wolfcubBeLynched();
			break;
		case PRINCE_ROLE:
			princeBeLynched();
			break;
		default:
			ACard::beLynched();
	}
}

void Doppelganger::setLife(bool alive)
{
	if (!_abilityUsed)
	{
		ACard::setLife(alive);
		return;
	}
	if (_copiedRole == HUNTER_ROLE)
		hunterSetLife(alive);
	else
		ACard::setLife(alive);
}

/// Role Specific Overrides

void Doppelganger::hunterBeAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF)
	{
		_game->setNightlyDeaths(_index);
	}
	else if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
}

void Doppelganger::hunterBeLynched()
{
	_alive = false;
	if (_side == WEREWOLF)
		_game->killWolf();
	else if (_side == VAMPIRE)
		_game->killVampire();
	else
		_game->killVillager();
	std::cout << "Player to die with the Hunter: ";
	str input = get_input(_game, false);
	while (!_game->isValidPlayerNumber(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input(_game, false);
	}
	_hunter_victim = std::stoi(input);
	_game->getPlayerByIndex(_hunter_victim)->beAttacked(_index);
	if (_game->getRoles()[CUPID_ROLE])
	{
		ACard* cupid = _game->getPlayerByRole(CUPID_ROLE);
		ACard* player1 = _game->getPlayerByIndex(cupid->getPlayer1());
		ACard* player2 = _game->getPlayerByIndex(cupid->getPlayer2());
		if (cupid->getPlayer1() == _index && player2->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
			player2->setLife(DEAD);
			_game->updateVillageNumbers(cupid->getPlayer2());
		}
		else if (cupid->getPlayer2() == _index && player1->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
			player1->setLife(DEAD);
			_game->updateVillageNumbers(cupid->getPlayer1());
		}
	}
}

void Doppelganger::hunterSetLife(bool alive)
{
	_alive = alive;
	if (alive == DEAD)
	{
		if (_hunter_victim == -1)
		{
			std::cout << "Enter Hunter's victim: ";
			str input = get_input(_game, false);
			while (!_game->isValidPlayerNumberAlt(input, _index))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(_game, false);
			}
			_hunter_victim = std::stoi(input);
		}
		takePlayerWith(_hunter_victim);
	}
}

void Doppelganger::toughguyBeAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getSide() == WEREWOLF)
		_copiedAbilityUsed = true;
	else if (attack->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (attack->getRole() == HUNTER_ROLE)
	{
		if (_game->getTimeOfDay() == NIGHT)
			_game->setNightlyDeaths(_index);
		else
		{
			_alive = false;
			_game->killVillager();
			if (_game->getRoles()[CUPID_ROLE])
			{
				ACard* cupid = _game->getPlayerByRole(CUPID_ROLE);
				ACard* player1 = _game->getPlayerByIndex(cupid->getPlayer1());
				ACard* player2 = _game->getPlayerByIndex(cupid->getPlayer2());
				if (cupid->getPlayer1() == _index && player2->getLife() == ALIVE)
				{
					std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
					player2->setLife(DEAD);
					_game->updateVillageNumbers(cupid->getPlayer2());
				}
				else if (cupid->getPlayer2() == _index && player1->getLife() == ALIVE)
				{
					std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
					player1->setLife(DEAD);
					_game->updateVillageNumbers(cupid->getPlayer1());
				}
			}
		}
	}
}

void Doppelganger::cursedBeAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (_side == VILLAGER)
	{
		if (attack->getSide() == WEREWOLF)
		{
			_game->setNightlyDeaths(_index);
			_abilityUsed = true;
		}
		else if (attack->getSide() == VAMPIRE)
			_game->setVampVictim(_index);
		else if (attack->getRole() == HUNTER_ROLE)
		{
			if (_game->getTimeOfDay() == NIGHT)
				_game->setNightlyDeaths(_index);
			else
			{
				_alive = false;
				_game->killVillager();
				if (_game->getRoles()[CUPID_ROLE])
				{
					ACard* cupid = _game->getPlayerByRole(CUPID_ROLE);
					ACard* player1 = _game->getPlayerByIndex(cupid->getPlayer1());
					ACard* player2 = _game->getPlayerByIndex(cupid->getPlayer2());
					if (cupid->getPlayer1() == _index && player2->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
						player2->setLife(DEAD);
						_game->updateVillageNumbers(cupid->getPlayer2());
					}
					else if (cupid->getPlayer2() == _index && player1->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
						player1->setLife(DEAD);
						_game->updateVillageNumbers(cupid->getPlayer1());
					}
				}
			}
		}
	}
	else if (_side == WEREWOLF)
	{
		if (attack->getSide() == VAMPIRE)
			_game->setVampVictim(_index);
		else if (attack->getRole() == HUNTER_ROLE)
		{
			if (_game->getTimeOfDay() == NIGHT)
				_game->setNightlyDeaths(_index);
			else
			{
				_alive = false;
				_game->killWolf();
				if (_game->getRoles()[CUPID_ROLE])
				{
					ACard* cupid = _game->getPlayerByRole(CUPID_ROLE);
					ACard* player1 = _game->getPlayerByIndex(cupid->getPlayer1());
					ACard* player2 = _game->getPlayerByIndex(cupid->getPlayer2());
					if (cupid->getPlayer1() == _index && player2->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
						player2->setLife(DEAD);
						_game->updateVillageNumbers(cupid->getPlayer2());
					}
					else if (cupid->getPlayer2() == _index && player1->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
						player1->setLife(DEAD);
						_game->updateVillageNumbers(cupid->getPlayer1());
					}
				}
			}
		}
	}
}

void Doppelganger::werewolfBeAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (attack->getRole() == HUNTER_ROLE)
	{
		if (_game->getTimeOfDay() == NIGHT)
			_game->setNightlyDeaths(_index);
		else
		{
			_alive = false;
			_game->killWolf();
		}
	}
}

void Doppelganger::wolfcubBeAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (attack->getRole() == HUNTER_ROLE)
	{
		if (_game->getTimeOfDay() == NIGHT)
			_game->setNightlyDeaths(_index);
		else
		{
			_alive = false;
			_game->killWolf();
			_game->wolfCubKilled();
		}
	}
}

void Doppelganger::wolfcubBeLynched()
{
	_alive = false;
	_game->killWolf();
	_game->wolfCubKilled();
	if (_game->getRoles()[CUPID_ROLE])
	{
		ACard* cupid = _game->getPlayerByRole(CUPID_ROLE);
		ACard* player1 = _game->getPlayerByIndex(cupid->getPlayer1());
		ACard* player2 = _game->getPlayerByIndex(cupid->getPlayer2());
		if (cupid->getPlayer1() == _index && player2->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
			player2->setLife(DEAD);
			_game->updateVillageNumbers(cupid->getPlayer2());
		}
		else if (cupid->getPlayer2() == _index && player1->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
			player1->setLife(DEAD);
			_game->updateVillageNumbers(cupid->getPlayer1());
		}
	}
}

void Doppelganger::lonewolfBeAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (attack->getRole() == HUNTER_ROLE)
	{
		if (_game->getTimeOfDay() == NIGHT)
			_game->setNightlyDeaths(_index);
		else
		{
			_alive = false;
			_game->killWolf();
		}
	}
}

void Doppelganger::vampireBeAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getRole() == HUNTER_ROLE)
	{
		if (_game->getTimeOfDay() == NIGHT)
			_game->setNightlyDeaths(_index);
		else
		{
			_alive = false;
			_game->killVampire();
		}
	}
}

void Doppelganger::princeBeLynched()
{
	if (_copiedAbilityUsed == true)
	{
		_game->killVillager();
		_alive = false;
		if (_game->getRoles()[CUPID_ROLE])
		{
			ACard* cupid = _game->getPlayerByRole(CUPID_ROLE);
			ACard* player1 = _game->getPlayerByIndex(cupid->getPlayer1());
			ACard* player2 = _game->getPlayerByIndex(cupid->getPlayer2());
			if (cupid->getPlayer1() == _index && player2->getLife() == ALIVE)
			{
				std::cout << "The Player's lover (" << cupid->getPlayer2() << ") has also died of a broken heart" << std::endl;
				player2->setLife(DEAD);
				_game->updateVillageNumbers(cupid->getPlayer2());
			}
			else if (cupid->getPlayer2() == _index && player1->getLife() == ALIVE)
			{
				std::cout << "The Player's lover (" << cupid->getPlayer1() << ") has also died of a broken heart" << std::endl;
				player1->setLife(DEAD);
				_game->updateVillageNumbers(cupid->getPlayer1());
			}
		}
	}
	else
		_copiedAbilityUsed = true;
}

/// Role Specific Functions

// Hunter methods
void Doppelganger::setVictim(int victim)
{
	_hunter_victim = victim;
}

int Doppelganger::getVictim() const
{
	return _hunter_victim;
}

void Doppelganger::takePlayerWith(int victim)
{
	_game->getPlayerByIndex(victim)->beAttacked(_index);
}

				
// Witch/Magician methods
bool Doppelganger::getSpellUsed(str spell) const
{
	if (spell == "heal")
		return _copiedHealUsed;
	else
		return _copiedKillUsed;
}

void Doppelganger::setSpellUsed(str spell)
{
	if (spell == "heal")
		_copiedHealUsed = true;
	else
		_copiedKillUsed = true;
}

				
// See methods
int Doppelganger::See(int index)
{
	if (_copiedRole == AURASEER_ROLE)
	{
		if (_game->getPlayerByIndex(index)->getName() == "Villager")
			return 0;
		else if (_game->getPlayerByIndex(index)->getName() == "Werewolf")
			return 0;
		else if (_game->getPlayerByIndex(index)->getName() == "Vampire")
			return 0;
		else
			return 1;
	}
	else if (_copiedRole == PI_ROLE)
	{
		if (_game->getPlayerByIndex(index)->getSide() == VAMPIRE || (_game->getPlayerByIndex(index)->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != MINION_ROLE))
			return 1;
		std::vector<ACard*>& players = _game->getPlayers();
		int targetPos = -1;
		for (size_t i = 0; i < players.size(); i++)
		{
			if (players[i] && players[i]->getIndex() == index)
			{
				targetPos = i;
				break;
			}
		}
		ACard* leftNeighbor = nullptr;
		for (int steps = 1; steps < (int)players.size(); steps++)
		{
			int pos = (targetPos - steps + players.size()) % players.size();
			if (players[pos] && players[pos]->getLife())
			{
				leftNeighbor = players[pos];
				break;
			}
		}
		ACard* rightNeighbor = nullptr;
		for (int steps = 1; steps < (int)players.size(); steps++)
		{
			int pos = (targetPos + steps) % players.size();
			if (players[pos] && players[pos]->getLife())
			{
				rightNeighbor = players[pos];
				break;
			}
		}
		if (leftNeighbor)
		{
			if ((leftNeighbor->getSide() == WEREWOLF && leftNeighbor->getRole() != MINION_ROLE) || leftNeighbor->getSide() == VAMPIRE)
				return 1;
		}
		if (rightNeighbor)
		{
			if ((rightNeighbor->getSide() == WEREWOLF && rightNeighbor->getRole() != MINION_ROLE) || leftNeighbor->getSide() == VAMPIRE)
				return 1;
		}
		return 0;
	}
	else if (_copiedRole == PRIEST_ROLE)
	{
		if (_game->getPlayerByIndex(index)->getRole() == MINION_ROLE)
			return 0;
		if (_game->getPlayerByIndex(index)->getRole() == LYCAN_ROLE || _game->getPlayerByIndex(index)->getSide() == VAMPIRE || _game->getPlayerByIndex(index)->getSide() == WEREWOLF)
			return 1;
		return 0;
	}
	else if (_copiedRole == SEER_ROLE)
	{
		if (_game->getPlayerByIndex(index)->getRole() == MINION_ROLE)
			return 0;
		if (_game->getPlayerByIndex(index)->getRole() == LYCAN_ROLE || _game->getPlayerByIndex(index)->getSide() == VAMPIRE || _game->getPlayerByIndex(index)->getSide() == WEREWOLF)
			return 1;
		return 0;
	}
	return -1;
}
			
// Sorcerer methods
int Doppelganger::SorcSee(int index)
{
	if (_game->getPlayerByIndex(index)->getName() == "Seer" || _game->getPlayerByIndex(index)->getName() == "Apprentice Seer")
		return 1;
	return 0;
}

				
// Protect methods
void Doppelganger::Protect(int index)
{
	if (_copiedRole == BODYGUARD_ROLE)
	{
		ACard* saved = _game->getPlayerByIndex(index);
		if (saved->getRole() == OLDMAN_ROLE)
		{
			if (saved->getAbilityUsed(false) == true)
				return ;
		}
		for (int i = 0; i < 68; i++)
		{
			if (_game->getNightlyDeaths()[i] == index)
				_game->getNightlyDeaths()[i] = -1;
		}
	}
	else if (_copiedRole == PRIEST_ROLE)
	{
		ACard* saved = _game->getPlayerByIndex(index);
		if (saved->getRole() == OLDMAN_ROLE)
		{
			if (saved->getAbilityUsed(false) == true)
				return ;
		}
		_game->setBlessedPlayer(index);
		_copiedAbilityUsed = true;
	}
}
		
// OldHag methods
void Doppelganger::Pox(int index)
{
	_game->getPlayerByIndex(index)->setInVillage(false);
}
		
// OldMan methods
void Doppelganger::Dies()
{
	if (_alive && _game->getCurrentNight() >= _game->getWereNo() + 1)
	{
		_copiedAbilityUsed = true;
		_game->setNightlyDeaths(_index);
	}
}
				
// CultLeader methods
void Doppelganger::Convert(int index)
{
	_game->getPlayerByIndex(index)->setInCult();
}

void Doppelganger::performAction(int index) // need to finish this
{
	if (_copiedRole == HUNTER_ROLE)
	{
		_hunter_victim = index;
	}
	else if (_copiedRole == CURSED_ROLE)
	{
		std::cout << "The Doppelganger is " << (_copiedAbilityUsed ? "a Werewolf" : "a Villager") << std::endl;
	}
	else if (_copiedRole == WITCH_ROLE)
	{
	}
	else if (_copiedRole == MAGICIAN_ROLE)
	{
	}
	else if (_copiedRole == SEER_ROLE)
	{
	}
	else if (_copiedRole == AURASEER_ROLE)
	{
	}
	else if (_copiedRole == SORCERER_ROLE)
	{
	}
	else if (_copiedRole == BODYGUARD_ROLE)
	{
	}
	else if (_copiedRole == PRIEST_ROLE)
	{
	}
	else if (_copiedRole == PI_ROLE)
	{
	}
	else if (_copiedRole == OLDHAG_ROLE)
	{
	}
	else if (_copiedRole == CULTLEADER_ROLE)
	{
	}
}
