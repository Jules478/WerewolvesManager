#pragma once

#include <iostream>

typedef std::string str;

# define RED "\e[0;31m"
# define BLUE "\e[0;34m"
# define GREEN "\e[0;32m"
# define PURPLE "\e[0;35m"
# define YELLOW "\e[0;33m"
# define WHITE "\e[0;37m"
# define GREY "\e[0;90m"
# define RESET "\e[0m"

typedef enum e_roles
{
	WEREWOLF_ROLE,
	WOLFCUB_ROLE,
	LONEWOLF_ROLE,
	VAMPIRE_ROLE,
	APPRENTICESEER_ROLE,
	AURASEER_ROLE,
	BODYGUARD_ROLE,
	CUPID_ROLE,
	DISEASED_ROLE,
	GHOST_ROLE,
	HUNTER_ROLE,
	IDIOT_ROLE,
	LYCAN_ROLE,
	MAGICIAN_ROLE,
	MARTYR_ROLE,
	MASON_ROLE,
	MAYOR_ROLE,
	OLDHAG_ROLE,
	OLDMAN_ROLE,
	PI_ROLE,
	PACIFIST_ROLE,
	PRIEST_ROLE,
	PRINCE_ROLE,
	SEER_ROLE,
	SPELLCASTER_ROLE,
	TOUGHGUY_ROLE,
	TROUBLEMAKER_ROLE,
	VILLAGER_ROLE,
	WITCH_ROLE,
	SORCERER_ROLE,
	MINION_ROLE,
	CURSED_ROLE,
	DOPPELGANGER_ROLE,
	CULTLEADER_ROLE,
	HOODLUM_ROLE,
	TANNER_ROLE,
	MAX_ROLES
} t_roles;

typedef enum	e_sides
{
	VILLAGER,
	WEREWOLF,
	VAMPIRE
}	t_sides;

class Game;

class ACard
{
	protected:
			ACard(t_roles role, str name, int side, bool wakes, Game* game, int value);
			t_roles _role;
			str _name;
			int _side;
			int	_index = -1;
			bool _alive = true;
			bool _wakes;
			Game* _game;
			bool _inVillage = true;
			int _value;
			bool _isDrunk = false;
			bool _inCult = false;
	
	public:
			virtual ~ACard();

			virtual int See(int index) { (void)index; return -1; }
			virtual void bePromoted() { return ; }
			virtual void Pox(int index) { (void)index; return ; }
			virtual void Protect(int index) { (void)index; return ; }
			virtual int SorcSee(int index) { (void)index; return -1; }
			virtual void Steal(int index) { (void)index; return ; }
			virtual void Convert(int index) { (void)index; return ; }
			virtual void Mischief(int index1, int index2) { (void)index1; (void)index2; return ; }
			virtual void setVictim(int victim) { (void)victim ; }
			virtual bool getSpellUsed(str spell) const { (void)spell; return false ; }
			virtual void setSpellUsed(str spell) { (void)spell ; }
			virtual bool getAbilityUsed(bool checkIfCopied) const { (void)checkIfCopied; return true ; }
			virtual void setAbilityUsed() { return ; }
			virtual void copy(int index) { (void)index; return ; }
			virtual void takePlayerWith(int victim) { (void)victim ; }
			virtual int getVictim() const { return -1; }
			virtual int getPlayer1() { return -1; }
			virtual int getPlayer2() { return -1; }
			virtual void setPlayer1(int index) { (void)index; return ; }
			virtual void setPlayer2(int index) { (void)index; return ; }
			virtual void Dies() { return ; }
			virtual int getCopiedRole() const { return -1; }

			int getSide() const;
			int getIndex() const;
			bool getLife() const;
			bool getWakes() const;
			t_roles getRole() const;
			str getName() const;
			bool getInVillage() const;
			int getValue() const;
			bool getDrunk() const;
			bool getInCult() const;

			void setRole(t_roles role);
			void setIndex(int index);
			void setSide(int side);
			virtual void setLife(bool alive);
			void setInVillage(bool exile);
			void setInCult();
			void setDrunk();

			virtual void beAttacked(int attacker);
			virtual void beLynched();

};