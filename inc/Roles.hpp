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
			void beLynched();

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
	private:
			int _player1;
			int _player2;

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
	private:
			int _victim;
			bool _lynched = false;

	public:
			Hunter(Game* game);
			~Hunter();
			
			void beAttacked(int attacker);
			void beLynched();
			void setVictim(int victim);
			int getVictim() const;
			void takePlayerWith(int victim);
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
	private:
			bool _healUsed = false;
			bool _killUsed = false;

	public:
			Magician(Game* game);
			~Magician();

			bool getSpellUsed(str spell) const;

			void setSpellUsed(str spell);

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

			void Dies();

};

class PI : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			PI(Game* game);
			~PI();

			int See(int index);
			bool getAbilityUsed() const;

};

class Pacifist : public ACard
{
	public:
			Pacifist(Game* game);
			~Pacifist();


};

class Priest : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			Priest(Game* game);
			~Priest();

			void Protect(int index);
			int See(int index);
			bool getAbilityUsed() const;

};

class Prince : public ACard
{
	private:
			bool _abilityUsed = false;

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
	private:
			bool _goingToDie = false;

	public:
			ToughGuy(Game* game);
			~ToughGuy();

			void beAttacked(int attacker);

};

class TroubleMaker : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			TroubleMaker(Game* game);
			~TroubleMaker();

			bool getAbilityUsed() const;
			void setAbilityUsed();
};

class Villager : public ACard
{
	public:
			Villager(Game* game);
			~Villager();

};

class Witch : public ACard
{
	private:
			bool _healUsed = false;
			bool _killUsed = false;

	public:
			Witch(Game* game);
			~Witch();

			bool getSpellUsed(str spell) const;

			void setSpellUsed(str spell);
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
	private:
			ACard* _identity;

	public:
			Doppelganger(Game* game);
			~Doppelganger();

			void Steal(int index);
			ACard* getStolenIdentity() const;

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
	private:
			int _player1;
			int _player2;

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

};
