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
    class Medic : public Character
    {
        public:
            Medic() = delete;
            Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);
            Medic(const Medic& medic) : Character(medic) {};
            ~Medic() = default;
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
            void reload() override;
            std::shared_ptr<Character> clone() const override;
            int getMoveDistance() const;
            bool checkIfTargetIsOutOfRange(int distance);
            char getTypeLetter() const override;
        private:
            const int move_distance = 5;
    };
}
#endif // MEDIC_H