#include "Soldier.h"
#include <assert.h>
#include <cmath>
#include <vector>

namespace mtm
{
    Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team) : Character(health, ammo,
                                                                                        range, power, team)
    {}
    void Soldier::reload()
    {
        ammo += 3;
    }
    std::shared_ptr<Character> Soldier::clone() const
    {
        return std::shared_ptr<Character>(new Soldier(*this));
    }
    int Soldier::getMoveDistance() const
    {
        return move_distance;
    }
    bool Soldier::checkIfTargetIsOutOfRange(int distance)
    {
        return distance > range;
    }
    void Soldier::attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& dst_coordinates)
    {
        if(ammo <= 0){
            throw mtm::OutOfAmmo();
        }
        std::vector<std::vector<std::shared_ptr<Character>>>::iterator row;
        std::vector<std::shared_ptr<Character>>::iterator col;
        for (row = board.begin(); row != board.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                int row_index = std::distance(board.begin(),row);
                int col_index = std::distance(row->begin() ,col);
                int dist = GridPoint::distance(dst_coordinates, GridPoint(row_index, col_index));
                if(dist > ceil(range/3)){
                    continue;
                }
                if(!(*col)){
                    continue;
                }
                if((*col)->team == team){
                    continue;
                }
                if(dist == 0){
                    (*col)->health -= power;
                }
                else{
                    (*col)->health -= ceil(power/2);
                }
            }
        }           
   }
   char Soldier::getTypeLetter() const
   {
       if(team == POWERLIFTERS){
           return power_lifter_soldier;
       }
       return cross_fitters_soldier;
   }
}
