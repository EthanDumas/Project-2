#include "CandyStore.h"
#include "Board.h"
#include <assert.h>
using namespace std;

Candy_store::Candy_store() {
    _store_name = "";
    _candy_count = 0;
}

Candy_store::Candy_store(string store_name) {
    _store_name = store_name;
    _candy_count = 0;
}

bool Candy_store::addCandy(Candy candy) {
    if(_candy_count == _MAX_CANDIES) {
        cout << "I already have plenty of candy here at " << _store_name << endl;
        return false;
    }
    _candies[_candy_count] = candy;
    _candy_count++;
    return true;
}

void Candy_store::displayCandies() const {
    if(_candy_count == 0) {
        cout << "We've got no candy at " << _store_name << endl;
        return;
    }
    cout << "Our stock is full at " << _store_name << endl;
    for(int i = 0; i < _candy_count; i++) {
        cout << _candies[i].name << endl;
    }
}
