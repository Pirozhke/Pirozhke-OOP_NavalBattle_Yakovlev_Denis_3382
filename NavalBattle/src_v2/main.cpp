#include "gameState.h"

int main(){
   Game game;
   GameState client(game);
    while(true){
        char s = 'a';
        while(s != 'y' && s != 'n'){
            std::cout << "Do you want to play Naval Battle (y - yes, n -no)?\n";
            std::cin >> s;
        }
        if(s == 'n'){
            break;
        }

        if(client.try_load() == false){
            client.new_game();
        }
        while(client.play_round()){
            if(client.try_save()){
                client.save("saved_game.txt");
            }
        }
    }
    return 0;
}