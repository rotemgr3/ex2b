#include <iostream>
#include <iostream>
#include <fstream>
#include <cassert>

#include "./../Exceptions.h"
#include "./../Game.h"

using namespace mtm;

void test_basic_errors();
void test_rules_1();

int main()
{
    test_basic_errors();
    test_rules_1();
}

void test_basic_errors()
{
    std::cout << "------test_basic_errors------" << std::endl;
    Game g1(1, 1);

    // move from empty cell to same cell
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }
    // move from empty cell to empty cell
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }
    // negative gridpoint src
    try
    {
        g1.move(GridPoint(-1, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    //  negative gridpoint dst
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(-1, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    //  CellEmpty vs. IllegalCell
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(1, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    // Attack from empty cell
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }
    // Attack from empty cell to out of bounds, CellEmpty vs. IllegalCell
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 1));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    //zero health
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 0, 2, 4, 5));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }
    //negative health
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, -5, 2, 4, 5));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }
    //copy
    Game g2(g1);
    assert((&g1 == &g2) == false);

    //zero ammo, range and power (legal)
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, 0, 0));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //checks if g2 content is the same as g1 (cell is occupied)
    try
    {
        g2.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }

    // checks if medic can attack itself
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    // checks if medic can move to itself
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Medic moves to out of bounds
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 1));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    //negative ammo
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, -1, 0, 0));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //negative range
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, -1, 0));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //negative power
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, 0, -1));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //cell occupied check
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, 0, 1));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Adding Sniper
    try
    {
        g2.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 5, 0, 0, 1));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Sniper attacking itself
    try
    {
        g2.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Adding Soldier
    Game g3(1, 1);

    try
    {
        g3.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 5, 0, 0, 1));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }

    //Soldier attacking itself (Out of ammo)
    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Soldier attacking itself
    try
    {
        g3.reload(GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Soldier shoots until out of ammo
    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    //check assignment
    Game g4(2, 2);
    g4 = g3;
    //Board becomes 1x1
    try
    {
        g4.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 2, 4, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g4.reload(GridPoint(1, 1));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    // Checks g4 is not the same as g3
    try
    {
        g4.reload(GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        g4.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    mtm::Team winning_team = mtm::Team::CROSSFITTERS;
    assert(g1.isOver(&winning_team) == true);
    assert(winning_team == POWERLIFTERS);
    assert(g2.isOver(&winning_team) == true);
    assert(winning_team == CROSSFITTERS);
    assert(g3.isOver(&winning_team) == true);
    assert(winning_team == CROSSFITTERS);
    assert(g4.isOver(&winning_team) == true);
    assert(winning_team == CROSSFITTERS);
    Game g5(1, 1);
    assert(g5.isOver(&winning_team) == false);
    std::cout << "\ntest_basic_errors[Ok]\n\n";
}

void test_rules_1()
{
    std::cout << "------test_rules_1------" << std::endl;

    Game g1(2, 2);
    //check attacks
    std::cout << "\n"
              << g1;
    try
    {
        g1.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 2, 4, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 5, 2, 1, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 0, 3));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 1));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";

    try
    {
        g1.reload(GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";

    //checking sniper
    try
    {
        g1.addCharacter(GridPoint(1, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 6, 2, 1, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 6, 2, 2, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(1, 1), GridPoint(1, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.reload(GridPoint(0, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";
    mtm::Team winning_team = mtm::Team::CROSSFITTERS;
    assert(g1.isOver(&winning_team) == false);
    assert((winning_team == POWERLIFTERS) == false);
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 1));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";

    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";

    try
    {
        g1.reload(GridPoint(0, 1));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n"
              << g1 << "\n";
    //check if soldier can attack if not in the same line (he shouldn't)
    try
    {
        g1.addCharacter(GridPoint(1, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 6, 8, 3, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
        std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(1, 0), GridPoint(0, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
        std::cout << "\n"
              << g1 << "\n";
    try
    {
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
        g1.attack(GridPoint(1, 0), GridPoint(1, 1));
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
            std::cout << "\n"
              << g1 << "\n";
                 
    assert(g1.isOver(&winning_team) == true);
    assert((winning_team == POWERLIFTERS) == true);
}
