#include "../inc/ACard.hpp"
#include "../inc/Game.hpp"

ACard::ACard(t_roles role, str name, int side, bool wakes, Game *game, int value) : _role(role), _name(name), _side(side), _wakes(wakes), _game(game), _value(value)
{
}

ACard::~ACard()
{
}

int ACard::getSide() const
{
	return _side;
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
	if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF)
	{
		_game->setNightlyDeaths(_index);
	}
	else if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
	else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
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
		}
	}
}

void ACard::beLynched()
{
	_alive = false;
	if (_side == WEREWOLF)
		_game->killWolf();
	else if (_side == VAMPIRE)
		_game->killVampire();
	else
		_game->killVillager();
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