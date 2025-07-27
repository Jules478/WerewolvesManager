#include "../inc/Roles.hpp"
#include "../inc/Game.hpp"

Werewolf::Werewolf(Game* game) : ACard(WEREWOLF_ROLE, "Werewolf", WEREWOLF, true, game)
{
}

Werewolf::~Werewolf()
{
}


void Werewolf::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE_ROLE)
		_game->setVampVictim(_index);
}

WolfCub::WolfCub(Game* game) : ACard(WOLFCUB_ROLE, "Wolfcub", WEREWOLF, true, game)
{
}

WolfCub::~WolfCub()
{
}


void WolfCub::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE_ROLE)
		_game->setVampVictim(_index);
}

LoneWolf::LoneWolf(Game* game) : ACard(LONEWOLF_ROLE, "Lonewolf", WEREWOLF, true, game)
{
}

LoneWolf::~LoneWolf()
{
}


void LoneWolf::beAttacked(int attacker)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE_ROLE)
		_game->setVampVictim(_index);
}

Vampire::Vampire(Game* game) : ACard(VAMPIRE_ROLE, "Vampire", VAMPIRE, true, game)
{
}

Vampire::~Vampire()
{
}

void Vampire::beAttacked(int attacker)
{
	(void)attacker;
}

ApprenticeSeer::ApprenticeSeer(Game* game) : ACard(APPRENTICESEER_ROLE, "Apprentice seer", VILLAGER, true, game)
{
}

ApprenticeSeer::~ApprenticeSeer()
{
}

void ApprenticeSeer::bePromoted()
{
}

int ApprenticeSeer::See(int index)
{
}


AuraSeer::AuraSeer(Game* game) : ACard(AURASEER_ROLE, "Aura seer", VILLAGER, true, game)
{
}

AuraSeer::~AuraSeer()
{
}

int AuraSeer::See(int index)
{
	if (_game->getPlayerByIndex(index)->getName() = "Villager")
		return 0;
	else if (_game->getPlayerByIndex(index)->getName() = "Werewolf")
		return 0;
	else if (_game->getPlayerByIndex(index)->getName() = "Vampire")
		return 0;
	else
		return 1;
}


Bodyguard::Bodyguard(Game* game) : ACard(BODYGUARD_ROLE, "Bodyguard", VILLAGER, true, game)
{
}

Bodyguard::~Bodyguard()
{
}

void Bodyguard::Protect(int index)
{
	int i = -1;
	while (_game->getNightlyDeaths[++i] != -1)
	{
		if (_game->getNightlyDeaths[i] == index)
			_game->getNightlyDeaths[i] = -1;
	}
}

Cupid::Cupid(Game* game) : ACard(CUPID_ROLE, "Cupid", VILLAGER, false, game)
{
}

Cupid::~Cupid()
{
}

void Cupid::Love(int index1, int index2)
{
}


Diseased::Diseased(Game* game) : ACard(DISEASED_ROLE, "Diseased", VILLAGER, false, game)
{
}

Diseased::~Diseased()
{
}

Ghost::Ghost(Game* game) : ACard(GHOST_ROLE, "Ghost", VILLAGER, false, game)
{
}

Ghost::~Ghost()
{
}

Hunter::Hunter(Game* game) : ACard(HUNTER_ROLE, "Hunter", VILLAGER, true, game)
{
}

Hunter::~Hunter()
{
}

void Hunter::beAttacked(int attacker, int victim)
{
	if (_game->getPlayerByIndex(attacker)->getSide() == WEREWOLF_ROLE)
		_game->setNightlyDeaths(_index);
	else if (_game->getPlayerByIndex(attacker)->getSide() == VAMPIRE_ROLE)
		_game->setVampVictim(_index);
	_game->getPlayerByIndex(victim)->beAttacked(_index);
}

void Hunter::beLynched()
{
}

Idiot::Idiot(Game* game) : ACard(IDIOT_ROLE, "Idiot", VILLAGER, false, game)
{
}

Idiot::~Idiot()
{
}

Lycan::Lycan(Game* game) : ACard(LYCAN_ROLE, "Lycan", VILLAGER, false, game)
{
}

Lycan::~Lycan()
{
}

Magician::Magician(Game* game) : ACard(MAGICIAN_ROLE, "Magician", VILLAGER, true, game)
{
}

Magician::~Magician()
{
}

Martyr::Martyr(Game* game) : ACard(MARTYR_ROLE, "Martyr", VILLAGER, false, game)
{
}

