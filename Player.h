#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include <iostream>
#include <vector>
using namespace std;


class Player {
    private:
    const static int _MAX_CANDY_AMOUNT = 9;
    string _name;
    int _stamina;
    double _gold;
    string _effect;
    Candy _inventory[_MAX_CANDY_AMOUNT];
    int _candy_amount;

    public:
    Player();
    Player(int stamina, double gold, string effect, Candy inventory[], const int CANDY_ARR_SIZE);

    int getCandyAmount() const;

    void setName(string);
    string getName() const;
    
    void setStamina(int);
    int getStamina() const;

    void setGold(double);
    double getGold() const;

    void setEffect(string);
    string getEffect() const;

    void printInventory();

    Candy findCandy(string candy_name);

    bool addCandy(Candy candy);

    bool removeCandy(string candy_name);
};
#endif
