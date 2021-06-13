#ifndef SNIPER_H
#define SNIPER_H
#include<iostream>


namespace mtm
{
    class Sniper : public Character
    {
        public:
            Sniper() = delete;
            Sniper(int health, int ammo, int range, int power, Team team);
            ~Sniper() = default;
            void attack(int range, Character& target) override;
            void reload() override;
    }
}
#endif