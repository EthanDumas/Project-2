#ifndef CANDYSTORE_H
#define CANDYSTORE_H
#include "Board.h"
#include <iostream>
using namespace std;



class Candy_store {
    private:
    string _store_name;
    const static int  _MAX_CANDIES = 3;
    Candy _candies[_MAX_CANDIES];
    int _candy_count;

    public:
    Candy_store();
    Candy_store(string store_name);

    bool addCandy(Candy candy);
    bool removeCandy(string candy_name);
    void displayCandies() const;
};
#endif
