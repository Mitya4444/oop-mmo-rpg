#pragma once

#include "UnitTypes.h"

class UnitFactory {
public:
    virtual ~UnitFactory();
    virtual Unit* createUnit(UnitKind kind, int x, int y) const = 0;
};

class InfantryFactory : public UnitFactory {
public:
    Unit* createUnit(UnitKind kind, int x, int y) const override;
};

class ArcherFactory : public UnitFactory {
public:
    Unit* createUnit(UnitKind kind, int x, int y) const override;
};

class CavalryFactory : public UnitFactory {
public:
    Unit* createUnit(UnitKind kind, int x, int y) const override;
};