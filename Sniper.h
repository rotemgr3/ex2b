#ifndef SNIPER_H
#define SNIPER_H

#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"
#include <memory>

namespace mtm
{
    const char power_lifter_sniper = 'N';
    const char cross_fitters_sniper = 'n';
    const units_t sniper_reload_supply = 2;
    const int sniper_move_distance = 4;
    const int divide_by_three = 3;
    const units_t sniper_combo_factor = 2;
    const int sniper_min_range_factor = 2;
    class Sniper : public Character
    {
        public:
            Sniper() = delete;
            Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team);
            Sniper(const Sniper& sniper) : Character(sniper) {};
            ~Sniper() = default;
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
            std::shared_ptr<Character> clone() const override;
            bool checkIfTargetIsOutOfRange(int distance) const override;
        private:
            int attacks_counter;
    };
}
#endif // MEDIC_H