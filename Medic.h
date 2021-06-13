#ifndef MEDIC_H
#define MEDIC_H
#include<iostream>


namespace mtm
{
    class Medic : public Character
    {
        public:
            Medic() = delete;
            Medic(int health, int ammo, int range, int power, Team team);
            ~Medic() = default;
            void attack(int range, Character& target) override;
            void reload() override;
    }
}
#endif