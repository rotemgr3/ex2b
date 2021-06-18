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

            /**
             * Medic: Medic constructor. create a new Medic.
             *
             * @param health - health points of medic.
             * @param ammo - ammo supply of medic.
             * @param range - range of attack of medic.
             * @param power - damgage medic make in each attack.
             * @param team - team of medic.
             * 
             * @return
             *     new medic
            */
            Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);

            /**
             * Medic: Medic copy constructor. create a new Medic.
             *
             * @param medic - medic to copy.
             * 
             * @return
             *     new copy of argument medic.
            */
            Medic(const Medic& medic) : Character(medic) {};
            ~Medic() = default;

            /**
             * attack: medic attack destination coordinates in a given board.
             *
             * @param board - the board of the game, 2-d vector of shared pointers of character.
             * @param src_coordinates - coordinates of medic.
             * @param dst_coordinates - coordinates of target.
             * 
             * @return
            */
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;

            /**
             * clone: copy medic to a shared pointer
             * 
             * @return
             *      shared pointer of a copy of medic.
            */
            std::shared_ptr<Character> clone() const override;
    };
}
#endif // MEDIC_H