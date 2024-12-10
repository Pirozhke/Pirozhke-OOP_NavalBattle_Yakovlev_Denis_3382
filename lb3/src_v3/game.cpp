#include "game.h"
#include "gameLoadException.h"

Game::Game(){
    /*count_of_ships = 4;
    field_height = 10;
    field_width = 10;*/

    count_of_ships = 2;
    field_height = 4;
    field_width = 4;
}

void Game::new_game(){
    std::cout << "Starting new game:\n";
    std::vector<size_t> list_of_ships;
    list_of_ships.push_back(2);
    list_of_ships.push_back(1);
    player_ship_manager = ShipManager(count_of_ships, list_of_ships);
    bot_ship_manager = ShipManager(count_of_ships, list_of_ships);

    player_field = Field(field_height, field_width);
    bot_field = Field(field_height, field_width);

    player_spells_manager = SpellsManager();

    std::vector<Ship> player_ships_array = player_ship_manager.getShipsArray();
    size_t i = 0, x, y;
    bool is_horizontal;

    std::ofstream file("setting_player.log");
    while(i < count_of_ships){
        std::cout << "How to setup ship with length = " << player_ships_array[i].size() << "?\n";
        std::cout << " x and y coordinates: ";
        std::cin >> x >> y;

        char s = 'a';
        while(s != 'y' && s != 'n'){
            std::cout << "Is ship horisontal (y - yes, n - no): ";
            std::cin >> s;
        }
        if(s == 'y'){
            is_horizontal = true;
        } else{
            is_horizontal = false;
        }

        try{
            player_field.setShip(player_ships_array[i], x, y, is_horizontal);
        }
        catch(WrongSettingShip& exception){
            std::cout << exception.what();
            std::cout << "Try again\n";
            continue;
        }

        file << x << "\n";
        file << y << "\n";
        file << (size_t)is_horizontal << "\n";

        i++;
    }
    file.close();

    std::cout << "Creating bot's field...\n";
    std::vector<Ship> bot_ships_array = bot_ship_manager.getShipsArray();
    i = 0;
    std::ofstream file1("setting_bot.log");
    while(i < count_of_ships){
        x = rand()%field_width;
        y = rand()%field_height;
        bool is_horizontal = rand()%2;
        try{
            bot_field.setShip(bot_ships_array[i], x, y, is_horizontal);
        }
        catch(WrongSettingShip& exception){
            continue;
        }
        file1 << x << "\n";
        file1 << y << "\n";
        file1 << (size_t)is_horizontal << "\n";
        i++;
    }
    file1.close();
    std::cout << "Done.\n";
}

bool isChanged(std::vector<bool> a, std::vector<bool> b){
    for(size_t i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return true;
        }
    }
    return false;
}

bool isVictory(ShipManager ship_manager){
    for(size_t i = 0; i < ship_manager.getShipsArray().size(); i++){
        if(ship_manager.getShipsArray()[i].isShipDestroyed() == false){
            return false;
        }
    }
    return true;
}

bool Game::play_round(){
    try{
        player_spells_manager.cast_spell(&bot_field, &bot_ship_manager);
    }
    catch(CastHaventSpell& exception){
        std::cout << exception.what();
    }

    try{
        std::cout << "Enter the coordinates of the attack " << "(damage = " << bot_ship_manager.getDamageScale() <<"):\n";
        size_t x, y;
        std::cin >> x >> y;
        std::cout << '\n';

        std::vector<bool> start_array, finish_array;
        for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
            start_array.push_back(bot_ship_manager.getShipsArray()[i].isShipDestroyed());
        }

        bot_field.attack(x, y, bot_ship_manager.getDamageScale());
        bot_ship_manager.setDamageScale(1);

        for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
            finish_array.push_back(bot_ship_manager.getShipsArray()[i].isShipDestroyed());
        }
        if(isChanged(start_array, finish_array)){
            size_t n = rand();
            if(n%3 == 1){
                player_spells_manager.add_spell(new Scan);
            } else if(n%3 == 2){
                player_spells_manager.add_spell(new Bombing);
            } else{
                player_spells_manager.add_spell(new DoubleDamage);
            }
        }

        std::cout<< "\n Bot's Field: \n";
        bot_field.printField();
    }
    catch(OutOfRangeAttack& exception){
        std::cout << exception.what();
    }

    if(isVictory(bot_ship_manager)){
        std::cout << "It is victory!\n";
        play_next_level();
        return true;
    }

