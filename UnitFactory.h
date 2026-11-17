#pragma once

#include "UnitTypes.h"

// Порождающий паттерн: фабричный метод в параметризованной разновидности.
// Абстрактную фабрику не берём: задаче не нужны семейства связанных юнитов
// ("армия Севера" / "армия Юга"), каждый юнит создаётся независимо.
// Параметр UnitKind нужен потому, что по чек-листу три фабрики на шесть видов:
// без выбора вида внутри фабрики понадобилось бы по фабрике на каждый вид.
// Создание делегировано виртуальному createUnit, клиент (GameField, main)
// знает только абстракции UnitFactory и Unit и не пишет new конкретных видов.
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