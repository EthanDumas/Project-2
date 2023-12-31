#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <assert.h>
#include <sstream>
#include <fstream>
#include "Player.h"
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Candy
{
    string name;
    string description;
    string effect_type;
    string effect_value;
    string candy_type;
    double price;
};

struct Tile
{
    string color;
    string tile_type;
};

struct Card
{
    string color;
    bool two;
};

struct Riddle
{
    string riddle_question;
    string riddle_answer;
};

class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    vector<Board> Bplayers;
    vector<Player> Pplayers;
    int _player_position;
    int special_tiles_position[4];
    int hidden_treasures[3];


    
public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    bool setPlayerPosition(int, int);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition(int) const;

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 

    bool movePlayer(int tile_to_move_forward, int player);

    int getCandyStoreIndex(int);

    vector<Candy> _candy(string);
    Card getCard();
    int getCardMovement(int player);
};
#endif
