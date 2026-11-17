#include "GameField.h"

#include <memory>
#include <stdexcept>
#include <utility>

#include "UnitFactory.h"

GameField::GameField(int width, int height, int maxUnits)
    : width(width > 0 ? width : 0),
      height(height > 0 ? height : 0),
      maxUnits(maxUnits > 0 ? maxUnits : 0),
      unitCount(0),
      cells(this->height, std::vector<Unit*>(this->width, nullptr)) {}

GameField::GameField(const GameField& other)
    : width(other.width),
      height(other.height),
      maxUnits(other.maxUnits),
      unitCount(0),
      cells(other.height, std::vector<Unit*>(other.width, nullptr)) {
    try {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (other.cells[y][x] != nullptr) {
                    cells[y][x] = other.cells[y][x]->clone();
                    ++unitCount;
                }
            }
        }
    } catch (...) {
        clear();
        throw;
    }
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        GameField temp(other);
        std::swap(width, temp.width);
        std::swap(height, temp.height);
        std::swap(maxUnits, temp.maxUnits);
        std::swap(unitCount, temp.unitCount);
        std::swap(cells, temp.cells);
    }
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : width(other.width),
      height(other.height),
      maxUnits(other.maxUnits),
      unitCount(other.unitCount),
      cells(std::move(other.cells)) {
    other.width = 0;
    other.height = 0;
    other.maxUnits = 0;
    other.unitCount = 0;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        clear();
        width = other.width;
        height = other.height;
        maxUnits = other.maxUnits;
        unitCount = other.unitCount;
        cells = std::move(other.cells);
        other.width = 0;
        other.height = 0;
        other.maxUnits = 0;
        other.unitCount = 0;
    }
    return *this;
}

GameField::~GameField() {
    clear();
}

bool GameField::addUnit(const UnitFactory& factory, UnitKind kind, int x, int y) {
    if (!insideBounds(x, y) || cells[y][x] != nullptr || unitCount >= maxUnits) {
        return false;
    }
    std::unique_ptr<Unit> unit(factory.createUnit(kind, x, y));
    if (!unit || unit->getX() != x || unit->getY() != y) {
        return false;
    }
    cells[y][x] = unit.release();
    ++unitCount;
    return true;
}

bool GameField::removeUnit(int x, int y) {
    if (!insideBounds(x, y) || cells[y][x] == nullptr) {
        return false;
    }
    delete cells[y][x];
    cells[y][x] = nullptr;
    --unitCount;
    return true;
}

bool GameField::moveUnit(int fromX, int fromY, int toX, int toY) {
    if (!insideBounds(fromX, fromY) || !insideBounds(toX, toY)) {
        return false;
    }
    if (cells[fromY][fromX] == nullptr || cells[toY][toX] != nullptr) {
        return false;
    }
    if (fromX == toX && fromY == toY) {
        return true;
    }
    Unit* unit = cells[fromY][fromX];
    cells[fromY][fromX] = nullptr;
    cells[toY][toX] = unit;
    unit->move(toX, toY);
    return true;
}

bool GameField::damageUnit(int x, int y, int damage) {
    if (!insideBounds(x, y) || cells[y][x] == nullptr) {
        return false;
    }
    cells[y][x]->takeDamage(damage);
    return true;
}

const Unit* GameField::getUnit(int x, int y) const {
    if (!insideBounds(x, y)) {
        return nullptr;
    }
    return cells[y][x];
}

int GameField::size() const {
    return unitCount;
}

bool GameField::empty() const {
    return unitCount == 0;
}

void GameField::clear() {
    for (std::vector<Unit*>& row : cells) {
        for (Unit*& cell : row) {
            delete cell;
            cell = nullptr;
        }
    }
    unitCount = 0;
}

int GameField::getWidth() const {
    return width;
}

int GameField::getHeight() const {
    return height;
}

int GameField::getMaxUnits() const {
    return maxUnits;
}

