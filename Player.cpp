#include "Player.h"
#include "Board.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


Player::Player() {
    _stamina = 0;
    _gold = 0;
    _effect = "";
    _candy_amount = 0;

    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        _inventory[i] = Candy{"","",0,""};
    }
}

Player::Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE) {
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    _candy_amount = 0;

    for(int i = 0; i < CANDY_ARR_SIZE && i < _MAX_CANDY_AMOUNT; i++) {
        if(candy_array[i].name != "" && candy_array[i].description != "" && candy_array[i].price != 0 && candy_array[i].candy_type != "") {
        _inventory[i] = candy_array[i];
        _candy_amount++;
        }
    }
}

int Player::getCandyAmount() const {
    return _candy_amount;
}

void Player::setStamina(int zap) {
    _stamina = zap;
}
int Player::getStamina() const {
    return _stamina;
}

void Player::setGold(double dabloon) {
    _gold = dabloon;
}
double Player::getGold() const {
    return _gold;
}

void Player::setEffect(string HDWGH) {
    _effect = HDWGH;
}
string Player::getEffect() const {
    return _effect;
}

void Player::printInventory() {
    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        if(i % 2 == 0) {
            if(_inventory[i].name == "") {
                cout << "|[Empty]|";
            }
            else {
                cout << "|[" << _inventory[i].name << "]|";
            }
        }
        else {
            if(_inventory[i].name == "") {
                cout << "[Empty]|" << endl;
            }
            else {
                cout << "[" << _inventory[i].name << "]|" << endl;
            }
        }
    }
}

Candy Player::findCandy(string candy_name) {
    for(int i = 0; i < _candy_amount; i++) {
        if(_inventory[i].name == candy_name) {
            return _inventory[i];
        }
    }
    return Candy{};
}

bool Player::addCandy(Candy candy) {
    if(_candy_amount < _MAX_CANDY_AMOUNT) {
        _candy_amount++;
        _inventory[_candy_amount-1] = candy;
        return true;
    }
    else {
        return false;
    }
}

bool Player::removeCandy(string candy_name) {
    string word;
    string temp;

    stringstream ss(candy_name);
    while(ss >> word) {
        word = tolower(word.at(0));
        temp.append(word);
        temp.append(" ");
    }
    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
        string dorw;
        string pmet;

        stringstream ss(_inventory[i].name);
        while(ss >> dorw) {
            dorw = tolower(dorw.at(0));
            pmet.append(dorw);
            pmet.append(" ");
        }
        if(word == dorw) {
            for(int j = i; j < _MAX_CANDY_AMOUNT - 1; j++) {
                _inventory[j] = _inventory[j+1];
            }
            _inventory[3] = Candy{"","",0,""};
            _candy_amount--;
            return true;
        }
    }
    return false;
}

void playRockPaperScissors(Player players[2]) {
    if(players[0].getCandyAmount() == 0 || players[1].getCandyAmount() == 0) {
        cout << "Not enough candy!" << endl;
    }
    string candy_name_1, candy_name_2;
    char player1_choice, player2_choice, r, p, s;


    cout << "Player 1 Inventory" << endl;
    players[0].printInventory();
    cout << "Player 1: Select candy to bet" << endl;
    cin >> candy_name_1;

    Candy candy_1 = players[0].findCandy(candy_name_1);
    if(candy_1.name.length() == 0) {
        cout << "Invalid selection!" << endl;
        return;
    }
    
    cout << "Player 2 Inventory" << endl;
    players[1].printInventory();
    cout << "Player 2: Select candy to bet" << endl;
    cin >> candy_name_2;

    Candy candy_2 = players[1].findCandy(candy_name_2);
    if(candy_2.name.length() == 0) {
        cout << "Invalid selection!" << endl;
        return;
    }

    cout << "Player 1: Enter r, p, or s" << endl;
    cin >> player1_choice;
    if(player1_choice != 'r' &&  player1_choice != 'p' && player1_choice != 's') {
        cout << "Invalid selection!" << endl;
        return;
    }

    cout << "Player 2: Enter r, p, or s" << endl;
    cin >> player2_choice;
    if(player2_choice != 'r' && player2_choice != 'p' && player2_choice != 's') {
        cout << "Invalid selection!" << endl;
        return;
    }

    if(player1_choice == player2_choice) {
        cout << "Tie! Play again" << endl;
    }
    else if((player1_choice == 'r' && player2_choice == 's' || player1_choice == 'p' && player2_choice == 'r' || player1_choice == 's' && player2_choice == 'p')) {
        cout << "Player 1 has won " << candy_name_2 << " from player 2!" << endl;
        players[0].addCandy(candy_2);
        players[1].removeCandy(candy_name_2);
        cout << "Player 1 Inventory after:" << endl;
        players[0].printInventory();
        cout << "Player 2 Inventory after:" << endl;
        players[1].printInventory();
    }
    else if((player2_choice == 'r' && player1_choice == 's' || player2_choice == 'p' && player1_choice == 'r' || player2_choice == 's' && player1_choice == 'p')) {
        cout << "Player 2 has won " << candy_name_1 << " from player 1!" << endl;
        players[0].addCandy(candy_1);
        players[1].removeCandy(candy_name_1);
        cout << "Player 1 Inventory after:" << endl;
        players[0].printInventory();
        cout << "Player 2 Inventory after:" << endl;
        players[1].printInventory();
    }
}





