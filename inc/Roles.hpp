#pragma once

#include "ACard.hpp"

class Game;

class Werewolf : public ACard
{
	public:
			Werewolf(Game* game);
			~Werewolf();

			void beAttacked(int attacker);
};

class WolfCub : public ACard
{
	public:
			WolfCub(Game* game);
			~WolfCub();

			void beAttacked(int attacker);

};

class LoneWolf : public ACard
{
	public:
			LoneWolf(Game* game);
			~LoneWolf();

			void beAttacked(int attacker);

};

class Vampire : public ACard
{
	public:
			Vampire(Game* game);
			~Vampire();

			void beAttacked(int attacker);

};

class ApprenticeSeer : public ACard
{
	public:
			ApprenticeSeer(Game* game);
			~ApprenticeSeer();

			void bePromoted();
			int See(int index);

};

class AuraSeer : public ACard
{
	public:
			AuraSeer(Game* game);
			~AuraSeer();

			int See(int index);
};

class Bodyguard : public ACard
{
	public:
			Bodyguard(Game* game);
			~Bodyguard();

			void Protect(int index);

};

class Cupid : public ACard
{
	public:
			Cupid(Game* game);
			~Cupid();

			void Love(int index1, int index2);

};

class Diseased : public ACard
{
	public:
			Diseased(Game* game);
			~Diseased();

};

class Ghost : public ACard
{
	public:
			Ghost(Game* game);
			~Ghost();

};

class Hunter : public ACard
{
	public:
			Hunter(Game* game);
			~Hunter();

			void beAttacked(int attacker, int victim);
			void beLynched();

};

class Idiot : public ACard
{
	public:
			Idiot(Game* game);
			~Idiot();

};

class Lycan : public ACard
{
	public:
			Lycan(Game* game);
			~Lycan();

};

class Magician : public ACard
{
	public:
			Magician(Game* game);
			~Magician();

};

class Martyr : public ACard
{
	public:
			Martyr(Game* game);
			~Martyr();

};

class Mason : public ACard
{
	public:
			Mason(Game* game);
			~Mason();

};

class Mayor : public ACard
{
	public:
			Mayor(Game* game);
			~Mayor();

};

class OldHag : public ACard
{
	public:
			OldHag(Game* game);
			~OldHag();

			void Pox(int index);

};

class OldMan : public ACard
{
	public:
			OldMan(Game* game);
			~OldMan();

			void Dies(int round);

};

class PI : public ACard
{
	public:
			PI(Game* game);
			~PI();

			int See(int index);

};

class Pacifist : public ACard
{
	public:
			Pacifist(Game* game);
			~Pacifist();


};

class Priest : public ACard
{
	public:
			Priest(Game* game);
			~Priest();

			void Protect(int index);
			int See(int index);

};

class Prince : public ACard
{
	public:
			Prince(Game* game);
			~Prince();

			void beLynched();

};

class Seer : public ACard
{
	public:
			Seer(Game* game);
			~Seer();

			int See(int index);

};

class Spellcaster : public ACard
{
	public:
			Spellcaster(Game* game);
			~Spellcaster();

};

class ToughGuy : public ACard
{
	public:
			ToughGuy(Game* game);
			~ToughGuy();

			void beAttacked(int attacker);
			void actuallyDies(int attacker);

};

class TroubleMaker : public ACard
{
	public:
			TroubleMaker(Game* game);
			~TroubleMaker();

};

class Villager : public ACard
{
	public:
			Villager(Game* game);
			~Villager();

};

class Witch : public ACard
{
	public:
			Witch(Game* game);
			~Witch();

};

class Sorcerer : public ACard
{
	public:
			Sorcerer(Game* game);
			~Sorcerer();

			int SorcSee(int index);

};

class Minion : public ACard
{
	public:
			Minion(Game* game);
			~Minion();

};

class Cursed : public ACard
{
	public:
			Cursed(Game* game);
			~Cursed();

			void beAttacked(int attacker);

};

class Doppelganger : public ACard
{
	public:
			Doppelganger(Game* game);
			~Doppelganger();

			void Steal(int index);

};

class Drunk : public ACard
{
	public:
			Drunk(Game* game);
			~Drunk();

};

class CultLeader : public ACard
{
	public:
			CultLeader(Game* game);
			~CultLeader();

			void Convert(int index);

};

class Hoodlum : public ACard
{
	public:
			Hoodlum(Game* game);
			~Hoodlum();

			void Mischief(int index1, int index2);

};

class Tanner : public ACard
{
	public:
			Tanner(Game* game);
			~Tanner();

			void beAttacked(int attacker);

};
