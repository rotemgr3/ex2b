#include "Medic.h"
#include <assert.h>
#include <cmath>
#include <vector>

namespace mtm
{
    Medic::Medic(units_t health, units_t ammo, units_t range, units_t power, Team team) : Character(health, ammo,
                                                                                        range, power, team)
    {}
    void Medic::reload()
    {
        ammo += medic_reload_supply;
    }
    std::shared_ptr<Character> Medic::clone() const
    {
        return std::shared_ptr<Character>(new Medic(*this));
    }
    int Medic::getMoveDistance() const
    {
        return move_distance;
    }
    bool Medic::checkIfTargetIsOutOfRange(int distance)
    {
        return distance > range;
    }
    void Medic::attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        std::shared_ptr<Character> target = board[dst_coordinates.row][dst_coordinates.col];
        if(!target){
            throw mtm::IllegalTarget();//check if Illegal_target ot Cell_empty
        }
        if(target->team == team){
            if(src_coordinates == dst_coordinates){
                throw mtm::IllegalTarget();
            }
            target->health += power;
        }
        else{
            if(ammo <= 0){
                throw mtm::OutOfAmmo();
            }
            target->health -= power;
            ammo--;
        }
    }    
    char Medic::getTypeLetter() const
    {
       if(team == POWERLIFTERS){
           return power_lifter_medic;
       }
       return cross_fitters_medic;
    }
}
