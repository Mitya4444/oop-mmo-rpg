#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

#include "Unit.h"

class UnitFactory;
enum class UnitKind;

class GameFieldIterator;
class ConstGameFieldIterator;

class GameField {
public:
    using iterator = GameFieldIterator;
    using const_iterator = ConstGameFieldIterator;

    GameField(int width, int height, int maxUnits);
    GameField(const GameField& other);
    GameField& operator=(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;
    ~GameField();

    bool addUnit(const UnitFactory& factory, UnitKind kind, int x, int y);
    bool removeUnit(int x, int y);
    bool moveUnit(int fromX, int fromY, int toX, int toY);
    bool damageUnit(int x, int y, int damage);
    const Unit* getUnit(int x, int y) const;
    int size() const;
    bool empty() const;
    void clear();
    int getWidth() const;
    int getHeight() const;
    int getMaxUnits() const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    friend class GameFieldIterator;
    friend class ConstGameFieldIterator;
    bool insideBounds(int x, int y) const;
    int width;
    int height;
    int maxUnits;
    int unitCount;
    std::vector<std::vector<Unit*>> cells;
};

class GameFieldIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Unit;
    using difference_type = std::ptrdiff_t;
    using pointer = Unit*;
    using reference = Unit&;

    GameFieldIterator();
    reference operator*() const;
    pointer operator->() const;
    GameFieldIterator& operator++();
    GameFieldIterator operator++(int);
    bool operator==(const GameFieldIterator& other) const;
    bool operator!=(const GameFieldIterator& other) const;

private:
    friend class GameField;
    GameFieldIterator(GameField* field, int x, int y);
    void skipEmpty();
    GameField* field;
    int x;
    int y;
};

class ConstGameFieldIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Unit;
    using difference_type = std::ptrdiff_t;
    using pointer = const Unit*;
    using reference = const Unit&;

    ConstGameFieldIterator();
    reference operator*() const;
    pointer operator->() const;
    ConstGameFieldIterator& operator++();
    ConstGameFieldIterator operator++(int);
    bool operator==(const ConstGameFieldIterator& other) const;
    bool operator!=(const ConstGameFieldIterator& other) const;

private:
    friend class GameField;
    ConstGameFieldIterator(const GameField* field, int x, int y);
    void skipEmpty();
    const GameField* field;
    int x;
    int y;
};