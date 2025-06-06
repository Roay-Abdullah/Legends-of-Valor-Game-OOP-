#include <iostream>
#include <string>
#include "24F-0570_24F-0512_Inventory.h"
#include "24F-0570_24F-0512_Item.h"
#include "24F-0570_24F-0512_Character.h"


//Inventory constructor to initialize the variables
Inventory::Inventory() : itemCount(0)
{
    for (int i = 0; i < 10; ++i)
    {
        items[i] = nullptr;
    }
}
//Copy Inventory constructor for deep copy
Inventory::Inventory(const Inventory& other) : itemCount(other.itemCount)
{
    for (int i = 0; i < itemCount; i++)
    {
        items[i] = other.items[i];
    }
    for (int i = itemCount; i < 10; i++)
    {
        items[i] = nullptr;
    }
}
//Inventory virtual destructor
Inventory::~Inventory()
{
    for (int i = 0; i < itemCount; i++)
    {
        delete items[i];
    }
}
//Add item to Inventory and check inventory full or duplicate items
bool Inventory::addItem(Item* item)
{
    try 
    {
        if (itemCount >= 10)
        {
            cout << "Inventory full!" << endl;
            system("pause");
            return false;
        }
        for (int i = 0; i < itemCount; i++) 
        {
            if (items[i]->getName() == item->getName() && item->getIsUnique())
            {
                cout << "Cannot add duplicate unique item: " << item->getName() << endl;
                system("pause");
                return false;
            }
        }
        items[itemCount++] = item;
        cout << "Added " << item->getName() << " to inventory." << endl;
        return true;
    }
    catch (...) 
    {
        cout << "Error adding item to inventory." << endl;
        system("pause");
        return false;
    }
}
//Remove item from Inventory
void Inventory::removeItem(int index) 
{
    try
    {
        if (index < 0 || index >= itemCount)
        {
            throw runtime_error("Invalid index!");
        }
        delete items[index];
        for (int i = index; i < itemCount - 1; i++)
        {
            items[i] = items[i + 1];
        }
        items[--itemCount] = nullptr;
        cout << "Item removed." << endl;
        system("pause");
    }
    catch (const runtime_error& e)
    {
        cout << e.what() << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error removing item from inventory." << endl;
        system("pause");
    }
}
//Use item from Inventory
void Inventory::useItem(int index, Character* c)
{
    try 
    {
        if (index < 0 || index >= itemCount)
        {
            throw runtime_error("Invalid item index!");
        }
        items[index]->use(c);
        if (items[index]->isConsumable())
        {
            removeItem(index);
        }
    }
    catch (const runtime_error& e) 
    {
        cout << e.what() << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error using item." << endl;
        system("pause");
    }
}
//Show inventory items
void Inventory::showInventory() const
{
    try
    {
        system("cls");
        cout << "Inventory:" << endl;
        if (itemCount == 0)
        {
            cout << "  (Empty)" << endl;
        }
        else
        {
            for (int i = 0; i < itemCount; i++)
            {
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
        system("pause");
    }
    catch (...)
    {
        cout << "Error displaying inventory." << endl;
        system("pause");
    }
}
//Save Data of Inventory through file Handling
void Inventory::save(ofstream& out) const
{
    try 
    {
        out << "[Inventory]" << endl;
        cout << "count = " << itemCount << endl;
        for (int i = 0; i < itemCount; i++) 
        {
            out << "item" << i << "=";
            items[i]->save(out);
            out << endl;
        }
    }
    catch (const ios_base::failure& e)
    {
        cout << "Error saving inventory: " << e.what() << endl;
        throw;
    }
    catch (...) 
    {
        cout << "Error saving inventory." << endl;
        throw;
    }
}
//Load Game data from previous saved game through file
void Inventory::load(ifstream& in, int count)
{
    try
    {
        itemCount = count;
        string line;
        for (int i = 0; i < count && getline(in, line); i++)
        {
            int p1 = line.find('=');
            int p2 = line.find(',', p1 + 1);
            int p3 = line.find(',', p2 + 1);

            if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
            {
                throw runtime_error("Invalid save data format.");
            }
            string n = line.substr(p1 + 1, p2 - p1 - 1);
            string d = line.substr(p2 + 1, p3 - p2 - 1);
            int u = 0;
            string boolStr = line.substr(p3 + 1);
            if (boolStr == "1")
            {
                u = 1;
            }
            if (n.find("Buff") != string::npos)
            {
                items[i] = new BuffItem(n, d, 5, 0, 2);
            }   
            else
            {
                items[i] = new Potion(n, d, 15);
            }       
        }
    }
    catch (const ios_base::failure& e) 
    {
        cout << "Error reading inventory from file: " << e.what() << endl;
        throw;
    }
    catch (const runtime_error& e) 
    {
        cout << "Error loading inventory: " << e.what() << endl;
        throw;
    }
    catch (...) 
    {
        cout << "Error loading inventory." << endl;
        throw;
    }
}
