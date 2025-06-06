#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Item;
class Character;

class Inventory
{
private:
    Item* items[10];
    int itemCount;

public:
    Inventory();
    Inventory(const Inventory&);
    ~Inventory();
    bool addItem(Item*);
    void removeItem(int);
    void useItem(int index, Character*);
    void showInventory() const;
    void save(ofstream&) const;
    void load(ifstream&, int);
};
