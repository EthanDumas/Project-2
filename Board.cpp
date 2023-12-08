#include "Board.h"
#include "Player.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    Tile special_tiles[4];
    int special_tiles_asserts[4];
    int hidden_treasures[3];

    for(int i = 0; i < 4; i++){
        special_tiles_position[i] = rand() % 83;
    }

    for(int i = 0; i < 4; i++){
        special_tiles_asserts[i] = rand() % 4;
        int j;
            if(special_tiles_asserts[i] = special_tiles_asserts[i-1]){
                i=i-1;
            }
            else{
                j = special_tiles_asserts[i];
                special_tiles[j];
            }
    }
    assert(special_tiles[0].tile_type == "Shortcut Tile");
    assert(special_tiles[1].tile_type == "Ice Cream Stop Tile");
    assert(special_tiles[2].tile_type == "Gumdrop Forest Tile");
    assert(special_tiles[3].tile_type == "Gingerbread House Tile");
   

    for(int i = 0; i < 4; i++){
        hidden_treasures[i] = rand() % 83;
        if(hidden_treasures[i] == special_tiles_position[i]){
            i = i-1;
        }
    }

    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        if(i == special_tiles_position[0]){
            new_tile = {current_color, special_tiles[0].tile_type};
        }
        else if(i == special_tiles_position[1]){
            new_tile = {current_color, special_tiles[1].tile_type};
        }
        else if(i == special_tiles_position[2]){
            new_tile = {current_color, special_tiles[2].tile_type};
        }
        else if(i == special_tiles_position[3]){
            new_tile = {current_color, special_tiles[3].tile_type};
        }
        else if(i == hidden_treasures[0] || i == hidden_treasures[1] || i == hidden_treasures[2] || i == hidden_treasures[3]){
            new_tile = {current_color, "hidden treasure"};
        }
        else{
            new_tile = {current_color, "regular tile"};
        }
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
    for(int i = 0; i < Bplayers.size(); i++){
        setPlayerPosition(0, i);
    }
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    for(int i = 0; i < Bplayers.size(); i++){
    if (position == Bplayers[i]._player_position)
    {
        cout << i+1;
    }
    else
    {
        cout << " ";
    }
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position, int player)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        Bplayers[player]._player_position = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition(int player) const
{
    return Bplayers[player]._player_position;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

vector<Riddle> _riddles(string riddles){
    string riddle_question;
    string riddle_answer;
    vector<Riddle> riddles_vector;
    ifstream file(riddles);

    if(file.is_open()){
        while(getline(file, riddles)){
        stringstream ssQ(riddles);
        getline(ssQ, riddle_question, '|');
        getline(ssQ, riddle_answer);
        Riddle one_riddle;
        one_riddle.riddle_question = riddle_question;
        one_riddle.riddle_answer = riddle_answer;
        riddles_vector.push_back(one_riddle);
        }
    }
    return riddles_vector;
}

vector<Candy> Board::_candy(string candies){
    string name, description, effect_type, effect_value, candy_type, _price;
    vector<Candy> _candy_vector;
    ifstream file(candies);

    if(file.is_open()){
        while(getline(file, candies)){
            stringstream ssC(candies);
            getline(ssC, name, '|');
            getline(ssC, description, '|');
            getline(ssC, effect_type, '|');
            getline(ssC, effect_value, '|');
            getline(ssC, _price);
            double price = stod(_price);
            Candy one_candy;
            one_candy.name = name;
            one_candy.description = description;
            one_candy.effect_type = effect_type;
            one_candy.effect_value = effect_value;
            one_candy.price = price;
            _candy_vector.push_back(one_candy);
        }
    }
    return _candy_vector;
}


bool Board::movePlayer(int tile_to_move_forward, int player)
{
    tile_to_move_forward = getCardMovement(player);
    int new_player_position = tile_to_move_forward + Bplayers[player]._player_position;
    string riddles;
    string candies;
    string playerAnswer;
    string riddleAnswer;
    int stamina_refill = 0;
    bool riddleSolution = false;
    string candy_name;
    Candy riddle_reward = {"Robber's Repel", "Prevents the holder from being stolen from"};
    

    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    else if(new_player_position == special_tiles_position[0]){
        cout << "Hooray you found a shortcut! Move ahead!" << endl;
        Bplayers[player].setPlayerPosition(new_player_position + 4, player);
        return true;
    }
    else if(new_player_position == special_tiles_position[1]){
        cout << "Welcome to the Ice Cream Shop! Draw another card!" << endl;
        Bplayers[player].movePlayer(getCardMovement(player), player);
    }
    else if(new_player_position == special_tiles_position[2]){
        cout << "Uh oh! You've enter the Gumdrop Forest and lost your way! Move back 4 tiles and lose some gold!" << endl;
        Bplayers[player].setPlayerPosition(new_player_position - 4, player);
        double Amount_gold = Pplayers[player].getGold();
        double Subtract_gold = Amount_gold - (rand() % 10 + 5);
        Pplayers[player].setGold(Subtract_gold);
        return true; 
    }
    else if(new_player_position == special_tiles_position[3]){
        cout << "You've entered the Gingerbread House. You'll be brought back to your previous position and will lose an immunity candy!" << endl;
        Bplayers[player].setPlayerPosition(new_player_position - tile_to_move_forward, player);
        for(int i = 0; i < 12; i++){
           string effect = _candy(candies).at(i).effect_value;
           if(effect == "Immunity"){
                string _name = _candy(candies).at(i).name;
                Pplayers[player].removeCandy(_name);
                Pplayers[player].printInventory();
                return true;
           }
           else{
            return false;
           }
        }
        
        
    }
    else if(new_player_position == hidden_treasures[0] || new_player_position == hidden_treasures[1] || new_player_position == hidden_treasures[2] || new_player_position == hidden_treasures[3]){
        int i = rand() % 20;
        cout << _riddles(riddles).at(i).riddle_question << endl;
        cout << "What is the answer?" << endl;
        cin >> playerAnswer;
        if(playerAnswer == riddleAnswer){
            riddleSolution = true;
            return true;
        }
        return false;
        if(riddleSolution = true){
            cout << "Well done. Recieve your prize." << endl;
            int rewards = rand() % 10;
            if(rewards == 0 || rewards == 1 || rewards == 2){
                int i = rand() % 3;
                if(i = 0){
                    stamina_refill = 10;
                }
                else if(i = 1){
                    stamina_refill = 20;
                }
                else{
                    stamina_refill = 30;
                }
                int playerStamina = Pplayers[player].getStamina();
                int new_playerStamina = playerStamina + stamina_refill;
                if(new_playerStamina > 100){
                    Pplayers[player].setStamina(100);
                }
                else{
                    Pplayers[player].setStamina(new_playerStamina);
                }
            }
            else if(rewards == 3){
                double addedGold = rand() % 40 + 20;
                double playerGold = Pplayers[player].getGold();
                double new_playerGold = playerGold + addedGold;
                if(new_playerGold > 100){
                    Pplayers[player].setGold(100.0);
                }
                else{
                    Pplayers[player].setGold(new_playerGold);
                }

            }
            else if(rewards == 4 || rewards == 5 || rewards == 6){
                int num_candy = Pplayers[player].getCandyAmount();
                if(num_candy > 9){
                    cout << "You have too many candies! Please remove one to fit your reward!" << endl;
                    Pplayers[player].printInventory();
                    cin >> candy_name;
                    Pplayers[player].findCandy(candy_name);
                    Pplayers[player].removeCandy(candy_name);
                    Pplayers[player].addCandy(riddle_reward);
                    Pplayers[player].printInventory();
                }
                else{
                    Pplayers[player].addCandy(riddle_reward);
                    Pplayers[player].printInventory(); 
                }
            }
            else if(rewards == 7 || rewards == 8 || rewards == 9){
                int possible_candy = rand() % 10;
                if(possible_candy == 0 || possible_candy == 1 || possible_candy == 2){
                    int i = rand() % 20;
                    cout << _riddles(riddles).at(i).riddle_question << endl;
                    cout << "What is the answer?" << endl;
                    cin >> playerAnswer;
                        if(playerAnswer == riddleAnswer){
                            riddleSolution = true;
                            return true;
                        }
                        return false;
                        if(riddleSolution = true){
                            cout << "Well done. Recieve your prize." << endl;
                            Pplayers[player].setStamina(100);
                        }
                }
                else{
                    stamina_refill = 50;
                    int preJelly_Stamina = Pplayers[player].getStamina();
                    int postJelly_Stamina = preJelly_Stamina + stamina_refill;
                    if(postJelly_Stamina > 100){
                        Pplayers[player].setStamina(100);
                    }
                    else{
                        Pplayers[player].setStamina(postJelly_Stamina);
                    }
                }
            }
        }
    }
    Bplayers[player]._player_position = new_player_position;
    return true;
}

int Board::getCandyStoreIndex(int board_position) {
    for(int i = 0; i < _candy_store_count; i++) {
        if(_candy_store_position[i] == board_position) {
            return i;
        }
    }
    return -1;
}

Card getCard(int player) {
    string card_name;
    Card card;
    int value = rand() % 10; 
    
    switch(rand() % 3){
        case 0:
        card_name = "Magnificant Magenta Mango \033[;45m";
        card.color = "Magenta";
        if(value == 0){
            card.two = true;
        }
        else{
            card.two = false;
        }
        cout << "You pulled a " << card_name << "!" << endl;
        return card;

        case 1:
        card_name = "Groovy Green Greengage \033[;42m";
        card.color = "Green";
        if(value == 0){
            card.two = true;
        }
        else{
            card.two = false;
        }
        cout << "You pulled a " << card_name << "!" << endl;
        return card;
        
        case 2:
        card_name = "Brilliant Blue Blueberry \033[;44m";
        card.color = "Blue";
        if(value == 0){
            card.two = true;
        }
        else{
            card.two = false;
        }
        cout << "You pulled a " << card_name << "!" << endl;
        return card;
        
        default:
        card_name = "";
        card.color = "";
        card.two = false;
        return card;
    }
}

int getCardMovement(int player){
    Card _card;
    Board players;

    _card = getCard(player);
    if(_card.two == false){
        for(int i = 1; i < 4; i++){
        int possible_move = players.getPlayerPosition(player) + i;
        cout << possible_move;
            if(_card.color == "Magenta"){
                if(possible_move % 3 == 0){
                    return i;
                }
                return 0;
            }
            else if(_card.color == "Green"){
                if(possible_move % 3 == 1){
                    return i;
                }
                return 0;
            }
            else if(_card.color == "Blue"){
                if(possible_move % 3 == 2){
                    return i;
                }
                return 0;
            }
        }
    }
    else if(_card.two == true){
        for(int i = 1; i < 4; i ++){
        int two_possible_move = players.getPlayerPosition(player) + (3 + i);
        cout << two_possible_move;
            if(_card.color == "Magenta"){
                if(two_possible_move % 3 == 0){
                    return i;
                }
                return 0;
            }
            else if(_card.color == "Green"){
                if(two_possible_move % 3 == 1){
                    return i;
                }
                return 0;
            }
            else if(_card.color == "Blue"){
                if(two_possible_move % 3 == 2){
                    return i;
                }
                return 0;
            }
        }
    }      
}






