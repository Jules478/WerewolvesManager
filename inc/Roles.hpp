#pragma once

#include "ACard.hpp"

class Game;

class Werewolf : public ACard
{
	public:
			Werewolf(Game* game);
			~Werewolf();

			void beAttacked(int attacker);
			void beLynched();
};

class WolfCub : public ACard
{
	public:
			WolfCub(Game* game);
			~WolfCub();

			void beAttacked(int attacker);
			void beLynched();

};

class LoneWolf : public ACard
{
	public:
			LoneWolf(Game* game);
			~LoneWolf();

			void beAttacked(int attacker);
			void beLynched();

};

class Vampire : public ACard
{
	public:
			Vampire(Game* game);
			~Vampire();

			void beAttacked(int attacker);
			void beLynched();

};

class ApprenticeSeer : public ACard
{
	public:
			ApprenticeSeer(Game* game);
			~ApprenticeSeer();

			void beAttacked(int attacker);
			void beLynched();
			void bePromoted();
			int See(int index);

};

class AuraSeer : public ACard
{
	public:
			AuraSeer(Game* game);
			~AuraSeer();

			void beAttacked(int attacker);
			void beLynched();
			int See(int index);
};

class Bodyguard : public ACard
{
	public:
			Bodyguard(Game* game);
			~Bodyguard();

			void beAttacked(int attacker);
			void beLynched();
			void Protect(int index);

};

class Cupid : public ACard
{
	public:
			Cupid(Game* game);
			~Cupid();

			void beAttacked(int attacker);
			void beLynched();
			void Love(int index1, int index2);

};

class Diseased : public ACard
{
	public:
			Diseased(Game* game);
			~Diseased();

			void beAttacked(int attacker);
			void beLynched();

};

class Ghost : public ACard
{
	public:
			Ghost(Game* game);
			~Ghost();

			void beAttacked(int attacker);
			void beLynched();

};

class Hunter : public ACard
{
	public:
			Hunter(Game* game);
			~Hunter();

			void beAttacked(int attacker);
			void beLynched();

};

class Idiot : public ACard
{
	public:
			Idiot(Game* game);
			~Idiot();

			void beAttacked(int attacker);
			void beLynched();

};

class Lycan : public ACard
{
	public:
			Lycan(Game* game);
			~Lycan();

			void beAttacked(int attacker);
			void beLynched();

};

class Magician : public ACard
{
	public:
			Magician(Game* game);
			~Magician();

			void beAttacked(int attacker);
			void beLynched();

};

class Martyr : public ACard
{
	public:
			Martyr(Game* game);
			~Martyr();

			void beAttacked(int attacker);
			void beLynched();

};

class Mason : public ACard
{
	public:
			Mason(Game* game);
			~Mason();

			void beAttacked(int attacker);
			void beLynched();

};

class Mayor : public ACard
{
	public:
			Mayor(Game* game);
			~Mayor();

			void beAttacked(int attacker);
			void beLynched();

};

class OldHag : public ACard
{
	public:
			OldHag(Game* game);
			~OldHag();

			void beAttacked(int attacker);
			void beLynched();
			void Pox(int index);

};

class OldMan : public ACard
{
	public:
			OldMan(Game* game);
			~OldMan();

			void beAttacked(int attacker);
			void beLynched();
			void Dies(int round);

};

class PI : public ACard
{
	public:
			PI(Game* game);
			~PI();

			void beAttacked(int attacker);
			void beLynched();
			int See(int index);

};

class Pacifist : public ACard
{
	public:
			Pacifist(Game* game);
			~Pacifist();

			void beAttacked(int attacker);
			void beLynched();

};

class Priest : public ACard
{
	public:
			Priest(Game* game);
			~Priest();

			void beAttacked(int attacker);
			void beLynched();
			void Protect(int index);
			int See(int index);

};

class Prince : public ACard
{
	public:
			Prince(Game* game);
			~Prince();

			void beAttacked(int attacker);
			void beLynched();

};

class Seer : public ACard
{
	public:
			Seer(Game* game);
			~Seer();

			void beAttacked(int attacker);
			void beLynched();
			int See(int index);

};

class Spellcaster : public ACard
{
	public:
			Spellcaster(Game* game);
			~Spellcaster();

			void beAttacked(int attacker);
			void beLynched();

};

class ToughGuy : public ACard
{
	public:
			ToughGuy(Game* game);
			~ToughGuy();

			void beAttacked(int attacker);
			void beLynched();

};

class TroubleMaker : public ACard
{
	public:
			TroubleMaker(Game* game);
			~TroubleMaker();

			void beAttacked(int attacker);
			void beLynched();

};

class Villager : public ACard
{
	public:
			Villager(Game* game);
			~Villager();

			void beAttacked(int attacker);
			void beLynched();

};

class Witch : public ACard
{
	public:
			Witch(Game* game);
			~Witch();

			void beAttacked(int attacker);
			void beLynched();

};

class Sorcerer : public ACard
{
	public:
			Sorcerer(Game* game);
			~Sorcerer();

			void beAttacked(int attacker);
			void beLynched();
			int SorcSee(int index);

};

class Minion : public ACard
{
	public:
			Minion(Game* game);
			~Minion();

			void beAttacked(int attacker);
			void beLynched();

};

class Cursed : public ACard
{
	public:
			Cursed(Game* game);
			~Cursed();

			void beAttacked(int attacker);
			void beLynched();

};

class Doppelganger : public ACard
{
	public:
			Doppelganger(Game* game);
			~Doppelganger();

			void beAttacked(int attacker);
			void beLynched();
			void Steal(int index);

};

class Drunk : public ACard
{
	public:
			Drunk(Game* game);
			~Drunk();

			void beAttacked(int attacker);
			void beLynched();

};

class CultLeader : public ACard
{
	public:
			CultLeader(Game* game);
			~CultLeader();

			void beAttacked(int attacker);
			void beLynched();
			void Convert(int index);

};

class Hoodlum : public ACard
{
	public:
			Hoodlum(Game* game);
			~Hoodlum();

			void beAttacked(int attacker);
			void beLynched();
			void Mischief(int index1, int index2);

};

class Tanner : public ACard
{
	public:
			Tanner(Game* game);
			~Tanner();

			void beAttacked(int attacker);
			void beLynched();

};
