#include "../inc/Roles.hpp"
#include "../inc/Game.hpp"

Werewolf::Werewolf(Game* game) : ACard(WEREWOLF_ROLE, "Werewolf", WEREWOLF, true, game, -6)
{
}

Werewolf::~Werewolf()
{
}


void Werewolf::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
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
			_game->killWolf();
		}
	}
}

WolfCub::WolfCub(Game* game) : ACard(WOLFCUB_ROLE, "Wolf Cub", WEREWOLF, true, game, -8)
{
}

WolfCub::~WolfCub()
{
}


void WolfCub::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
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
			_game->killWolf();
		}
	}
}

void WolfCub::beLynched()
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

LoneWolf::LoneWolf(Game* game) : ACard(LONEWOLF_ROLE, "Lone Wolf", WEREWOLF, true, game, -5)
{
}

LoneWolf::~LoneWolf()
{
}


void LoneWolf::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
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
			_game->killWolf();
		}
	}
}

Vampire::Vampire(Game* game) : ACard(VAMPIRE_ROLE, "Vampire", VAMPIRE, true, game, -8)
{
}

Vampire::~Vampire()
{
}

void Vampire::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (_game->getPlayerByIndex(attacker)->getRole() == HUNTER_ROLE)
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

ApprenticeSeer::ApprenticeSeer(Game* game) : ACard(APPRENTICESEER_ROLE, "Apprentice Seer", VILLAGER, true, game, 4)
{
}

ApprenticeSeer::~ApprenticeSeer()
{
}

AuraSeer::AuraSeer(Game* game) : ACard(AURASEER_ROLE, "Aura Seer", VILLAGER, true, game, 3)
{
}

AuraSeer::~AuraSeer()
{
}

int AuraSeer::See(int index)
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


Bodyguard::Bodyguard(Game* game) : ACard(BODYGUARD_ROLE, "Bodyguard", VILLAGER, true, game, 3)
{
}

Bodyguard::~Bodyguard()
{
}

void Bodyguard::Protect(int index)
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

Cupid::Cupid(Game* game) : ACard(CUPID_ROLE, "Cupid", VILLAGER, false, game, -3)
{
}

Cupid::~Cupid()
{
}

void Cupid::setPlayer1(int index)
{
	_player1 = index;
}

void Cupid::setPlayer2(int index)
{
	_player2 = index;
}

int Cupid::getPlayer1()
{
	return _player1;
}

int Cupid::getPlayer2()
{
	return _player2;
}

Diseased::Diseased(Game* game) : ACard(DISEASED_ROLE, "Diseased", VILLAGER, false, game, 3)
{
}

Diseased::~Diseased()
{
}

Ghost::Ghost(Game* game) : ACard(GHOST_ROLE, "Ghost", VILLAGER, false, game, 2)
{
}

Ghost::~Ghost()
{
}

Hunter::Hunter(Game* game) : ACard(HUNTER_ROLE, "Hunter", VILLAGER, true, game, 3)
{
}

Hunter::~Hunter()
{
}

void Hunter::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF || _game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
}

void Hunter::beLynched()
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

void Hunter::setVictim(int victim)
{
	_victim = victim;
}

int Hunter::getVictim() const
{
	return _victim;
}

void Hunter::takePlayerWith(int victim)
{
	_game->getPlayerByIndex(victim)->beAttacked(_index);
}

void Hunter::setLife(bool alive)
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

Idiot::Idiot(Game* game) : ACard(IDIOT_ROLE, "Idiot", VILLAGER, false, game, 2)
{
}

Idiot::~Idiot()
{
}

Lycan::Lycan(Game* game) : ACard(LYCAN_ROLE, "Lycan", VILLAGER, false, game, -1)
{
}

Lycan::~Lycan()
{
}

Magician::Magician(Game* game) : ACard(MAGICIAN_ROLE, "Magician", VILLAGER, true, game, 4)
{
}

Magician::~Magician()
{
}

bool Magician::getSpellUsed(str spell) const
{
	if (spell == "heal")
		return _healUsed;
	else
		return _killUsed;
}

void Magician::setSpellUsed(str spell)
{
	if (spell == "heal")
		_healUsed = true;
	else
		_killUsed = true;
}

void Magician::Protect(int index)
{
	_healUsed = true;
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

Martyr::Martyr(Game* game) : ACard(MARTYR_ROLE, "Martyr", VILLAGER, false, game, 3)
{
}

Martyr::~Martyr()
{
}

bool Martyr::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _abilityUsed;
}

void Martyr::setAbilityUsed()
{
	_abilityUsed = true;
}

Mason::Mason(Game* game) : ACard(MASON_ROLE, "Mason", VILLAGER, false, game, 2)
{
}

Mason::~Mason()
{
}

Mayor::Mayor(Game* game) : ACard(MAYOR_ROLE, "Mayor", VILLAGER, false, game, 2)
{
}

