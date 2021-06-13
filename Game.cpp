#include "Game.h"
#include <iostream>


namespace mtm
{
    Game::Game(int height, int width)
    {
        if(height <= 0 || width <= 0){
            throw IllegalArgument();
        }
        board.resize(height, std::vector<std::shared_ptr<Character>>(width));
        this->height = height;
        this->width = width;
    }
    Game::Game(const Game& game)
    {
        height = game.height;
        width = game.width;
        board.resize(height, std::vector<std::shared_ptr<Character>>(width));
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                board[i][j] = game.board[i][j]->clone();
            }
        }
    }
    Game& Game::operator=(const Game& game)
    {
        Game temp_game(game);
        height = game.height;
        width = game.width;
        this->board = temp_game.board;
    }
    void Game::AddCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        if(coordinates.row >= height || coordinates.row < 0 || coordinates.col >= width || coordinates.col < 0){
            throw IllegalCell();
        }
        if(!(board[coordinates.row][coordinates.col])){
            throw CellOccupied();
        }
        board[coordinates.row][coordinates.col] = character;
    }
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                    units_t health, units_t ammo, 
                                                    units_t range, units_t power)
    {
        if(health <= 0 || ammo < 0 || range < 0 || power < 0){
            throw IllegalArgument();
        }
        if(type == SOLDIER){
            return std::shared_ptr<Character>(new Soldier(health, ammo, range, power, team));
        }
        if(type == MEDIC){
            return std::shared_ptr<Character>(new Medic(health, ammo, range, power, team));
        }
        if(type == SNIPER){
            return std::shared_ptr<Character>(new Sniper(health, ammo, range, power, team));
        }
        throw IllegalArgument();//shouldn't get here!
    }
    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(src_coordinates.row >= height || src_coordinates.row < 0 
          || src_coordinates.col >= width || src_coordinates.col < 0
          || dst_coordinates.row >= height || dst_coordinates.row < 0 
          || dst_coordinates.col >= width || dst_coordinates.col < 0){
            throw IllegalCell();
        }
        if(!(board[src_coordinates.row][src_coordinates.col])){
            throw CellEmpty();
        }
        int dist = GridPoint::distance(src_coordinates, dst_coordinates);
        if(board[src_coordinates.row][src_coordinates.col]->getMoveDistance() > dist){
            throw MoveTooFar();
        }
        if(!(board[dst_coordinates.row][dst_coordinates.col])){
            throw CellOccupied();
        }
        board[src_coordinates.row][src_coordinates.col].swap(board[dst_coordinates.row][dst_coordinates.col]);
    }
    void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(src_coordinates.row >= height || src_coordinates.row < 0 
          || src_coordinates.col >= width || src_coordinates.col < 0
          || dst_coordinates.row >= height || dst_coordinates.row < 0 
          || dst_coordinates.col >= width || dst_coordinates.col < 0){
            throw IllegalCell();
        }
        if(!(board[src_coordinates.row][src_coordinates.col])){
            throw CellEmpty();
        }
        int dist = GridPoint::distance(src_coordinates, dst_coordinates);
        if(board[src_coordinates.row][src_coordinates.col]->checkIfTargetIsOutOfRange(dist)){
            throw OutOfRange();
        }

    }

}