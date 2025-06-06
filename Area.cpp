#include <iostream>
#include <string>
#include "24F-0570_24F-0512_Area.h"
#include "24F-0570_24F-0512_Character.h"
#include "24F-0570_24F-0512_Enemy.h"
#include "24F-0570_24F-0512_Item.h"
using namespace std;

//Area constructor to initialize the variables
Area::Area(string Name, string Desc, float Rate, bool Locked) : name(Name), description(Desc), enemyEncounterRate(Rate), isLocked(Locked) {}
//Area virtual destructor
Area::~Area() {}
//Area get Enmey Encounter Rate
float Area::getEnemyEncounterRate() const
{
    return enemyEncounterRate;
}
//Area get Name
string Area::getName() const
{
    return name;
}
//Area get is Locked to check is it locked or open
bool Area::getIsLocked() const
{
    return isLocked;
}
//Area set is Locked
void Area::setIsLocked(bool locked)
{
    isLocked = locked;
}


//Forest constructor
Forest::Forest() : Area("Forest", "A dense, mysterious forest.", 0.5f, false) {}
//Enter Area
void Forest::enterArea() 
{
    try 
    {
        system("cls");
        cout << "Entering " << name << ": " << description << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error entering Forest." << endl;
        system("pause");
    }
}
//Get random Enemy
Enemy* Forest::getRandomEnemy(int Level) 
{
    try 
    {
        int choice = rand() % 2;
        int Hp = 20 + Level * 5;
        if (choice == 0)
        {
            return new Wolves("Forest Wolf", Hp, 10, 5 + Level * 2, 2 + Level);
        }
        else 
        {
            return new Goblin("Forest Goblin", Hp - 5, 15, 7 + Level * 2, 3 + Level);
        }
    }
    catch (...) 
    {
        cout << "Error generating random enemy in Forest." << endl;
        system("pause");
        return nullptr;
    }
}
//Trigger random event
void Forest::triggerEvent(Character* c) 
{
    try
    {
        if (rand() % 100 < 30)
        {
            cout << "Found a healing herb! +5 HP" << endl;
            c->heal(5);
            system("pause");
        }
    }
    catch (...) 
    {
        cout << "Error triggering event in Forest." << endl;
        system("pause");
    }
}


//Cave constructor
Cave::Cave() : Area("Cave", "A dark and eerie cave.", 0.7f, false) {}
//Same as Forest
void Cave::enterArea() 
{
    try 
    {
        system("cls");
        cout << "Entering " << name << ": " << description << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error entering Cave." << endl;
        system("pause");
    }
}
//Same as Forest
Enemy* Cave::getRandomEnemy(int Level) 
{
    try 
    {
        int choice = rand() % 2;
        int Hp = 25 + Level * 5;
        if (choice == 0) 
        {
            return new Zombie("Cave Zombie", Hp, 5, 6 + Level * 2, 4 + Level);
        }
        else 
        {
            return new Dragon("Cave Dragon", Hp + 10, 15, 15 + Level * 2, 8 + Level);
        }
    }
    catch (...)
    {
        cout << "Error generating random enemy in Cave." << endl;
        system("pause");
        return nullptr;
    }
}
//Same as Forest
void Cave::triggerEvent(Character* c)
{
    try 
    {
        system("cls");

        int choice = 0;
        string input;
        cout << endl;
        cout << "Welcome to the Shop!" << endl;
        cout << "1.Attack Buff(50 gold)" << endl;
        cout << "2.Exit" << endl;
        cout << "Choice: ";
        getline(cin, input);

        choice = stoi(input);

        if (choice == 1)
        {
            Item* buff = new BuffItem("Attack Buff", "Boosts attack by 5 for 2 turns", 5, 0, 2);
            if (!c->buyItem(buff, 50))
            {
                delete buff;
            }
        }
        else if (choice == 2)
        {
            cout << "Exiting...." << endl;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
        system("pause");
              
    }
    catch (...) 
    {
        cout << "Error triggering event in Cave." << endl;
        system("pause");
    }
}


//Town constructor
Town::Town() : Area("Town", "A peaceful town.", 0.0f, false) {}
//Same as Forest
void Town::enterArea() 
{
    try
    {
        system("cls");
        cout << "Entering " << name << ": " << description << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error entering Town." << endl;
        system("pause");
    }
}
//Same as Forest
Enemy* Town::getRandomEnemy(int) 
{
    return nullptr;
}
//Same as Forest
void Town::triggerEvent(Character* c) 
{
    try
    {
        cout << "Resting in town: +20 HP restored" << endl;
        c->heal(20);
        system("pause");
    }
    catch (...) 
    {
        cout << "Error triggering event in Town." << endl;
        system("pause");
    }
}


//Dungeon constructor
Dungeon::Dungeon() : Area("Dungeon", "A dangerous dungeon.", 1.0f, true) {}
//Same as Forest
void Dungeon::enterArea() 
{
    try {
        system("cls");
        cout << "Entering " << name << ": " << description << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error entering Dungeon." << endl;
        system("pause");
    }
}
//Same as Forest
Enemy* Dungeon::getRandomEnemy(int Level)
{
    try
    {
        return new Boss("Dungeon Boss", 80 + Level * 5, 10, 15 + Level * 2, 10 + Level);
    }
    catch (...)
    {
        cout << "Error generating random enemy in Dungeon." << endl;
        system("pause");
        return nullptr;
    }
}
//Same as Forest
void Dungeon::triggerEvent(Character* c)
{
    try 
    {
        if (rand() % 100 < 10)
        {
            cout << "Trap triggered! -10 HP" << endl;
            c->takeDamage(10);
            system("pause");
        }
    }
    catch (...) 
    {
        cout << "Error triggering event in Dungeon." << endl;
        system("pause");
    }
}
