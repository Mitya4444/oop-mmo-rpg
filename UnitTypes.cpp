#include "UnitTypes.h"

Infantry::Infantry(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Unit(health, armor, attack, x, y) {}

Swordsman::Swordsman(int x, int y)
    : Swordsman(Health(100), Armor(5), Attack(12), x, y) {}

Swordsman::Swordsman(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Infantry(health, armor, attack, x, y) {}

Unit* Swordsman::clone() const {
    return new Swordsman(health, armor, attack, x, y);
}

std::string Swordsman::getType() const {
    return "Swordsman";
}

Spearman::Spearman(int x, int y)
    : Spearman(Health(90), Armor(4), Attack(10), x, y) {}

Spearman::Spearman(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Infantry(health, armor, attack, x, y) {}

Unit* Spearman::clone() const {
    return new Spearman(health, armor, attack, x, y);
}

std::string Spearman::getType() const {
    return "Spearman";
}

Archer::Archer(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Unit(health, armor, attack, x, y) {}

LightArcher::LightArcher(int x, int y)
    : LightArcher(Health(60), Armor(1), Attack(14), x, y) {}

LightArcher::LightArcher(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Archer(health, armor, attack, x, y) {}

Unit* LightArcher::clone() const {
    return new LightArcher(health, armor, attack, x, y);
}

std::string LightArcher::getType() const {
    return "LightArcher";
}

HeavyArcher::HeavyArcher(int x, int y)
    : HeavyArcher(Health(70), Armor(3), Attack(16), x, y) {}

HeavyArcher::HeavyArcher(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Archer(health, armor, attack, x, y) {}

Unit* HeavyArcher::clone() const {
    return new HeavyArcher(health, armor, attack, x, y);
}

std::string HeavyArcher::getType() const {
    return "HeavyArcher";
}

Cavalry::Cavalry(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Unit(health, armor, attack, x, y) {}

Cataphract::Cataphract(int x, int y)
    : Cataphract(Health(120), Armor(8), Attack(15), x, y) {}

Cataphract::Cataphract(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Cavalry(health, armor, attack, x, y) {}

Unit* Cataphract::clone() const {
    return new Cataphract(health, armor, attack, x, y);
}

std::string Cataphract::getType() const {
    return "Cataphract";
}

HorseArcher::HorseArcher(int x, int y)
    : HorseArcher(Health(80), Armor(2), Attack(13), x, y) {}

HorseArcher::HorseArcher(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : Cavalry(health, armor, attack, x, y) {}

Unit* HorseArcher::clone() const {
    return new HorseArcher(health, armor, attack, x, y);
}

std::string HorseArcher::getType() const {
    return "HorseArcher";
}