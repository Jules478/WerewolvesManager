#pragma once

#include "ACard.hpp"
#include "Doppelganger.hpp"

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
	private:
			bool _whichSeer = false;
			bool _replacedSeer = false;

	public:
			ApprenticeSeer(Game* game);
			~ApprenticeSeer();

			bool getWhichSeer() const;
			void setWhichSeer(bool which);
			bool getAbilityUsed(bool checkIfCopied) const;
			void setAbilityUsed();

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
	private:
		int _lastProtect = -1;

	public:
			Bodyguard(Game* game);
			~Bodyguard();

			void Protect(int index);
			void setPlayer1(int index);
			int getPlayer1();

};

class Cupid : public ACard
{
	private:
			int _player1;
			int _player2;

	public:
			Cupid(Game* game);
			~Cupid();

			void setPlayer1(int index);
			void setPlayer2(int index);
			int getPlayer1();
			int getPlayer2();

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

	public:
			Hunter(Game* game);
			~Hunter();
			
			void beAttacked(int attacker);
			void beLynched();
			void setVictim(int victim);
			int getVictim() const;
			void takePlayerWith(int victim);
			void setLife(bool alive);
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
			void Protect(int index);

};

class Martyr : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			Martyr(Game* game);
			~Martyr();

			bool getAbilityUsed(bool checkIfCopied) const;
			void setAbilityUsed();

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
	private:
			bool _diesOldAge = false;

	public:
			OldMan(Game* game);
			~OldMan();

			void Dies();
			bool getAbilityUsed(bool checkIfCopied) const;
			
};

class PI : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			PI(Game* game);
			~PI();

			int See(int index);
			bool getAbilityUsed(bool checkIfCopied) const;

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
			bool getAbilityUsed(bool checkIfCopied) const;

};

class Prince : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			Prince(Game* game);
			~Prince();

			void beLynched();

			bool getAbilityUsed(bool checkIfCopied) const;

};

class Seer : public ACard
{
	private:
			bool _secondSeer = false;

	public:
			Seer(Game* game);
			~Seer();

			int See(int index);
			bool getAbilityUsed(bool checkIfCopied) const;
			void setAbilityUsed();

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
			bool getAbilityUsed(bool checkIfCopied) const;
};

class TroubleMaker : public ACard
{
	private:
			bool _abilityUsed = false;

	public:
			TroubleMaker(Game* game);
			~TroubleMaker();

			bool getAbilityUsed(bool checkIfCopied) const;
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
			void Protect(int index);
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
	private:
			bool _abilityUsed = false;

	public:
			Cursed(Game* game);
			~Cursed();

			void beAttacked(int attacker);
			bool getAbilityUsed(bool checkIfCopied) const;
			void setAbilityUsed();

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

			int getPlayer1();
			int getPlayer2();

			void setPlayer1(int index);
			void setPlayer2(int index);

};

class Tanner : public ACard
{
	public:
			Tanner(Game* game);
			~Tanner();

};