bool GameField::insideBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

GameField::iterator GameField::begin() {
    iterator it(this, 0, 0);
    it.skipEmpty();
    return it;
}

GameField::iterator GameField::end() {
    return iterator(this, width, height);
}

GameField::const_iterator GameField::begin() const {
    return cbegin();
}

GameField::const_iterator GameField::end() const {
    return cend();
}

GameField::const_iterator GameField::cbegin() const {
    const_iterator it(this, 0, 0);
    it.skipEmpty();
    return it;
}

GameField::const_iterator GameField::cend() const {
    return const_iterator(this, width, height);
}

GameFieldIterator::GameFieldIterator()
    : field(nullptr), x(0), y(0) {}

GameFieldIterator::GameFieldIterator(GameField* field, int x, int y)
    : field(field), x(x), y(y) {}

GameFieldIterator::reference GameFieldIterator::operator*() const {
    if (field == nullptr || y >= field->height || x >= field->width || field->cells[y][x] == nullptr) {
        throw std::out_of_range("GameFieldIterator: dereference of empty cell");
    }
    return *field->cells[y][x];
}

GameFieldIterator::pointer GameFieldIterator::operator->() const {
    return &operator*();
}

GameFieldIterator& GameFieldIterator::operator++() {
    if (field == nullptr || y >= field->height) {
        return *this;
    }
    ++x;
    if (x >= field->width) {
        x = 0;
        ++y;
    }
    skipEmpty();
    return *this;
}

GameFieldIterator GameFieldIterator::operator++(int) {
    GameFieldIterator previous = *this;
    ++(*this);
    return previous;
}

bool GameFieldIterator::operator==(const GameFieldIterator& other) const {
    return field == other.field && x == other.x && y == other.y;
}

bool GameFieldIterator::operator!=(const GameFieldIterator& other) const {
    return !(*this == other);
}

void GameFieldIterator::skipEmpty() {
    if (field == nullptr) {
        return;
    }
    while (y < field->height) {
        while (x < field->width) {
            if (field->cells[y][x] != nullptr) {
                return;
            }
            ++x;
        }
        x = 0;
        ++y;
    }
    x = field->width;
    y = field->height;
}

ConstGameFieldIterator::ConstGameFieldIterator()
    : field(nullptr), x(0), y(0) {}

ConstGameFieldIterator::ConstGameFieldIterator(const GameField* field, int x, int y)
    : field(field), x(x), y(y) {}

ConstGameFieldIterator::reference ConstGameFieldIterator::operator*() const {
    if (field == nullptr || y >= field->height || x >= field->width || field->cells[y][x] == nullptr) {
        throw std::out_of_range("ConstGameFieldIterator: dereference of empty cell");
    }
    return *field->cells[y][x];
}

ConstGameFieldIterator::pointer ConstGameFieldIterator::operator->() const {
    return &operator*();
}

ConstGameFieldIterator& ConstGameFieldIterator::operator++() {
    if (field == nullptr || y >= field->height) {
        return *this;
    }
    ++x;
    if (x >= field->width) {
        x = 0;
        ++y;
    }
    skipEmpty();
    return *this;
}

ConstGameFieldIterator ConstGameFieldIterator::operator++(int) {
    ConstGameFieldIterator previous = *this;
    ++(*this);
    return previous;
}

bool ConstGameFieldIterator::operator==(const ConstGameFieldIterator& other) const {
    return field == other.field && x == other.x && y == other.y;
}

bool ConstGameFieldIterator::operator!=(const ConstGameFieldIterator& other) const {
    return !(*this == other);
}

void ConstGameFieldIterator::skipEmpty() {
    if (field == nullptr) {
        return;
    }
    while (y < field->height) {
        while (x < field->width) {
            if (field->cells[y][x] != nullptr) {
                return;
            }
            ++x;
        }
        x = 0;
        ++y;
    }
    x = field->width;
    y = field->height;
}