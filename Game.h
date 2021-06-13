#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <memory>
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

namespace mtm
{
    typedef std::vector<std::vector<std::shared_ptr<Character>>> board_t;
    class Game
    {
        private:
            board_t board;
            int height;
            int width;
        public:
            Game(int height, int width);
            ~Game() = default;
            Game(const Game& game);
            Game& operator=(const Game& game);
            void AddCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                            units_t health, units_t ammo, 
                                                            units_t range, units_t power);
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void reload(const GridPoint & coordinates);
            friend std::ostream& operator<<(std::ostream& os, const Game& game);
            bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif