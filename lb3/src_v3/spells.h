#pragma once
#include <iostream>
#include "field.h"
#include "shipManager.h"

class Spell{
    public:
        virtual void cast_spell(Field* field, ShipManager* ship_manager) = 0;
};

class DoubleDamage: public Spell{
    public:
        void cast_spell(Field* field, ShipManager* ship_manager) override;
};

class Scan: public Spell{
    public:
        void cast_spell(Field* field, ShipManager* ship_manager) override;
};

class Bombing: public Spell{
    public:
        void cast_spell(Field* field, ShipManager* ship_manager) override;
};