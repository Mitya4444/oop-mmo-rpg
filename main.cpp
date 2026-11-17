#include <iostream>
#include <utility>
#include <vector>

#include "GameField.h"
#include "UnitFactory.h"

void scenario1() {
    std::cout << "=== Scenario 1: Create and populate field ===" << std::endl;
    GameField field(5, 5, 10);
    InfantryFactory infantryFactory;
    ArcherFactory archerFactory;
    CavalryFactory cavalryFactory;

    field.addUnit(infantryFactory, UnitKind::Swordsman, 1, 1);
    field.addUnit(infantryFactory, UnitKind::Spearman, 2, 1);
    field.addUnit(archerFactory, UnitKind::LightArcher, 3, 2);
    field.addUnit(archerFactory, UnitKind::HeavyArcher, 4, 2);
    field.addUnit(cavalryFactory, UnitKind::Cataphract, 0, 4);
    field.addUnit(cavalryFactory, UnitKind::HorseArcher, 1, 4);

    std::cout << "Field size: " << field.size() << std::endl;
    std::cout << "Field dimensions: " << field.getWidth() << "x" << field.getHeight() << std::endl;
    std::cout << "Max units: " << field.getMaxUnits() << std::endl;
    std::cout << "Units:" << std::endl;
    for (const Unit& unit : field) {
        std::cout << "  " << unit.getType() << " at (" << unit.getX() << "," << unit.getY()
                  << ") hp=" << unit.getHealth().getValue()
                  << " armor=" << unit.getArmor().getValue()
                  << " attack=" << unit.getAttack().getValue() << std::endl;
    }

    std::cout << "Centralized move:" << std::endl;
    std::cout << "  move (1,1)->(0,0): " << field.moveUnit(1, 1, 0, 0) << std::endl;
    std::cout << "  unit at (0,0): " << field.getUnit(0, 0)->getType() << std::endl;
    std::cout << "  cell (1,1) empty: " << (field.getUnit(1, 1) == nullptr) << std::endl;
    std::cout << "  moved unit coords: " << field.getUnit(0, 0)->getX() << "," << field.getUnit(0, 0)->getY() << std::endl;

    const GameField& readonly = field;
    std::cout << "Const traversal:" << std::endl;
    for (const Unit& unit : readonly) {
        std::cout << "  " << unit.getType() << std::endl;
    }
    std::cout << std::endl;
}

void scenario2() {
    std::cout << "=== Scenario 2: Deep copy ===" << std::endl;
    GameField original(5, 5, 10);
    InfantryFactory infantryFactory;
    ArcherFactory archerFactory;

    original.addUnit(infantryFactory, UnitKind::Swordsman, 1, 1);
    original.addUnit(archerFactory, UnitKind::LightArcher, 3, 2);

    GameField copy = original;
    std::cout << "Copy constructor test:" << std::endl;
    std::cout << "  Original size: " << original.size() << std::endl;
    std::cout << "  Copy size: " << copy.size() << std::endl;

    original.damageUnit(1, 1, 50);
    std::cout << "  After damage to original:" << std::endl;
    std::cout << "    Original hp at (1,1): " << original.getUnit(1, 1)->getHealth().getValue() << std::endl;
    std::cout << "    Copy hp at (1,1): " << copy.getUnit(1, 1)->getHealth().getValue() << std::endl;

    original.removeUnit(3, 2);
    std::cout << "  After remove from original:" << std::endl;
    std::cout << "    Original size: " << original.size() << std::endl;
    std::cout << "    Copy size: " << copy.size() << std::endl;
    std::cout << "    Copy still has unit at (3,2): " << (copy.getUnit(3, 2) != nullptr) << std::endl;

    GameField assigned(3, 3, 5);
    assigned.addUnit(infantryFactory, UnitKind::Spearman, 0, 0);
    std::cout << "Copy assignment test:" << std::endl;
    std::cout << "  Assigned size before: " << assigned.size() << std::endl;
    std::cout << "  Assigned unit type: " << assigned.getUnit(0, 0)->getType() << std::endl;

    assigned = original;
    std::cout << "  After assignment:" << std::endl;
    std::cout << "    Assigned size: " << assigned.size() << std::endl;
    std::cout << "    Assigned has Swordsman at (1,1): " << (assigned.getUnit(1, 1) != nullptr) << std::endl;
    std::cout << "    Assigned has Spearman at (0,0): " << (assigned.getUnit(0, 0) != nullptr) << std::endl;
    std::cout << "    Original size unchanged: " << original.size() << std::endl;

    std::cout << "  Independence check:" << std::endl;
    assigned.damageUnit(1, 1, 10);
    std::cout << "    Assigned hp at (1,1) after damage: " << assigned.getUnit(1, 1)->getHealth().getValue() << std::endl;
    std::cout << "    Original hp at (1,1) unchanged: " << original.getUnit(1, 1)->getHealth().getValue() << std::endl;
    std::cout << std::endl;
}

