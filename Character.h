#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "Auxiliaries.h"


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
            Character(Character& character);
            virtual ~Character() = default;
            virtual Character& operator=(Character& character) = default;
            virtual bool attack(int distance, Character& target) = 0;
            virtual void reload() = 0;
            virtual std::shared_ptr<Character> clone() const = 0;
            virtual int getMoveDistance() const = 0;
            friend class Soldier;
    };
}


#endif