Martyr::~Martyr()
{
}

Mason::Mason(Game* game) : ACard(MASON_ROLE, "Mason", VILLAGER, false, game)
{
}

Mason::~Mason()
{
}

Mayor::Mayor(Game* game) : ACard(MAYOR_ROLE, "Mayor", VILLAGER, false, game)
{
}

Mayor::~Mayor()
{
}

OldHag::OldHag(Game* game) : ACard(OLDHAG_ROLE, "Old Hag", VILLAGER, false, game)
{
}

OldHag::~OldHag()
{
}
void OldHag::Pox(int index)
{
}

OldMan::OldMan(Game* game) : ACard(OLDMAN_ROLE, "Old Man", VILLAGER, false, game)
{
}

OldMan::~OldMan()
{
}
void OldMan::Dies(int round)
{
}

PI::PI(Game* game) : ACard(PI_ROLE, "PI", VILLAGER, true, game)
{
}

PI::~PI()
{
}
int PI::See(int index)
{
}

Pacifist::Pacifist(Game* game) : ACard(PACIFIST_ROLE, "Pacifist", VILLAGER, false, game)
{
}

Pacifist::~Pacifist()
{
}

Priest::Priest(Game* game) : ACard(PRIEST_ROLE, "Priest", VILLAGER, true, game)
{
}

Priest::~Priest()
{
}
void Priest::Protect(int index)
{
}

int Priest::See(int index)
{
}

Prince::Prince(Game* game) : ACard(PRINCE_ROLE, "Prince", VILLAGER, false, game)
{
}

Prince::~Prince()
{
}

Seer::Seer(Game* game) : ACard(SEER_ROLE, "Seer", VILLAGER, true, game)
{
}

Seer::~Seer()
{
}

int Seer::See(int index)
{
}

Spellcaster::Spellcaster(Game* game) : ACard(SPELLCASTER_ROLE, "Spellcaster", VILLAGER, true, game)
{
}

Spellcaster::~Spellcaster()
{
}

ToughGuy::ToughGuy(Game* game) : ACard(TOUGHGUY_ROLE, "Tough Guy", VILLAGER, false, game)
{
}

ToughGuy::~ToughGuy()
{
}

TroubleMaker::TroubleMaker(Game* game) : ACard(TROUBLEMAKER_ROLE, "Troublemaker", VILLAGER, true, game)
{
}

TroubleMaker::~TroubleMaker()
{
}

Villager::Villager(Game* game) : ACard(VILLAGER_ROLE, "Villager", VILLAGER, false, game)
{
}

Villager::~Villager()
{
}

Witch::Witch(Game* game) : ACard(WITCH_ROLE, "WITCH", VILLAGER, true, game)
{
}

Witch::~Witch()
{
}

Sorcerer::Sorcerer(Game* game) : ACard(SORCERER_ROLE, "Sorcerer", WEREWOLF, true, game)
{
}

Sorcerer::~Sorcerer()
{
}
int Sorcerer::SorcSee(int index)
{
}

Minion::Minion(Game* game) : ACard(MINION_ROLE, "Minion", WEREWOLF, false, game)
{
}

Minion::~Minion()
{
}

Cursed::Cursed(Game* game) : ACard(CURSED_ROLE, "Cursed", VILLAGER, false, game)
{
}

Cursed::~Cursed()
{
}

Doppelganger::Doppelganger(Game* game) : ACard(DOPPELGANGER_ROLE, "Doppelganger", VILLAGER, false, game)
{
}

Doppelganger::~Doppelganger()
{
}
void Doppelganger::Steal(int index)
{
}

Drunk::Drunk(Game* game) : ACard(DRUNK_ROLE, "Drunk", VILLAGER, false, game)
{
}

Drunk::~Drunk()
{
}

CultLeader::CultLeader(Game* game) : ACard(CULTLEADER_ROLE, "Cult Leader", VILLAGER, true, game)
{
}

CultLeader::~CultLeader()
{
}

void CultLeader::Convert(int index)
{
}

Hoodlum::Hoodlum(Game* game) : ACard(HOODLUM_ROLE, "Hoodlum", VILLAGER, false, game)
{
}

Hoodlum::~Hoodlum()
{
}
void Hoodlum::Mischief(int index1, int index2)
{
}

Tanner::Tanner(Game* game) : ACard(TANNER_ROLE, "Tanner", VILLAGER, false, game)
{
}

Tanner::~Tanner()
{
}