void scenario3() {
    std::cout << "=== Scenario 3: Move semantics ===" << std::endl;
    GameField source(5, 5, 10);
    InfantryFactory infantryFactory;
    source.addUnit(infantryFactory, UnitKind::Swordsman, 1, 1);
    source.addUnit(infantryFactory, UnitKind::Spearman, 2, 2);

    std::cout << "Move constructor test:" << std::endl;
    std::cout << "  Source size before move: " << source.size() << std::endl;

    GameField moved = std::move(source);
    std::cout << "  Source size after move: " << source.size() << std::endl;
    std::cout << "  Moved size: " << moved.size() << std::endl;

    GameField target(3, 3, 5);
    InfantryFactory factory2;
    target.addUnit(factory2, UnitKind::Swordsman, 0, 0);
    std::cout << "Move assignment test:" << std::endl;
    std::cout << "  Target size before move assignment: " << target.size() << std::endl;

    target = std::move(moved);
    std::cout << "  Target size after move assignment: " << target.size() << std::endl;
    std::cout << "  Moved size after assignment: " << moved.size() << std::endl;
    std::cout << std::endl;
}

void scenario4() {
    std::cout << "=== Scenario 4: Iterator with mass action ===" << std::endl;
    GameField field(5, 5, 10);
    InfantryFactory infantryFactory;
    ArcherFactory archerFactory;

    field.addUnit(infantryFactory, UnitKind::Swordsman, 1, 1);
    field.addUnit(infantryFactory, UnitKind::Spearman, 2, 2);
    field.addUnit(archerFactory, UnitKind::LightArcher, 3, 3);

    std::cout << "Before mass damage:" << std::endl;
    for (const Unit& unit : field) {
        std::cout << "  " << unit.getType() << " hp=" << unit.getHealth().getValue() << std::endl;
    }

    std::cout << "Applying 20 damage to all units..." << std::endl;
    for (Unit& unit : field) {
        unit.takeDamage(20);
    }

    std::cout << "After mass damage:" << std::endl;
    for (const Unit& unit : field) {
        std::cout << "  " << unit.getType() << " hp=" << unit.getHealth().getValue() << std::endl;
    }
    std::cout << std::endl;
}

void scenario5() {
    std::cout << "=== Scenario 5: Deferred removal during iteration ===" << std::endl;
    GameField field(5, 5, 10);
    InfantryFactory infantryFactory;

    field.addUnit(infantryFactory, UnitKind::Swordsman, 1, 1);
    field.addUnit(infantryFactory, UnitKind::Spearman, 2, 2);
    field.addUnit(infantryFactory, UnitKind::Swordsman, 3, 3);

    std::cout << "Before removal:" << std::endl;
    for (const Unit& unit : field) {
        std::cout << "  " << unit.getType() << " at (" << unit.getX() << "," << unit.getY() << ")" << std::endl;
    }

    std::vector<std::pair<int, int>> doomed;
    for (const Unit& unit : field) {
        if (unit.getHealth().getValue() < 100) {
            doomed.push_back(std::make_pair(unit.getX(), unit.getY()));
        }
    }

    std::cout << "Removing units with health < 100..." << std::endl;
    for (const std::pair<int, int>& position : doomed) {
        field.removeUnit(position.first, position.second);
    }

    std::cout << "After removal:" << std::endl;
    for (const Unit& unit : field) {
        std::cout << "  " << unit.getType() << " at (" << unit.getX() << "," << unit.getY() << ")" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    scenario1();
    scenario2();
    scenario3();
    scenario4();
    scenario5();

    std::cout << "All scenarios completed successfully." << std::endl;
    return 0;
}