Mayor::~Mayor()
{
}

OldHag::OldHag(Game* game) : ACard(OLDHAG_ROLE, "Old Hag", VILLAGER, false, game, 1)
{
}

OldHag::~OldHag()
{
}
void OldHag::Pox(int index)
{
	_game->getPlayerByIndex(index)->setInVillage(false);
}

OldMan::OldMan(Game* game) : ACard(OLDMAN_ROLE, "Old Man", VILLAGER, false, game, 0)
{
}

OldMan::~OldMan()
{
}

void OldMan::Dies()
{
	if (_alive && _game->getCurrentNight() >= _game->getWereNo() + 1)
	{
		_diesOldAge = true;
		_game->setNightlyDeaths(_index);
	}
}

bool OldMan::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _diesOldAge;
}

PI::PI(Game* game) : ACard(PI_ROLE, "PI", VILLAGER, true, game, 3)
{
}

PI::~PI()
{
}

/*int PI::See(int index)
{
	if (_game->getPlayerByIndex(index)->getSide() == VAMPIRE || (_game->getPlayerByIndex(index)->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != SORCERER_ROLE && _game->getPlayerByIndex(index)->getRole() != MINION_ROLE))
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
	ACard* leftNeighbour = nullptr;
	for (int steps = 1; steps < (int)players.size(); steps++)
	{
		int pos = (targetPos - steps + players.size()) % players.size();
		if (players[pos] && players[pos]->getLife() == ALIVE)
		{
			leftNeighbour = players[pos];
			break;
		}
	}
	ACard* rightNeighbour = nullptr;
	for (int steps = 1; steps < (int)players.size(); steps++)
	{
		int pos = (targetPos + steps) % players.size();
		if (players[pos] && players[pos]->getLife() == ALIVE)
		{
			rightNeighbour = players[pos];
			break;
		}
	}
	if (leftNeighbour)
	{
		if ((leftNeighbour->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != SORCERER_ROLE && leftNeighbour->getRole() != MINION_ROLE) || leftNeighbour->getSide() == VAMPIRE)
			return 1;
	}
	if (rightNeighbour)
	{
		if ((rightNeighbour->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != SORCERER_ROLE && rightNeighbour->getRole() != MINION_ROLE) || leftNeighbour->getSide() == VAMPIRE)
			return 1;
	}
	return 0;
}*/

int PI::See(int index)
{
	_abilityUsed = true;
	if (_game->getPlayerByIndex(index)->getSide() == VAMPIRE || (_game->getPlayerByIndex(index)->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != SORCERER_ROLE && _game->getPlayerByIndex(index)->getRole() != MINION_ROLE))
		return 1;
	std::vector<ACard*>& players = _game->getPlayers();
	ACard* leftNeighbour = nullptr;
	int neighbour = index;
	int max = static_cast<int>(players.size());
	while (--neighbour > 0)
	{
		if (_game->getPlayerByIndex(neighbour)->getLife() == ALIVE)
		{
			leftNeighbour = _game->getPlayerByIndex(neighbour);
			break;
		}
		if (neighbour == 1)
			neighbour = max;
	}
	ACard* rightNeighbour = nullptr;
	neighbour = index;
	while (++neighbour <= max)
	{
		if (_game->getPlayerByIndex(neighbour)->getLife() == ALIVE)
		{
			rightNeighbour = _game->getPlayerByIndex(neighbour);
			break;
		}
		if (neighbour == max)
			neighbour = 0;
	}
	if (leftNeighbour)
	{
		if (leftNeighbour->getRole() == LYCAN_ROLE || (leftNeighbour->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != SORCERER_ROLE && leftNeighbour->getRole() != MINION_ROLE) || leftNeighbour->getSide() == VAMPIRE)
			return 1;
	}
	if (rightNeighbour)
	{
		if (rightNeighbour->getRole() == LYCAN_ROLE || (rightNeighbour->getSide() == WEREWOLF && _game->getPlayerByIndex(index)->getRole() != SORCERER_ROLE && rightNeighbour->getRole() != MINION_ROLE) || leftNeighbour->getSide() == VAMPIRE)
			return 1;
	}
	return 0;
}

bool PI::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _abilityUsed;
}

Pacifist::Pacifist(Game* game) : ACard(PACIFIST_ROLE, "Pacifist", VILLAGER, false, game, -2)
{
}

Pacifist::~Pacifist()
{
}

Priest::Priest(Game* game) : ACard(PRIEST_ROLE, "Priest", VILLAGER, true, game, 3)
{
}

Priest::~Priest()
{
}
void Priest::Protect(int index)
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
	_abilityUsed = true;
}

