#include "Character.h"


namespace mtm 
{
    Character::Character(units_t health, units_t ammo, units_t range, units_t power, Team team,
                const char power_lifter_letter, const char cross_fitters_letter,
                const units_t reload_supply, const int move_distance) : 
            health(health), ammo(ammo), range(range), power(power), team(team),
            power_lifter_letter(power_lifter_letter), cross_fitters_letter(cross_fitters_letter),
            reload_supply(reload_supply), move_distance(move_distance)
    {}
    void Character::reload()
    {
        ammo += reload_supply;
    }

    int Character::getMoveDistance() const
    {
        return move_distance;
    }

    bool Character::checkIfTargetIsOutOfRange(int distance) const
    {
        return distance > range;
    }

    char Character::getTypeLetter() const
    {
       if(team == POWERLIFTERS){
           return power_lifter_letter;
       }
       return cross_fitters_letter;
    }

    Team Character::getTeam() const 
    {
        return team;
    }

    bool Character::isDead() const 
    {
        return health <= 0;
    }
}