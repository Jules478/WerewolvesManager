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
	str input = get_input();
	while (!_game->isValidPlayerNumber(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input();
	}
	_game->getPlayerByIndex(std::stoi(input))->beAttacked(_index);
	if (_game->getRoles()[CUPID_ROLE])
	{
		if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer1() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer2() << ") has also died of a broken heart" << std::endl;
			_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->setLife(DEAD);
			_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2());
		}
		else if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer2() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer1() << ") has also died of a broken heart" << std::endl;
			_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->setLife(DEAD);
			_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1());
		}
	}
}

void Doppelganger::hunterSetLife(bool alive)
{
	_alive = alive;
	if (alive == DEAD)
	{
		std::cout << "Enter Hunter's victim: ";
		str input = get_input();
		while (!_game->isValidPlayerNumber(input))
		{
			std::cout << "ERROR: Enter player number: ";
			input = get_input();
		}
		_game->getPlayerByRole(HUNTER_ROLE)->takePlayerWith(std::stoi(input));
	}
}

void Doppelganger::toughguyBeAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF)
		_copiedAbilityUsed = true;
	else if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
	{
		if (_game->getTimeOfDay() == NIGHT)
			_game->setNightlyDeaths(_index);
		else
		{
			_alive = false;
			_game->killVillager();
			if (_game->getRoles()[CUPID_ROLE])
			{
				if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer1() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->getLife() == ALIVE)
				{
					std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer2() << ") has also died of a broken heart" << std::endl;
					_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->setLife(DEAD);
					_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2());
				}
				else if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer2() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->getLife() == ALIVE)
				{
					std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer1() << ") has also died of a broken heart" << std::endl;
					_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->setLife(DEAD);
					_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1());
				}
			}
		}
	}
}

void Doppelganger::cursedBeAttacked(int attacker)
{
	if (_side == VILLAGER)
	{
		if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF)
			_game->setNightlyDeaths(_index);
		else if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
			_game->setVampVictim(_index);
		else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
		{
			if (_game->getTimeOfDay() == NIGHT)
				_game->setNightlyDeaths(_index);
			else
			{
				_alive = false;
				_game->killVillager();
				if (_game->getRoles()[CUPID_ROLE])
				{
					if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer1() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer2() << ") has also died of a broken heart" << std::endl;
						_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->setLife(DEAD);
						_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2());
					}
					else if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer2() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer1() << ") has also died of a broken heart" << std::endl;
						_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->setLife(DEAD);
						_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1());
					}
				}
			}
		}
	}
	else if (_side == WEREWOLF)
	{
		if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
			_game->setVampVictim(_index);
		else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
		{
			if (_game->getTimeOfDay() == NIGHT)
				_game->setNightlyDeaths(_index);
			else
			{
				_alive = false;
				_game->killWolf();
				if (_game->getRoles()[CUPID_ROLE])
				{
					if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer1() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer2() << ") has also died of a broken heart" << std::endl;
						_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->setLife(DEAD);
						_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2());
					}
					else if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer2() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->getLife() == ALIVE)
					{
						std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer1() << ") has also died of a broken heart" << std::endl;
						_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->setLife(DEAD);
						_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1());
					}
				}
			}
		}
	}
}

void Doppelganger::werewolfBeAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
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
	if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
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

void Doppelganger::wolfcubBeLynched()
{
	_alive = false;
	_game->killWolf();
	_game->wolfCubKilled();
	if (_game->getRoles()[CUPID_ROLE])
	{
		if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer1() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer2() << ") has also died of a broken heart" << std::endl;
			_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->setLife(DEAD);
			_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2());
		}
		else if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer2() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->getLife() == ALIVE)
		{
			std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer1() << ") has also died of a broken heart" << std::endl;
			_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->setLife(DEAD);
			_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1());
		}
	}
}

void Doppelganger::lonewolfBeAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
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
	if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
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
			if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer1() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->getLife() == ALIVE)
			{
				std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer2() << ") has also died of a broken heart" << std::endl;
				_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2())->setLife(DEAD);
				_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer2());
			}
			else if (_game->getPlayerByRole(CUPID_ROLE)->getPlayer2() == _index && _game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->getLife() == ALIVE)
			{
				std::cout << "The Player's lover (" << _game->getPlayerByRole(CUPID_ROLE)->getPlayer1() << ") has also died of a broken heart" << std::endl;
				_game->getPlayerByIndex(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1())->setLife(DEAD);
				_game->updateVillageNumbers(_game->getPlayerByRole(CUPID_ROLE)->getPlayer1());
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
		if (_game->getPlayerByIndex(index)->getRole() == OLDMAN_ROLE)
		{
			if (_game->getPlayerByIndex(index)->getAbilityUsed(false) == true)
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
		if (_game->getPlayerByIndex(index)->getRole() == OLDMAN_ROLE)
		{
			if (_game->getPlayerByIndex(index)->getAbilityUsed(false) == true)
				return ;
		}
		int i = -1;
		while (_game->getNightlyDeaths()[++i] != -1)
		{
			if (_game->getNightlyDeaths()[i] == index)
				_game->getNightlyDeaths()[i] = -1;
		}
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
