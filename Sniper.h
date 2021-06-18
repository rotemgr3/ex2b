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

            /**
             * Sniper: Sniper constructor. create a new Sniper.
             *
             * @param health - health points of sniper.
             * @param ammo - ammo supply of sniper.
             * @param range - range of attack of sniper.
             * @param power - damgage sniper make in each attack.
             * @param team - team of sniper.
             * 
             * @return
             *     new sniper
            */
            Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team);

            
            /**
             * Sniper: Sniper copy constructor. create a new Sniper.
             *
             * @param soldier - sniper to copy.
             * 
             * @return
             *     new copy of argument sniper.
            */
            Sniper(const Sniper& sniper) : Character(sniper) {};
            ~Sniper() = default;

            /**
             * attack: sniper attack destination coordinates in a given board.
             *
             * @param board - the board of the game, 2-d vector of shared pointers of character.
             * @param src_coordinates - coordinates of sniper.
             * @param dst_coordinates - coordinates of target.
             * 
             * @return
            */
            void attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
            
            /**
             * clone: copy sniper to a shared pointer
             * 
             * @return
             *      shared pointer of a copy of sniper.
            */
            std::shared_ptr<Character> clone() const override;

            /**
             * checkIfTargetIsOutOfRange: check if a target is out of snipers attack range.
             *
             * @param distance - the distance from the sniper to the taget.
             * 
             * @return
             *     true - targat is out of range.
             *     false - otherwise.
            */
            bool checkIfTargetIsOutOfRange(int distance) const override;
        private:
            int attacks_counter;
    };
}
#endif // SNIPER_H