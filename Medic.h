#ifndef MEDIC_H
#define MEDIC_H

#include <iostream>
#include "Auxiliaries.h"
#include "Character.h"
#include <memory>

namespace mtm
{
    const char power_lifter_medic = 'M';
    const char cross_fitters_medic = 'm';
    const units_t medic_reload_supply = 5;
    const int medic_move_distance = 5;
    class Medic : public Character
    {
        public:
            Medic() = delete;
            Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);
            Medic(const Medic& medic) : Character(medic) {};
            ~Medic() = default;
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
            std::shared_ptr<Character> clone() const override;
    };
}
#endif // MEDIC_H