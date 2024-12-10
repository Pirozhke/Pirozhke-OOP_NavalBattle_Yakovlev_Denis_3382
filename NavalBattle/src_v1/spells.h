#include <iostream>
class Spell{
public:
    virtual void cast_spell() = 0;
};
class DoubleDamage: public Spell{
public:
    void cast_spell();
};
class Scan: public Spell{
public:
    void cast_spell(size_t x, size_t y);
};
class Bombing: public Spell{
public:
    void cast_spell();
};