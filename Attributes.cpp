#include <limits>
#include <stdexcept>

#include "Attributes.h"

Health::Health(int value) : value(value < 0 ? 0 : value) {}

int Health::getValue() const {
    return value;
}

void Health::decrease(int amount) {
    if (amount > 0) {
        value -= amount;
        if (value < 0) {
            value = 0;
        }
    }
}

void Health::increase(int amount) {
    if (amount > 0) {
        if (amount > std::numeric_limits<int>::max() - value) {
            throw std::overflow_error("Health::increase");
        }
        value += amount;
    }
}

bool Health::isZero() const {
    return value == 0;
}

Armor::Armor(int value) : value(value < 0 ? 0 : value) {}

int Armor::getValue() const {
    return value;
}

int Armor::reduceDamage(int damage) const {
    if (damage <= value) {
        return 0;
    }
    return damage - value;
}

Attack::Attack(int value) : value(value < 0 ? 0 : value) {}

int Attack::getValue() const {
    return value;
}

int Attack::calculateDamage(const Armor& targetArmor) const {
    return targetArmor.reduceDamage(value);
}