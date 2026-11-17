#pragma once

#include <string>

#include "Attributes.h"

class Unit {
public:
    Unit(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
    virtual ~Unit();

    virtual Unit* clone() const = 0;
    virtual std::string getType() const = 0;

    Health getHealth() const;
    Armor getArmor() const;
    Attack getAttack() const;
    int getX() const;
    int getY() const;
    void move(int newX, int newY);
    void takeDamage(int damage);

protected:
    Health health;
    Armor armor;
    Attack attack;
    int x;
    int y;
};