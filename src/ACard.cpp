#include "../inc/ACard.hpp"
#include "../inc/Game.hpp"

ACard::ACard(t_roles role, str name, int side, bool wakes, Game *game, int value) : _role(role), _name(name), _side(side), _wakes(wakes), _game(game), _value(value)
{
}

ACard::~ACard()
{
}

int ACard::getIndex() const
{
	return _index;
}

bool ACard::getLife() const
{
	return _alive;
}

bool ACard::getWakes() const
{
	return _wakes;
}

void ACard::setIndex(int index)
{
	_index = index;
}

void ACard::setSide(int side)
{
	_side = side;
}

void ACard::setLife(bool alive)
{
	_alive = alive;
}

t_roles ACard::getRole() const
{
	return _role;
}

void ACard::setRole(t_roles role)
{
	_role = role;
}

str ACard::getName() const
{
	return _name;
}

void ACard::beAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getSide() == WEREWOLF || attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
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
			if (_side == WEREWOLF)
				_game->killWolf();
			else if (_side == VAMPIRE)
				_game->killVampire();
			else
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

void ACard::beLynched()
{
	_alive = false;
	if (_side == WEREWOLF && _role != MINION_ROLE && _role != SORCERER_ROLE)
		_game->killWolf();
	else if (_side == VAMPIRE)
		_game->killVampire();
	else
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

bool ACard::getInVillage() const
{
	return _inVillage;
}

void ACard::setInVillage(bool exile)
{
	_inVillage = exile;
}

int ACard::getValue() const
{
	return _value;
}

void ACard::setInCult()
{
	_inCult = true;
}

void ACard::setDrunk()
{
	_isDrunk = !_isDrunk;
}

bool ACard::getDrunk() const
{
	return _isDrunk;
}

bool ACard::getInCult() const
{
	return _inCult;
}