#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"
#include <memory>

namespace mtm
{
    class Soldier : public Character
    {
        public:
            Soldier() = delete;
            Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
            Soldier(Soldier& soldier) = default;
            ~Soldier() = default;
            bool attack(int distance, Character& target) override;
            void reload() override;
            std::shared_ptr<Character> clone() const override;
            int getMoveDistance() const;
        private:
            const int move_distance = 3;
    };
}
#endif