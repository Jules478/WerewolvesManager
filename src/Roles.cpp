#include "../inc/Roles.hpp"
#include "../inc/Game.hpp"

Werewolf::Werewolf(Game* game) : ACard(WEREWOLF_ROLE, "Werewolf", WEREWOLF, true, game, -6)
{
}

Werewolf::~Werewolf()
{
}

/**
 * Has no handling for being attacked by wolf
 * Intended behaviour for debugging purposes
 */
void Werewolf::beAttacked(int attacker)
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

WolfCub::WolfCub(Game* game) : ACard(WOLFCUB_ROLE, "Wolf Cub", WEREWOLF, true, game, -8)
{
}

WolfCub::~WolfCub()
{
}

/**
 * Has no handling for being attacked by wolf
 * Intended behaviour for debugging purposes
 */
void WolfCub::beAttacked(int attacker)
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

/**
 * Sets flag for two wolf attacks
 */
void WolfCub::beLynched()
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

LoneWolf::LoneWolf(Game* game) : ACard(LONEWOLF_ROLE, "Lone Wolf", WEREWOLF, true, game, -5)
{
}

LoneWolf::~LoneWolf()
{
}

/**
 * Has no handling for being attacked by wolf
 * Intended behaviour for debugging purposes
 */
void LoneWolf::beAttacked(int attacker)
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

Vampire::Vampire(Game* game) : ACard(VAMPIRE_ROLE, "Vampire", VAMPIRE, true, game, -8)
{
}

Vampire::~Vampire()
{
}

/**
 * Cannot be attacked by Werewolf
 */
void Vampire::beAttacked(int attacker)
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

/**
 * Aura Seer only checks if player has special role
 * 
 * @param index Index of player to be seen
 * 
 * @returns 1 on special role, 0 on basic
 */
int AuraSeer::See(int index)
{
	ACard* seen = _game->getPlayerByIndex(index);
	if (seen->getName() == "Villager")
		return 0;
	else if (seen->getName() == "Werewolf")
		return 0;
	else if (seen->getName() == "Vampire")
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

/**
 * Searches death array for given player and removes them
 */
void Bodyguard::Protect(int index)
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

/**
 * Used to prevent same player being protected twice consecutively
 */
void Bodyguard::setPlayer1(int index)
{
	_lastProtect = index;
}

int Bodyguard::getPlayer1()
{
	return _lastProtect;
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
	_victim = -1;
}

Hunter::~Hunter()
{
}

void Hunter::beAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getSide() == WEREWOLF || attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getSide() == VAMPIRE)
		_game->setVampVictim(_index);
}

/**
 * Handles Hunter being able to kill another player when lynched
 */
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
	str input = get_input(_game, false);
	while (!_game->isValidPlayerNumber(input))
	{
		std::cout << "ERROR: Enter player number: ";
		input = get_input(_game, false);
	}
	_victim = std::stoi(input);
	_game->getPlayerByIndex(_victim)->beAttacked(_index);
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
		if (_victim == -1)
		{
			std::cout << "Enter Hunter's victim: ";
			str input = get_input(_game, false);
			while (!_game->isValidPlayerNumberAlt(input, _index))
			{
				std::cout << "ERROR: Enter player number: ";
				input = get_input(_game, false);
			}
			_victim = std::stoi(input);
		}
		takePlayerWith(_victim);
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

/**
 * Check if Magician abilities are used
 * 
 * @param spell if "heal" is passed then heal spell is checked, otherwise kill spell is checked
 */
bool Magician::getSpellUsed(str spell) const
{
	if (spell == "heal")
		return _healUsed;
	else
		return _killUsed;
}

/**
 * Sets Magician abilities as used
 * 
 * @param spell if "heal" is passed then heal spell used, otherwise kill spell is used
 */
void Magician::setSpellUsed(str spell)
{
	if (spell == "heal")
		_healUsed = true;
	else
		_killUsed = true;
}

/**
 * Removes given player from the death array
 * If player is Old Man it will check whether they're dying naturally or attacked
 */
