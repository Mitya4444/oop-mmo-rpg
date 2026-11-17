#pragma once

#include <string>

#include "Unit.h"

enum class UnitKind {
    Swordsman,
    Spearman,
    LightArcher,
    HeavyArcher,
    Cataphract,
    HorseArcher
};

class Infantry : public Unit {
protected:
    Infantry(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class Swordsman : public Infantry {
public:
    Swordsman(int x, int y);
    Unit* clone() const override;
    std::string getType() const override;
private:
    Swordsman(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class Spearman : public Infantry {
public:
    Spearman(int x, int y);
    Unit* clone() const override;
    std::string getType() const override;
private:
    Spearman(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class Archer : public Unit {
protected:
    Archer(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class LightArcher : public Archer {
public:
    LightArcher(int x, int y);
    Unit* clone() const override;
    std::string getType() const override;
private:
    LightArcher(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class HeavyArcher : public Archer {
public:
    HeavyArcher(int x, int y);
    Unit* clone() const override;
    std::string getType() const override;
private:
    HeavyArcher(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class Cavalry : public Unit {
protected:
    Cavalry(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class Cataphract : public Cavalry {
public:
    Cataphract(int x, int y);
    Unit* clone() const override;
    std::string getType() const override;
private:
    Cataphract(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};

class HorseArcher : public Cavalry {
public:
    HorseArcher(int x, int y);
    Unit* clone() const override;
    std::string getType() const override;
private:
    HorseArcher(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
};