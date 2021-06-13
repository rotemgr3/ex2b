#include "Soldier.h"
#include <assert.h>
#include <cmath>

namespace mtm
{
    Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team) : Character(health, ammo,
                                                                                        range, power, team)
    {}
    bool Soldier::attack(int distance, Character* target)
    {
        assert(target != nullptr);
        if(target->team == team){
            return false;
        }
        if(distance == 0){
            target->health -= power;
            return target->health <= 0;
        }
        if(distance <= ceil(range/3)){
            target->health -= ceil(power/2);
        }
        return target->health <= 0;
    }
    void Soldier::reload()
    {
        ammo += 3;
    }
    std::shared_ptr<Character> Soldier::clone() const
    {
        return std::shared_ptr<Character>(new Soldier(*this));
    }
    int getMoveDistance() const
    {
        return move_distance;
    }
}