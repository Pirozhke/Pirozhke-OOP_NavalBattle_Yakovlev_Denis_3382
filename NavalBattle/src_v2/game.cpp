#include "game.h"

Game::Game(){
    /*count_of_ships = 4;
    field_height = 10;
    field_width = 10;*/

    count_of_ships = 2;
    field_height = 4;
    field_width = 4;
}

void Game::new_game(){
    std::vector<size_t> list_of_ships;
    list_of_ships.push_back(2);
    list_of_ships.push_back(1);
    player_ship_manager = ShipManager(count_of_ships, list_of_ships);
    bot_ship_manager = ShipManager(count_of_ships, list_of_ships);

    player_field = Field(field_height, field_width);
    bot_field = Field(field_height, field_width);

    player_spells_manager = SpellsManager();

    std::vector<Ship*> player_ships_array = player_ship_manager.getShipsArray();
    for(size_t q = 0; q < player_ships_array.size(); q++){
        for(size_t w = 0; w < player_ships_array[q]->size(); w++){
            std::cout << player_ships_array[q]->getArray()[w]->getHealth() << " ";
        }
        std::cout << "\n";
    }
    size_t i = 0, x, y;
    bool is_horizontal;

    std::ofstream file("setting_player.log");
    while(i < count_of_ships){
        std::cout << "How to setup ship with length = " << player_ships_array[i]->size() << "?\n";
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
        
        for(size_t I = 0; I < field_height; I++){
            for(size_t J = 0; J < field_height; J++){
                player_field.attack(I, J, 1);
            }
        }
        player_field.printField();

        try{
            player_field.setShip(*(player_ships_array[i]), x, y, is_horizontal);
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
    std::vector<Ship*> bot_ships_array = bot_ship_manager.getShipsArray();
    i = 0;
    std::ofstream file1("setting_bot.log");
    while(i < count_of_ships){
        x = rand()%field_width;
        y = rand()%field_height;
        bool is_horizontal = rand()%2;
        try{
            bot_field.setShip(*bot_ships_array[i], x, y, is_horizontal);
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
        if(ship_manager.getShipsArray()[i]->isShipDestroyed() == false){
            return false;
        }
    }
    return true;
}

bool Game::play_round(){
    try{
        player_spells_manager.cast_spell(&bot_field, &bot_ship_manager);

        std::cout << "Enter the coordinates of the attack " << "(damage = " << player_ship_manager.getDamageScale() <<"):\n";
        size_t x, y;
        std::cin >> x >> y;
        std::cout << '\n';

        std::vector<bool> start_array, finish_array;
        for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
            start_array.push_back(bot_ship_manager.getShipsArray()[i]->isShipDestroyed());
        }

        bot_field.attack(x, y, bot_ship_manager.getDamageScale());
        bot_ship_manager.setDamageScale(1);

        for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
            finish_array.push_back(bot_ship_manager.getShipsArray()[i]->isShipDestroyed());
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
    catch(CastHaventSpell& exception){
        std::cout << exception.what();
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
    std::vector<Ship*> bot_ships_array = bot_ship_manager.getShipsArray();
    size_t i = 0;
    while(i < count_of_ships){
        size_t x = rand()%field_width;
        size_t y = rand()%field_height;
        bool is_horizontal = rand()%2;
        try{
            bot_field.setShip(*bot_ships_array[i], x, y, is_horizontal);
        }
        catch(WrongSettingShip& exception){
            continue;
        }
        i++;
    }
    std::cout << "Done.\n";
    play_round();
}

void Game::save(const std::string& filename){
    std::ofstream file(filename);

    file << player_ship_manager.getDamageScale() << "\n";
    file << player_ship_manager.getShipsArray().size() << "\n";
    for(size_t i = 0; i < player_ship_manager.getShipsArray().size(); i++){
        file << player_ship_manager.getShipsArray()[i]->size() << "\n";
        for(size_t j = 0; j < player_ship_manager.getShipsArray()[i]->size(); j++){
            file << player_ship_manager.getShipsArray()[i]->getArray()[j]->getHealth() << "\n";
        }
    }

    file << bot_ship_manager.getDamageScale() << "\n";
    for(size_t i = 0; i < bot_ship_manager.getShipsArray().size(); i++){
        file << bot_ship_manager.getShipsArray()[i]->size() << "\n";
        for(size_t j = 0; j < bot_ship_manager.getShipsArray()[i]->size(); j++){
            file << bot_ship_manager.getShipsArray()[i]->getArray()[j]->getHealth() << "\n";
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
    std::ifstream file(filename);

    size_t damage_scale, size_of_ship;

    file >> damage_scale;
    file >> count_of_ships;
    for(size_t i = 0; i < count_of_ships; i++){
        file >> size_of_ship;
        for(size_t j = 0; j < player_ship_manager.getShipsArray()[i]->size(); j++){
            //file >> player_ship_manager.getShipsArray()[i]->getArray()[j]->getHealth();
        }
    }

    file.close();
}