//------------------------------------------------------------- Bot's attack -----------------------------------------------------------------------------------------------------------------

    player_field.attack(rand()%field_width, rand()%field_height, player_ship_manager.getDamageScale());

    std::cout<< "\n Your Field: \n";
    player_field.printField();
    
    if(isVictory(player_ship_manager)){
        std::cout << "It is defeat.\n";
        return false;
    } else{
        return true;
    }
}

void Game::play_next_level(){
    std::vector<size_t> list_of_ships = {2, 1};
    std::cout << "Creating bot's field...\n";
    bot_field = Field(field_height, field_width);
    bot_ship_manager = ShipManager(count_of_ships, list_of_ships);
    std::vector<Ship> bot_ships_array = bot_ship_manager.getShipsArray();
    size_t i = 0;
    std::ofstream file1("setting_bot.log");
    while(i < count_of_ships){
        size_t x = rand()%field_width;
        size_t y = rand()%field_height;
        bool is_horizontal = rand()%2;
        try{
            bot_field.setShip(bot_ships_array[i], x, y, is_horizontal);
        }
        catch(WrongSettingShip& exception){
            continue;
        }
        file1 << x << "\n";
        file1 << y << "\n";
        file1 << (size_t)is_horizontal << "\n";
        i++;
    }
    file1.close();
    std::cout << "Done.\n";
    play_round();
}

void Game::save(const std::string& filename){
    std::ofstream file(filename);

    file << player_ship_manager.getDamageScale() << "\n";
    file << player_ship_manager.getShipsArray().size() << "\n";
    for(size_t i = 0; i < player_ship_manager.getShipsArray().size(); i++){
        file << player_ship_manager.getShipsArray()[i].size() << "\n";
        for(size_t j = 0; j < player_ship_manager.getShipsArray()[i].size(); j++){
            file << player_ship_manager.getShipsArray()[i].getArray()[j]->getHealth() << "\n";
        }
    }

    file << bot_ship_manager.getDamageScale() << "\n";
    for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
        file << bot_ship_manager.getShipsArray()[i].size() << "\n";
        for(size_t j = 0; j < bot_ship_manager.getShipsArray()[i].size(); j++){
            file << bot_ship_manager.getShipsArray()[i].getArray()[j]->getHealth() << "\n";
        }
    }

    file << field_height << "\n";
    file << field_width << "\n";
    std::vector<std::pair<size_t, size_t>> visiable_cords;
    for(size_t i = 0; i < field_height; i++){
        for(size_t j = 0; j < field_width; j++){
            if(!player_field.getFieldArray()[i][j].isHidden()){
                visiable_cords.push_back(std::make_pair(i, j));
            }
        }
    }
    file << visiable_cords.size() << "\n";
    for(size_t i = 0; i < visiable_cords.size(); i++){
        file << visiable_cords[i].first << "\n";
        file << visiable_cords[i].second << "\n";
    }
    visiable_cords.clear();

    for(size_t i = 0; i < field_height; i++){
        for(size_t j = 0; j < field_width; j++){
            if(!bot_field.getFieldArray()[i][j].isHidden()){
                visiable_cords.push_back(std::make_pair(i, j));
            }
        }
    }
    file << visiable_cords.size() << "\n";
    for(size_t i = 0; i < visiable_cords.size(); i++){
        file << visiable_cords[i].first << "\n";
        file << visiable_cords[i].second << "\n";
    }

    file << player_spells_manager.size() << "\n";
    for(size_t i = 0; i < player_spells_manager.size(); i++){
        file << player_spells_manager.array()[i] << "\n";
    }
    
    file.close();
}

