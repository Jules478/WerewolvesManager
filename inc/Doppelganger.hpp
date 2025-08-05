#pragma once

#include "ACard.hpp"

class Game;

class Doppelganger : public ACard
{
	private:
			t_roles _copiedRole;
			int _copiedPlayer;
			bool _abilityUsed = false;

			bool _copiedAbilityUsed = false;

			int _hunter_victim;

			bool _copiedHealUsed = false;
			bool _copiedKillUsed = false;

	public:
			Doppelganger(Game* game);
			~Doppelganger();
				
			// Doppelganger Native Functions
			void copy(int index) override;
			int getCopiedRole() const override;
			// Implement a way to get the player index
			bool getAbilityUsed(bool checkIfCopied) const override;
			void setAbilityUsed() override;
				
			// Override virtual methods from ACard for polymorphic behavior
			void beAttacked(int attacker) override;
			void beLynched() override;
			void setLife(bool alive) override;
				
			// Hunter methods
			void setVictim(int victim) override;
			int getVictim() const override;
			void takePlayerWith(int victim) override;
				
			// Witch/Magician methods
			bool getSpellUsed(str spell) const override;
			void setSpellUsed(str spell) override;
				
			// Seer methods
			int See(int index) override;
				
			// AuraSeer methods
			int SorcSee(int index) override;
				
			// Bodyguard/Priest methods
			void Protect(int index) override;
				
			// OldHag methods
			void Pox(int index) override;
				
			// OldMan methods
			void Dies() override;
				
			// CultLeader methods
			void Convert(int index) override;

	private:
			// Helper methods for role-specific behavior implementation
			void hunterBeAttacked(int attacker);
			void hunterBeLynched();
			void hunterSetLife(bool alive);
				
			void toughguyBeAttacked(int attacker);
				
			void cursedBeAttacked(int attacker);
				
			void werewolfBeAttacked(int attacker);
			void wolfcubBeAttacked(int attacker);
			void wolfcubBeLynched();
			void lonewolfBeAttacked(int attacker);
				
			void vampireBeAttacked(int attacker);
				
			void princeBeLynched();

};
