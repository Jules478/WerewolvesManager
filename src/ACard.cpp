#include "../inc/ACard.hpp"
#include "../inc/Game.hpp"

ACard::ACard(t_roles role, str name, int side, bool wakes, Game* game) : _role(role), _name(name), _side(side), _wakes(wakes), _game(game)
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
	if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF_ROLE)
		_game->setNightlyDeaths(_index);
}

void ACard::beLynched()
{
	_alive = false;
}