void Game::load(const std::string& filename){
    std::cout << "Loading...\n";
    std::ifstream file(filename);

    if(!file.is_open()){
        std::string exception = "Loading game is broken: wrong opening file\n";
        throw BrokenLoadingFile(exception);
    }

//------------------------------------------------------ Player ship manager --------------------------------------------------------------------------

    size_t damage_scale = -1;
    file >> damage_scale;
    if(damage_scale != 1 && damage_scale != 2){
        std::string exception = "Loading game is broken: player damage scale is not 1 or 2\n";
        throw BrokenLoadingFile(exception);
    }

    size_t size = -1;
    file >> size;
    if(size < 1 || size > 10){
        std::string exception = "Loading game is broken: count of ships is not in [1, 10]\n";
        throw BrokenLoadingFile(exception);
    }

    std::vector <size_t> ships;
    std::vector <std::vector <size_t>> damage;
    for(size_t i = 0; i < size; i++){
        size_t ship_size = -1;
        file >> ship_size;
        if(ship_size < 1 || ship_size > 4){
            std::string exception = "Loading game is broken: ship's size is not in [1, 4]\n";
            throw BrokenLoadingFile(exception);
        }
        ships.push_back(ship_size);

        std::vector <size_t> damage_buffer;
        for(size_t j = 0; j < ship_size; j++){
            size_t buffer = -1;
            file >> buffer;
            if(buffer > 2){
                std::string exception = "Loading game is broken: health of ship cell is not in [0, 2]\n";
                throw BrokenLoadingFile(exception);
            }
            damage_buffer.push_back(2 - buffer);
        }
        damage.push_back(damage_buffer);
    }

    player_ship_manager = ShipManager(size, ships);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < player_ship_manager.getShipsArray()[i].size(); j++){
            player_ship_manager.getShipsArray()[i].getArray()[j]->attack(damage[i][j]);
        }
    }

//------------------------------------------------------ Bot ship manager --------------------------------------------------------------------------

    damage_scale = -1;
    file >> damage_scale;
    if(damage_scale != 1 && damage_scale != 2){
        std::string exception = "Loading game is broken: player damage scale is not 1 or 2\n";
        throw BrokenLoadingFile(exception);
    }

    ships.clear();
    damage.clear();
    for(size_t i = 0; i < size; i++){
        size_t ship_size = -1;
        file >> ship_size;
        if(ship_size < 1 || ship_size > 4){
            std::string exception = "Loading game is broken: ship's size is not in [1, 4]\n";
            throw BrokenLoadingFile(exception);
        }
        ships.push_back(ship_size);

        std::vector <size_t> damage_buffer;
        for(size_t j = 0; j < ship_size; j++){
            size_t buffer = -1;
            file >> buffer;
            if(buffer > 2){
                std::string exception = "Loading game is broken: health of ship cell is not in [0, 2]\n";
                throw BrokenLoadingFile(exception);
            }
            damage_buffer.push_back(2 - buffer);
        }
        damage.push_back(damage_buffer);
    }
    
    bot_ship_manager = ShipManager(size, ships);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < bot_ship_manager.getShipsArray()[i].size(); j++){
            bot_ship_manager.getShipsArray()[i].getArray()[j]->attack(damage[i][j]);
        }
    }

