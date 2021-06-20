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
#include <string>

namespace mtm
{
    const char default_empty_cell = ' ';
    class Game
    {
        private:
            std::vector<std::vector<std::shared_ptr<Character>>> board;
            int height;
            int width;
        public:

             /**
             * Game: Game constructor. create a new Game.
             *
             * @param height - number of rows in board, positive number. 
             * @param width - number of columns in board, positive number.
             * 
             * @return
             *     new game
            */
            Game(int height, int width);
            ~Game() = default;

            /**
             * Game: Game copy Game. Create a new Game.
             *
             * @param game - game to create a copy of.
             * 
             * @return
             *     copy game of argument game.
            */
            Game(const Game& game);
            Game& operator=(const Game& game);

            /**
             * addCharacter: adds a new charcter to the game
             *
             * @param coordinates - point in the board to place the new character at.
             * @param character - shared pointer of charcter to add to game.
             * 
             * @return
             *     
            */
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

            /**
             * makeCharacter: creates a new character
             *
             * @param type - type of charcter - SOLDIER/MEDIC/SNIPER
             * @param team - team of charcter - POWERLIFTERS/CROSSFITTERS
             * @param health - number of health points of character. non-negative.
             * @param ammo - ammo supply of character. non-negative.
             * @param range - attack range of character. non-negative.
             * @param power - number of health points of character. non-negative.
             * 
             * @return
             *     shared pointer of the new charcter created
            */
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                            units_t health, units_t ammo, 
                                                            units_t range, units_t power);
            
            /**
             * move: moves charcter from source coordinates to destination coordinates.
             *
             * @param src_coordinates - source coordinates, location of the character to move.
             * @param dst_coordinates - destination coordinates, new location of the charcter.
             * 
             * @return
             * 
            */
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

            /**
             * attack: attack character at destination coordinates via character at source coordinates.
             *
             * @param src_coordinates - source coordinates, location of the attacker.
             * @param dst_coordinates - destination coordinates, location of target.
             * 
             * @return
             * 
            */
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

            /**
             * updateBoard: removes dead players from board.
             *
             * @return
             * 
            */
            void updateBoard();

            /**
             * reload: add ammo to character at a given coordinates
             * 
             * @param coordinates - location of the charcter who will reload.
             *
             * @return
             * 
            */
            void reload(const GridPoint & coordinates);
            friend std::ostream& operator<<(std::ostream& os, const Game& game);

            /**
             * isOver: check if the game is over or not
             * 
             * @param winningTeam - pointer that will obtain the winning team if there is one.
             *
             * @return
             *      true - there is a winning team.
             *      false - otherwise.    
            */
            bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif