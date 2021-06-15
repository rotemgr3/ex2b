#include "Sniper.h"
#include <assert.h>
#include <cmath>
#include <vector>

namespace mtm
{
    Sniper::Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team) : 
                    Character(health, ammo,range, power, team), attacks_counter(0)
    {}
    void Sniper::reload()
    {
        ammo += sniper_reload_supply;
    }
    std::shared_ptr<Character> Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }
    int Sniper::getMoveDistance() const
    {
        return move_distance;
    }
    bool Sniper::checkIfTargetIsOutOfRange(int distance)
    {
        return distance > range;
    }
    void Sniper::attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        std::shared_ptr<Character> target = board[dst_coordinates.row][dst_coordinates.col];
        if(GridPoint::distance(src_coordinates, dst_coordinates) < ceil( ((double)range) / sniper_min_range_factor)){
            throw mtm::OutOfRange();
        }
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
    char Sniper::getTypeLetter() const
    {
       if(team == POWERLIFTERS){
           return power_lifter_sniper;
       }
       return cross_fitters_sniper;
    }
}
