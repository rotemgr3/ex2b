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
            int health;
            int ammo;
            int range;
            int power;
            Team team;
        public:
            Character() = delete;
            Character(units_t health, units_t ammo, units_t range, units_t power, Team team) : health(health),
            ammo(ammo), range(range), power(power), team(team) {};
            Character(const Character& character) = default;
            virtual ~Character() = default;
            virtual Character& operator=(Character& character) = default;
            virtual void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                                const GridPoint& src_coordinates, const GridPoint& dst_coordinates) = 0;
            virtual bool checkIfTargetIsOutOfRange(int distance) = 0;
            virtual void reload() = 0;
            virtual std::shared_ptr<Character> clone() const = 0;
            virtual int getMoveDistance() const = 0;
            virtual char getTypeLetter() const = 0;
            Team getTeam() const {return team;};
            friend class Soldier;
            friend class Medic;
            friend class Sniper;
            bool isDead() const {return health <= 0;};
    };
}


#endif