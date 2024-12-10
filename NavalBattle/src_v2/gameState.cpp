#include "gameState.h"

GameState::GameState(Game game): game(game){
    state = GameStates::Loaded;
}

bool GameState::try_load(){
    char s = 'a';
    std::cout << "Do you want to load the game or start new game(y - yes, load; n - no, start new game)?\n";
    while(s != 'y' && s != 'n'){
        std::cin >> s;
    }
    if(s == 'y'){
        try{
            load("saved_game.txt");
        }
        catch(NoSaves& exception){
            std::cout << exception.what();
            return false;
        }
        return true;
    } else{
        return false;
    }
}

bool GameState::try_save(){
    char s = 'a';
    std::cout << "Do you want to save the game (y - yes, n - no)?\n";
    while(s != 'y' && s != 'n'){
        std::cin >> s;
    }
    if(s == 'y'){
        save("saved_game.txt");
        return true;
    } else{
        return false;
    }
}

void GameState::new_game(){
    game.new_game();
}

bool GameState::play_round(){
    return game.play_round();
}

void GameState::save(const std::string& filename){
    game.save(filename);
}

void GameState::load(const std::string& filename){
    /*char s[100];
    std::vector<std::vector<std::string>> save;
    std::vector<std::string> local;
    std::ifstream file(filename);
    
    while(file.getline(s, 100)){
        char* pch = strtok(s, " ");
        while(pch != NULL){
            local.push_back(pch);
            pch = strtok (NULL, " ");
        }
        save.push_back(local);
        local.clear();
    }

    file.close();*/

    game.load(filename);
}

std::ostream& operator << (std::ostream &os, const GameState &game_state){

}

std::istream& operator >> (std::istream& in, GameState &game_state){

}