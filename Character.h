#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <memory>
#include <vector>

namespace mtm
{
    class Character
    {
        protected:
            units_t health;
            units_t ammo;
            units_t range;
            units_t power;
            Team team;
            const char power_lifter_letter;
            const char cross_fitters_letter;
            const units_t reload_supply;
            const int move_distance;
        public:
            Character() = delete;

            /**
             * Character: Character constructor. create a new Character.
             *
             * @param health - health points of character.
             * @param ammo - ammo supply of character.
             * @param range - range of attack of character.
             * @param power - damgage character make in each attack.
             * @param team - team of character
             * @param power_lifter_letter - const char that represent the charecter type in power lifter.   
             * @param cross_fitters_letter - const char that represent the charecter type in cross fitters.
             * @param reload_supply - number of ammo to add to character each reload.
             * @param move_distance - number of cells charcter can make each step.
             * 
             * @return
             *     new character
            */
            Character(units_t health, units_t ammo, units_t range, units_t power, Team team,
                        const char power_lifter_letter, const char cross_fitters_letter,
                        const units_t reload_supply, const int move_distance);
            /**
             * Character: character copy constructor.
             *            create a new Character.
             *
             * @param character - character to create a copy of.
             * 
             * @return
             *     copy character of argument character.
            */
            Character(const Character& character) = default;
            virtual ~Character() = default;
            virtual Character& operator=(Character& character) = default;

            /**
             * attack: attack destination coordinates in a given board.
             *
             * @param board - the board of the game, 2-d vector of shared pointers of character.
             * @param src_coordinates - coordinates of character.
             * @param dst_coordinates - coordinates of target.
             * 
             * @return
            */
            virtual void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                                const GridPoint& src_coordinates, const GridPoint& dst_coordinates) = 0;
            /**
             * checkIfTargetIsOutOfRange: check if a target is out of charcters attack range.
             *
             * @param distance - the distance from the charcter to the taget.
             * 
             * @return
             *     true - targat is out of range.
             *     false - otherwise.
            */
            virtual bool checkIfTargetIsOutOfRange(int distance) const;

            /**
             * reload: adds reload supply to character.
             * 
             * @return
            */
            void reload();

            /**
             * clone: copy character to a shared pointer
             * 
             * @return
             *      shared pointer of a copy of character.
            */
            virtual std::shared_ptr<Character> clone() const = 0;

            /**
             * getMoveDistance: return characters max move distance in a single step
             * 
             * @return
             *      characters max move distance in a single step
            */
            int getMoveDistance() const;

            /**
             * getTypeLetter: return characters letter for printing according to character team and type
             * 
             * @return
             *      characters letter for printing according to character team and type
            */
            char getTypeLetter() const;

            /**
             * getTeam: return characters team
             * 
             * @return
             *      characters team
            */
            Team getTeam() const;

            /**
             * isDead: check if character health is zero or less
             * 
             * @return
             *      true - chacter health is zero or else
             *      false - otherwise    
            */
            bool isDead() const;
            friend class Soldier;
            friend class Medic;
            friend class Sniper; 
    };
}


#endif