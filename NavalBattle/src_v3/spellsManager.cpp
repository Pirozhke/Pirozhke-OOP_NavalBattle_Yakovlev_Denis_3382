#include "spellsManager.h"

SpellsManager::SpellsManager(){
    size_t n = rand();
    if(n%3 == 1){
        add_spell(new Scan);
        if(n%2 == 1){
            add_spell(new Bombing);
            add_spell(new DoubleDamage);
        } else{
            add_spell(new DoubleDamage);
            add_spell(new Bombing);
        }
    } else if(n%3 == 2){
        add_spell(new Bombing);
        if(n%2 == 1){
            add_spell(new Scan);
            add_spell(new DoubleDamage);
        } else{
            add_spell(new DoubleDamage);
            add_spell(new Scan);
        }
    } else{
        add_spell(new DoubleDamage);
        if(n%2 == 1){
            add_spell(new Bombing);
            add_spell(new Scan);
        } else{
            add_spell(new Scan);
            add_spell(new Bombing);
        }
    }
}

void SpellsManager::cast_spell(Field* field, ShipManager* ship_manager){
    char flag = '1';
    while(flag != 'n' && flag != 'y'){
        std::cout << "Do you want to use the ability when attacking? (y - yes/ n - no)\n";
        std::cin >> flag;
        std::cout << '\n';
    }

    if(flag == 'y' && !spells_queue.empty()){
        spells_queue.front()->cast_spell(field, ship_manager);
        spells_queue.pop();
    } else if(flag == 'y' && spells_queue.empty()){
        throw CastHaventSpell();
    }
}

void SpellsManager::add_spell(Spell* new_spell){
    spells_queue.push(new_spell);
}

void SpellsManager::pop_spell(){
    spells_queue.pop();
}

size_t SpellsManager::size(){
    return spells_queue.size();
}

std::vector<size_t> SpellsManager::array(){
    std::vector<size_t> array;
    size_t size = this->size();
    for(size_t i = 0; i < size; i++){
        Spell* spell = spells_queue.front();
        spells_queue.pop();
        if(typeid(*spell) == typeid(DoubleDamage)){
            array.push_back(0);
        } else if(typeid(*spell) == typeid(Scan)){
            array.push_back(1);
        } else{
            array.push_back(2);
        }
    }
    create(array);
    return array;
}

void SpellsManager::create(std::vector <size_t> array){
    for(size_t i = 0; i < array.size(); i++){
        Spell* spell;
        if(array[i] == 0){
            spell = new DoubleDamage;
        } else if(array[i] == 1){
            spell = new Scan;
        } else{
            spell = new Bombing;
        }
        spells_queue.push(spell);
    }
}

SpellsManager::~SpellsManager(){
    while(!spells_queue.empty()){
        spells_queue.pop();
    }
}