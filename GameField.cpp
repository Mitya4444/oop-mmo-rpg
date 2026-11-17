#include "GameField.h"

#include "UnitFactory.h"

#include <utility>

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
    Unit* unit = factory.createUnit(kind, x, y);
    if (unit == nullptr) {
        return false;
    }
    cells[y][x] = unit;
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

Unit* GameField::getUnit(int x, int y) {
    if (!insideBounds(x, y)) {
        return nullptr;
    }
    return cells[y][x];
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

GameFieldIterator GameField::begin() {
    GameFieldIterator it(this, 0, 0);
    it.skipEmpty();
    return it;
}

GameFieldIterator GameField::end() {
    return GameFieldIterator(this, width, height);
}

GameFieldIterator::GameFieldIterator(GameField* field, int x, int y)
    : field(field), x(x), y(y) {}

Unit* GameFieldIterator::operator*() const {
    return field->cells[y][x];
}

GameFieldIterator& GameFieldIterator::operator++() {
    ++x;
    if (x >= field->width) {
        x = 0;
        ++y;
    }
    skipEmpty();
    return *this;
}

bool GameFieldIterator::operator!=(const GameFieldIterator& other) const {
    return field != other.field || x != other.x || y != other.y;
}

void GameFieldIterator::skipEmpty() {
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