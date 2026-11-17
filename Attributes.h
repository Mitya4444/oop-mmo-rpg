#pragma once

// Контракт классов-атрибутов:
// Health - изменяемый атрибут: значение меняется только через decrease/increase
// с проверками (не ниже нуля, защита от переполнения).
// Armor и Attack - неизменяемые после создания: модификаторов нет, присваивание
// удалено; копирование разрешено осознанно, юнит копирует атрибуты в свои поля.
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