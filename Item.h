#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Character;

class Item
{
protected:
    string name;
    string description;
    bool isUnique;

public:
    Item(string, string, bool);
    virtual ~Item();
    virtual void use(Character*) = 0;
    virtual bool isConsumable() const;
    string getName() const;
    bool getIsUnique() const;
    void save(ofstream&) const;
};


class Potion : public Item
{
protected:
    int healAmount;

public:
    Potion(string, string, int);
    virtual void use(Character*) override;
    virtual bool isConsumable() const override;
};


class BuffItem : public Item 
{
protected:
    int attackBoost;
    int defenseBoost;
    int duration;

public:
    BuffItem(string, string, int, int, int);
    virtual void use(Character*) override;
    virtual bool isConsumable() const override;
};


