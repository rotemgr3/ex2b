#include "Game.h"
#include <iostream>


namespace mtm
{
    Game::Game(int height, int width)
    {
        if(height <= 0 || width <= 0){
            throw mtm::IllegalArgument();
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
                if(game.board[i][j]){
                    board[i][j] = game.board[i][j]->clone();
                }
            }
        }
    }
    Game& Game::operator=(const Game& game)
    {
        Game temp_game(game);
        height = game.height;
        width = game.width;
        this->board = temp_game.board;
        return *this;
    }
    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        if(coordinates.row >= height || coordinates.row < 0 || coordinates.col >= width || coordinates.col < 0){
            throw mtm::IllegalCell();
        }
        if(board[coordinates.row][coordinates.col]){
            throw mtm::CellOccupied();
        }
        board[coordinates.row][coordinates.col] = character;
    }
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                    units_t health, units_t ammo, 
                                                    units_t range, units_t power)
    {
        if(health < 0 || range < 0 || ammo < 0 || power < 0) {
            throw mtm::IllegalArgument();
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
        throw mtm::IllegalArgument();//shouldn't get here!
    }
    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(src_coordinates.row >= height || src_coordinates.row < 0 
          || src_coordinates.col >= width || src_coordinates.col < 0
          || dst_coordinates.row >= height || dst_coordinates.row < 0 
          || dst_coordinates.col >= width || dst_coordinates.col < 0){
            throw mtm::IllegalCell();
        }
        if(!(board[src_coordinates.row][src_coordinates.col])){
            throw mtm::CellEmpty();
        }
        int dist = GridPoint::distance(src_coordinates, dst_coordinates);
        if(board[src_coordinates.row][src_coordinates.col]->getMoveDistance() < dist){
            throw mtm::MoveTooFar();
        }
        if(board[dst_coordinates.row][dst_coordinates.col]){
            throw mtm::CellOccupied();
        }
        board[src_coordinates.row][src_coordinates.col].swap(board[dst_coordinates.row][dst_coordinates.col]);
    }
    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        if(src_coordinates.row >= height || src_coordinates.row < 0 
          || src_coordinates.col >= width || src_coordinates.col < 0
          || dst_coordinates.row >= height || dst_coordinates.row < 0 
          || dst_coordinates.col >= width || dst_coordinates.col < 0){
            throw mtm::IllegalCell();
        }
        if(!(board[src_coordinates.row][src_coordinates.col])){
            throw mtm::CellEmpty();
        }
        int dist = GridPoint::distance(src_coordinates, dst_coordinates);
        if(board[src_coordinates.row][src_coordinates.col]->checkIfTargetIsOutOfRange(dist)){
            throw mtm::OutOfRange();
        }
        board[src_coordinates.row][src_coordinates.col]->attack(board, src_coordinates, dst_coordinates);
        this->updateBoard();
    }
    void Game::updateBoard()
    {
        std::vector<std::vector<std::shared_ptr<Character>>>::iterator row;
        std::vector<std::shared_ptr<Character>>::iterator col;
        for (row = board.begin(); row != board.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                if((*col) && (*col)->isDead()){
                    col->reset();
                }
            }
        }
    }
    void Game::reload(const GridPoint & coordinates)
    {
        if(coordinates.row >= height || coordinates.row < 0 
          || coordinates.col >= width || coordinates.col < 0){
            throw mtm::IllegalCell();
        }
        if(!(board[coordinates.row][coordinates.col])) {
            throw mtm::CellEmpty();
        }
        board[coordinates.row][coordinates.col]->reload();
    }
    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        std::string str((game.height * game.width), default_empty_cell);
        std::vector<std::vector<std::shared_ptr<Character>>>::const_iterator row;
        std::vector<std::shared_ptr<Character>>::const_iterator col;
        int i = 0;
        for (row = game.board.begin(); row != game.board.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                if (*col) {
                    str[i] = (*col)->getTypeLetter();
                }
                i++;
            }
        }
        printGameBoard(os, &str[0], &str.back() + 1, game.width);
        return os;
    }
    bool Game::isOver(Team* winningTeam) const
    {
        int count_cross_fitters = 0;
        int count_power_lifters = 0;
        std::vector<std::vector<std::shared_ptr<Character>>>::const_iterator row;
        std::vector<std::shared_ptr<Character>>::const_iterator col;
        for (row = board.begin(); row != board.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                if(!*col){
                    continue;
                }
                if((*col)->getTeam() == POWERLIFTERS){
                    count_power_lifters++;
                }
                else{
                    count_cross_fitters++;
                }
            }
        }
        if(count_power_lifters == 0 && count_cross_fitters != 0){
            if(winningTeam != nullptr){
                *winningTeam = CROSSFITTERS;
            }
            return true;
        }
        if(count_cross_fitters == 0 && count_power_lifters != 0){
            if(winningTeam != nullptr){
                *winningTeam = POWERLIFTERS;
            }
            return true;
        }
        return false;
    }
}