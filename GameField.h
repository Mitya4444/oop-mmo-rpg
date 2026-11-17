#pragma once

#include <vector>

#include "Unit.h"

class UnitFactory;
enum class UnitKind;

class GameFieldIterator;

class GameField {
public:
    GameField(int width, int height, int maxUnits);
    GameField(const GameField& other);
    GameField& operator=(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;
    ~GameField();

    bool addUnit(const UnitFactory& factory, UnitKind kind, int x, int y);
    bool removeUnit(int x, int y);
    Unit* getUnit(int x, int y);
    const Unit* getUnit(int x, int y) const;
    int size() const;
    bool empty() const;
    void clear();
    int getWidth() const;
    int getHeight() const;
    int getMaxUnits() const;

    GameFieldIterator begin();
    GameFieldIterator end();

private:
    friend class GameFieldIterator;
    bool insideBounds(int x, int y) const;
    int width;
    int height;
    int maxUnits;
    int unitCount;
    std::vector<std::vector<Unit*>> cells;
};

class GameFieldIterator {
public:
    GameFieldIterator(GameField* field, int x, int y);

    Unit* operator*() const;
    GameFieldIterator& operator++();
    bool operator!=(const GameFieldIterator& other) const;

private:
    friend class GameField;
    GameField* field;
    int x;
    int y;
    void skipEmpty();
};