int Priest::See(int index)
{
	if (_game->getPlayerByIndex(index)->getRole() == MINION_ROLE)
		return 0;
	if (_game->getPlayerByIndex(index)->getRole() == LYCAN_ROLE || _game->getPlayerByIndex(index)->getSide() == VAMPIRE || _game->getPlayerByIndex(index)->getSide() == WEREWOLF)
		return 1;
	return 0;
}

bool Priest::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _abilityUsed;
}

Prince::Prince(Game* game) : ACard(PRINCE_ROLE, "Prince", VILLAGER, false, game, 3)
{
}

Prince::~Prince()
{
}

void Prince::beLynched()
{
	if (_abilityUsed == true)
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
		_abilityUsed = true;
}

bool Prince::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _abilityUsed;
}

Seer::Seer(Game* game) : ACard(SEER_ROLE, "Seer", VILLAGER, true, game, 7)
{
}

Seer::~Seer()
{
}

int Seer::See(int index)
{
	if (_game->getPlayerByIndex(index)->getRole() == MINION_ROLE)
		return 0;
	if (_game->getPlayerByIndex(index)->getRole() == LYCAN_ROLE || _game->getPlayerByIndex(index)->getSide() == VAMPIRE || _game->getPlayerByIndex(index)->getSide() == WEREWOLF)
		return 1;
	return 0;
}

Spellcaster::Spellcaster(Game* game) : ACard(SPELLCASTER_ROLE, "Spellcaster", VILLAGER, true, game, 1)
{
}

Spellcaster::~Spellcaster()
{
}

ToughGuy::ToughGuy(Game* game) : ACard(TOUGHGUY_ROLE, "Tough Guy", VILLAGER, false, game, 3)
{
}

ToughGuy::~ToughGuy()
{
}

void ToughGuy::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF)
		_goingToDie = true;
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

bool ToughGuy::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _goingToDie;
}

TroubleMaker::TroubleMaker(Game* game) : ACard(TROUBLEMAKER_ROLE, "Troublemaker", VILLAGER, true, game, 2)
{
}

TroubleMaker::~TroubleMaker()
{
}

void TroubleMaker::setAbilityUsed()
{
	_abilityUsed = true;
}

bool TroubleMaker::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _abilityUsed;
}

Villager::Villager(Game* game) : ACard(VILLAGER_ROLE, "Villager", VILLAGER, false, game, 1)
{
}

Villager::~Villager()
{
}

Witch::Witch(Game* game) : ACard(WITCH_ROLE, "Witch", VILLAGER, true, game, 4)
{
}

Witch::~Witch()
{
}

bool Witch::getSpellUsed(str spell) const
{
	if (spell == "heal")
		return _healUsed;
	else
		return _killUsed;
}

void Witch::setSpellUsed(str spell)
{
	if (spell == "heal")
		_healUsed = true;
	else
		_killUsed = true;
}

void Witch::Protect(int index)
{
	_healUsed = true;
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

Sorcerer::Sorcerer(Game* game) : ACard(SORCERER_ROLE, "Sorcerer", WEREWOLF, true, game, -3)
{
}

Sorcerer::~Sorcerer()
{
}
int Sorcerer::SorcSee(int index)
{
	if (_game->getPlayerByIndex(index)->getName() == "Seer" || _game->getPlayerByIndex(index)->getName() == "Apprentice Seer")
		return 1;
	return 0;
}

Minion::Minion(Game* game) : ACard(MINION_ROLE, "Minion", WEREWOLF, false, game, -6)
{
}

Minion::~Minion()
{
}

Cursed::Cursed(Game* game) : ACard(CURSED_ROLE, "Cursed", VILLAGER, false, game, -3)
{
}

Cursed::~Cursed()
{
}

void Cursed::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getRole() == WITCH_ROLE || _game->getPlayerByIndex(attacker)->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (_side == VILLAGER)
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

CultLeader::CultLeader(Game* game) : ACard(CULTLEADER_ROLE, "Cult Leader", VILLAGER, true, game, 1)
{
	_inCult = true;
}

CultLeader::~CultLeader()
{
}

void CultLeader::Convert(int index)
{
	_game->getPlayerByIndex(index)->setInCult();
}

Hoodlum::Hoodlum(Game* game) : ACard(HOODLUM_ROLE, "Hoodlum", VILLAGER, false, game, 0)
{
}

Hoodlum::~Hoodlum()
{
}
void Hoodlum::Mischief(int index1, int index2)
{
	_player1 = index1;
	_player2 = index2;
}

int Hoodlum::getPlayer1()
{
	return _player1;
}

int Hoodlum::getPlayer2()
{
	return _player2;
}

void Hoodlum::setPlayer1(int index)
{
	_player1 = index;
}

void Hoodlum::setPlayer2(int index)
{
	_player2 = index;
}

Tanner::Tanner(Game* game) : ACard(TANNER_ROLE, "Tanner", VILLAGER, false, game, 1)
{
}

Tanner::~Tanner()
{
}
