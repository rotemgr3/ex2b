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
    const int soldier_move_distance = 3;
    const int soldier_range_area_factor = 3;
    const int soldier_power_factor = 2;
    class Soldier : public Character
    {
        public:
            Soldier() = delete;

            /**
             * Soldier: Soldier constructor. create a new Soldier.
             *
             * @param health - health points of soldier.
             * @param ammo - ammo supply of soldier.
             * @param range - range of attack of soldier.
             * @param power - damgage soldier make in each attack.
             * @param team - team of soldier.
             * 
             * @return
             *     new soldier
            */
            Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);

            /**
             * Soldier: Soldier copy constructor. create a new Soldier.
             *
             * @param soldier - soldier to copy.
             * 
             * @return
             *     new copy of argument soldier.
            */
            Soldier(const Soldier& soldier) : Character(soldier) {};
            ~Soldier() = default;

            /**
             * attack: soldier attack destination coordinates in a given board.
             *
             * @param board - the board of the game, 2-d vector of shared pointers of character.
             * @param src_coordinates - coordinates of soldier.
             * @param dst_coordinates - coordinates of target.
             * 
             * @return
            */
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
            
            /**
             * clone: copy soldier to a shared pointer
             * 
             * @return
             *      shared pointer of a copy of soldier.
            */
            std::shared_ptr<Character> clone() const override;
    };
}
#endif