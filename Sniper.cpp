#include "Sniper.h"
#include <cmath>
#include <vector>

namespace mtm
{
    Sniper::Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team) : 
                Character(health, ammo, range, power, team, power_lifter_sniper, cross_fitters_sniper,
                        sniper_reload_supply, sniper_move_distance), attacks_counter(0)
    {}
    std::shared_ptr<Character> Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }
    
    bool Sniper::checkIfTargetIsOutOfRange(int distance) const
    {
        return distance > range || distance < ceil(((double)range) / sniper_min_range_factor);
    }

    void Sniper::attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        std::shared_ptr<Character> target = board[dst_coordinates.row][dst_coordinates.col];
        if(ammo <= 0){
            throw mtm::OutOfAmmo();
        }
        if(!target || target->team == team){
            throw mtm::IllegalTarget();
        }
        ammo--;
        attacks_counter++;
        if(attacks_counter % divide_by_three == 0){
            target->health -= sniper_combo_factor * power;
        }
        else{
            target->health -= power;
        }
    }    
}
