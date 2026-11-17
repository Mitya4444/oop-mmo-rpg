#include "Unit.h"

Unit::Unit(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
    : health(health), armor(armor), attack(attack), x(x), y(y) {}

Unit::~Unit() {}

Health Unit::getHealth() const {
    return health;
}

Armor Unit::getArmor() const {
    return armor;
}

Attack Unit::getAttack() const {
    return attack;
}

int Unit::getX() const {
    return x;
}

int Unit::getY() const {
    return y;
}

void Unit::move(int newX, int newY) {
    x = newX;
    y = newY;
}

void Unit::takeDamage(int damage) {
    health.decrease(armor.reduceDamage(damage));
}