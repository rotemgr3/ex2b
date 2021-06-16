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
            Character(units_t health, units_t ammo, units_t range, units_t power, Team team,
                        const char power_lifter_letter, const char cross_fitters_letter,
                        const units_t reload_supply, const int move_distance);
            Character(const Character& character) = default;
            virtual ~Character() = default;
            virtual Character& operator=(Character& character) = default;
            virtual void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                                const GridPoint& src_coordinates, const GridPoint& dst_coordinates) = 0;
            virtual bool checkIfTargetIsOutOfRange(int distance) const;
            void reload();
            virtual std::shared_ptr<Character> clone() const = 0;
            int getMoveDistance() const;
            char getTypeLetter() const;
            Team getTeam() const;
            bool isDead() const;
            friend class Soldier;
            friend class Medic;
            friend class Sniper; 
    };
}


#endif