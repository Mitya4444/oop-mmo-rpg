#include <stdexcept>

#include "UnitFactory.h"

UnitFactory::~UnitFactory() {}

Unit* InfantryFactory::createUnit(UnitKind kind, int x, int y) const {
    switch (kind) {
    case UnitKind::Swordsman:
        return new Swordsman(x, y);
    case UnitKind::Spearman:
        return new Spearman(x, y);
    default:
        throw std::invalid_argument("InfantryFactory: unsupported unit kind");
    }
}

Unit* ArcherFactory::createUnit(UnitKind kind, int x, int y) const {
    switch (kind) {
    case UnitKind::LightArcher:
        return new LightArcher(x, y);
    case UnitKind::HeavyArcher:
        return new HeavyArcher(x, y);
    default:
        throw std::invalid_argument("ArcherFactory: unsupported unit kind");
    }
}

Unit* CavalryFactory::createUnit(UnitKind kind, int x, int y) const {
    switch (kind) {
    case UnitKind::Cataphract:
        return new Cataphract(x, y);
    case UnitKind::HorseArcher:
        return new HorseArcher(x, y);
    default:
        throw std::invalid_argument("CavalryFactory: unsupported unit kind");
    }
}