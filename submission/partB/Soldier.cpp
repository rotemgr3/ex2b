#include "Soldier.h"
#include <cmath>
#include <vector>

namespace mtm
{
    Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team) : 
                    Character(health, ammo, range, power, team, power_lifter_soldier, cross_fitters_soldier,
                            soldier_reload_supply, soldier_move_distance)
    {}

    std::shared_ptr<Character> Soldier::clone() const
    {
        return std::shared_ptr<Character>(new Soldier(*this));
    }
    
    void Soldier::attack(std::vector<std::vector<std::shared_ptr<Character>>>& board, 
                        const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        if(ammo <= 0){
            throw mtm::OutOfAmmo();
        }
        if(src_coordinates.col != dst_coordinates.col && src_coordinates.row != dst_coordinates.row){
            throw mtm::IllegalTarget();
        }
        std::vector<std::vector<std::shared_ptr<Character>>>::iterator row;
        std::vector<std::shared_ptr<Character>>::iterator col;
        for (row = board.begin(); row != board.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                int row_index = std::distance(board.begin(),row);
                int col_index = std::distance(row->begin() ,col);
                int dist = GridPoint::distance(dst_coordinates, GridPoint(row_index, col_index));
                if(dist > ceil( ((double)range) / soldier_range_area_factor)){
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
                    (*col)->health -= ceil( ((double)power) / soldier_power_factor);
                }
            }
        }
        ammo--;           
   }
}