void Magician::Protect(int index)
{
	ACard* saved = _game->getPlayerByIndex(index);
	_healUsed = true;
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

/**
 * Old Man should die on night X where X = number of werewolves + 1
 * If condition is met then death will be set
 */
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

/**
 * If selected player is a villager then neighbours will be checked
 * Will cycle through neighbours until a living neighbour is found. Player list wraps around
 */
int PI::See(int index)
{
	ACard* seen = _game->getPlayerByIndex(index);
	_abilityUsed = true;
	if (seen->getSide() == VAMPIRE || (seen->getSide() == WEREWOLF && seen->getRole() != SORCERER_ROLE && seen->getRole() != MINION_ROLE))
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
		if (leftNeighbour->getRole() == LYCAN_ROLE || (leftNeighbour->getSide() == WEREWOLF && leftNeighbour->getRole() != SORCERER_ROLE && leftNeighbour->getRole() != MINION_ROLE) || leftNeighbour->getSide() == VAMPIRE)
			return 1;
	}
	if (rightNeighbour)
	{
		if (rightNeighbour->getRole() == LYCAN_ROLE || (rightNeighbour->getSide() == WEREWOLF && rightNeighbour->getRole() != SORCERER_ROLE && rightNeighbour->getRole() != MINION_ROLE) || rightNeighbour->getSide() == VAMPIRE)
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

/**
 * Removes player from death array
 */
void Priest::Protect(int index)
{
	ACard* saved = _game->getPlayerByIndex(index);
	if (saved->getRole() == OLDMAN_ROLE)
	{
		if (saved->getAbilityUsed(false) == true)
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

/**
 * Checks given player
 * 
 * @returns 0 for villager, 1 for non villager
 */
int Priest::See(int index)
{
	ACard* seen = _game->getPlayerByIndex(index);
	if (seen->getRole() == MINION_ROLE)
		return 0;
	if (seen->getRole() == LYCAN_ROLE || seen->getSide() == VAMPIRE || seen->getSide() == WEREWOLF)
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

/**
 * If first lynching of Prince then role will be revealed and will not die
 */
void Prince::beLynched()
{
	if (_abilityUsed == true)
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

/**
 * Checks given player
 * 
 * @returns 0 for villager, 1 for non villager
 */
int Seer::See(int index)
{
	ACard* seen = _game->getPlayerByIndex(index);
	if (seen->getRole() == MINION_ROLE || seen->getRole() == SORCERER_ROLE)
		return 0;
	if (seen->getRole() == LYCAN_ROLE || seen->getSide() == VAMPIRE || seen->getSide() == WEREWOLF)
		return 1;
	return 0;
}

bool Seer::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _secondSeer;
}

void Seer::setAbilityUsed()
{
	_secondSeer = !_secondSeer;
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

/**
 * Same logic as Villager but if attacked by wolves death does not occur immediately
 * Flag set that Tough Guy will die the following night
 */
void ToughGuy::beAttacked(int attacker)
{
	ACard* attack = _game->getPlayerByIndex(attacker);
	if (attack->getRole() == WITCH_ROLE || attack->getRole() == MAGICIAN_ROLE)
		_game->setNightlyDeaths(_index);
	else if (attack->getSide() == WEREWOLF)
		_goingToDie = true;
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
	ACard* saved = _game->getPlayerByIndex(index);
	_healUsed = true;
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

Sorcerer::Sorcerer(Game* game) : ACard(SORCERER_ROLE, "Sorcerer", WEREWOLF, true, game, -3)
{
}

Sorcerer::~Sorcerer()
{
}

/**
 * Checks given player
 * 
 * @returns 1 for Seer or Apprentice Seer, 0 for everyone else
 */
int Sorcerer::SorcSee(int index)
{
	ACard* seen = _game->getPlayerByIndex(index);
	if (seen->getName() == "Seer" || seen->getName() == "Apprentice Seer")
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

/**
 * If Cursed is villager then logic the same as Villager unless attacked by wolf
 * If wolf attacks then Cursed switches sides
 * 
 * If Cursed is werewolf then logic the same except no handling for wolf attack
 */
void Cursed::beAttacked(int attacker)
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

bool Cursed::getAbilityUsed(bool checkIfCopied) const
{
	(void)checkIfCopied;
	return _abilityUsed;
}

void Cursed::setAbilityUsed()
{
	_abilityUsed = !_abilityUsed;
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