//------------------------------------------------------ Player field --------------------------------------------------------------------------

    size_t height = -1, width = -1;
    file >> height >> width;
    if(height < 1 || height > 15 || width < 1 || height > 15){
        std::string exception = "Loading game is broken: field size is not in [1, 15]\n";
        throw BrokenLoadingFile(exception);
    }
    player_field = Field(height, width);

    size = -1;
    file >> size;
    if(size < 1 || size > height*width){
        std::string exception = "Loading game is broken: count of visiable cells is not in field size\n";
        throw BrokenLoadingFile(exception);
    }
    std::vector<std::pair<size_t, size_t>> player_visiable_cords;
    for(size_t i = 0; i < size; i++){
        size_t x = -1, y = -1;
        file >> y >> x;
        if(y >= height || x >= width){
            std::string exception = "Loading game is broken: visiable coordinate is not in field size\n";
            throw BrokenLoadingFile(exception);
        }
        player_visiable_cords.push_back(std::make_pair(y, x));
    }

//------------------------------------------------------ Bot field ------------------------------------------------------------------------------------------

    bot_field = Field(height, width);

    size = -1;
    file >> size;
    if(size < 1 || size > height*width){
        std::string exception = "Loading game is broken: count of visiable cells is not in field size\n";
        throw BrokenLoadingFile(exception);
    }
    std::vector<std::pair<size_t, size_t>> bot_visiable_cords;
    for(size_t i = 0; i < size; i++){
        size_t x = -1, y = -1;
        file >> y >> x;
        if(y >= height || x >= width){
            std::string exception = "Loading game is broken: visiable coordinate is not in field size\n";
            throw BrokenLoadingFile(exception);
        }
        bot_visiable_cords.push_back(std::make_pair(y, x));
    }

//------------------------------------------------------ Player spells manager ------------------------------------------------------------------------------------------

    while(player_spells_manager.array().size() != 0){
        player_spells_manager.pop_spell();
    }

    size = -1;
    file >> size;
    if(size > 100){
        std::string exception = "Loading game is broken: count of spells too much\n";
        throw BrokenLoadingFile(exception);
    }
    std::vector <size_t> spells;
    for(size_t i = 0; i < size; i++){
        size_t spell = -1;
        file >> spell;
        if(spell > 2){
            std::string exception = "Loading game is broken: number of spell is not in [0, 2]\n";
            throw BrokenLoadingFile(exception);
        }
        spells.push_back(spell);
    }
    player_spells_manager.create(spells);

    file.close();

//------------------------------------------------------ Setup ships ------------------------------------------------------------------------------------------

    std::ifstream file1("setting_player.log");
    if(!file1.is_open()){
        std::string exception = "Loading game is broken: wrong opening file\n";
        throw BrokenLoadingFile(exception);
    }

    for(size_t i = 0; i < player_ship_manager.getShipsArray().size(); i++){
        size_t x = -1, y = -1, orient = -1;
        file1 >> x >> y >> orient;
        if(x >= width || y >= height || (orient != 0 && orient != 1)){
            std::string exception = "Loading game is broken: wrong setting player's ship\n";
            throw BrokenLoadingFile(exception);
        }
        player_field.setShip(player_ship_manager.getShipsArray()[i], x, y, (bool)orient);
    }
    file1.close();

    std::ifstream file2("setting_bot.log");
    if(!file2.is_open()){
        std::string exception = "Loading game is broken: wrong opening file\n";
        throw BrokenLoadingFile(exception);
    }

    for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
        size_t x = -1, y = -1, orient = -1;
        file2 >> x >> y >> orient;
        if(x >= width || y >= height || (orient != 0 && orient != 1)){
            std::string exception = "Loading game is broken: wrong setting bot's ship\n";
            throw BrokenLoadingFile(exception);
        }
        bot_field.setShip(bot_ship_manager.getShipsArray()[i], x, y, (bool)orient);
    }
    file2.close();
        
//------------------------------------------------------ Setup visiable coordinates ------------------------------------------------------------------------------------------

    player_field.reveal(player_visiable_cords);

    bot_field.reveal(bot_visiable_cords);

    std::cout << "Game was loaded.\n ";
    std::cout<< "\n Bot's Field: \n";
    bot_field.printField();
    std::cout<< "\n Your Field: \n";
    player_field.printField();
}