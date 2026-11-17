#pragma once

class Health {
public:
    explicit Health(int value);
    int getValue() const;
    void decrease(int amount);
    void increase(int amount);
    bool isZero() const;
private:
    int value;
};

class Armor {
public:
    explicit Armor(int value);
    Armor& operator=(const Armor&) = delete;
    int getValue() const;
    int reduceDamage(int damage) const;
private:
    int value;
};

class Attack {
public:
    explicit Attack(int value);
    Attack& operator=(const Attack&) = delete;
    int getValue() const;
    int calculateDamage(const Armor& targetArmor) const;
private:
    int value;
};