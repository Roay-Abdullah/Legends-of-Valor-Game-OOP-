#include <iostream>
#include <string>
#include "24F-0570_24F-0512_Item.h"
#include "24F-0570_24F-0512_Character.h"
using namespace std;


//Item constructor to initialize the variables
Item::Item(string Name, string Desc, bool Unq = false) : name(Name), description(Desc), isUnique(Unq) {}
//Item virtual destructor
Item::~Item() {}
//Item to check is it Consumable/useable or not
bool Item::isConsumable() const
{
    return false;
}
//Item get Name
string Item::getName() const
{
    return name;
}
//Item get is Unique to avoid duplication of item 
bool Item::getIsUnique() const
{
    return isUnique;
}
//Item save data through file handling
void Item::save(ofstream& out) const 
{
    try 
    {
        out << name << "," << description << "," << isUnique;
    }
    catch (const ios_base::failure& e)
    {
        cout << "Error writing item to file: " << e.what() << endl;
        throw;
    }
    catch (...)
    {
        cout << "Unexpected error saving item." << endl;
        throw;
    }
}


//Potion constructor
Potion::Potion(string Name, string Desc, int Heal) : Item(Name, Desc), healAmount(Heal) {}
//Potion to check is it Consumable/useable or not
bool Potion::isConsumable() const
{
    return true;
}
//Potion use 
void Potion::use(Character* c) 
{
    try
    {
        c->heal(healAmount);
        cout << c->getName() << " healed for " << healAmount << " HP." << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error using Potion." << endl;
        system("pause");
    }
}


//BuffItem constructor
BuffItem::BuffItem(string Name, string Desc, int attBoost, int defBoost, int Dur) : Item(Name, Desc), attackBoost(attBoost), defenseBoost(defBoost), duration(Dur) {}
//Same as Potion
bool BuffItem::isConsumable() const
{
    return true;
}
//Same as Potion
void BuffItem::use(Character* c) 
{
    try 
    {
        c->applyBuff(name, attackBoost, defenseBoost, 0, duration);
        system("pause");
    }
    catch (...) 
    {
        cout << "Error using BuffItem." << endl;
        system("pause");
    }
}
