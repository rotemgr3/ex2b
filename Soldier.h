#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"
#include <memory>

namespace mtm
{
    const char power_lifter_soldier = 'S';
    const char cross_fitters_soldier = 's';
    const units_t soldier_reload_supply = 3;
    const int soldier_range_area_factor = 3;
    const int soldier_power_factor = 2;
    class Soldier : public Character
    {
        public:
            Soldier() = delete;
            Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
            Soldier(const Soldier& soldier) : Character(soldier) {};
            ~Soldier() = default;
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
            void reload() override;
            std::shared_ptr<Character> clone() const override;
            int getMoveDistance() const;
            bool checkIfTargetIsOutOfRange(int distance);
            char getTypeLetter() const override;
        private:
            const int move_distance = 3;
    };
}
#endif