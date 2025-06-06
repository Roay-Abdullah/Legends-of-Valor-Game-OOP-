#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "24F-0570_24F-0512_Character.h"
#include "24F-0570_24F-0512_Enemy.h"
#include "24F-0570_24F-0512_Area.h"
#include "24F-0570_24F-0512_Item.h"
#include "24F-0570_24F-0512_Inventory.h"
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_RED     "\033[31m"
#define BOLD_ON       "\033[1m"
#define BOLD_OFF      "\033[22m"
using namespace std;


//Clear Input Buffer
static void clearInputBuffer()
{
    try
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (...)
    {
        cout << "Error clearing input buffer." << endl;
        system("pause");
    }
}

//Get integer Input
static int getIntInput(const string& prompt)
{
    try
    {
        int value = 0;
        string input;
        cout << prompt;
        getline(cin, input);
        bool valid = true;
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                valid = false;
                break;
            }
            value = value * 10 + (input[i] - '0');
        }
        if (!valid || input.empty())
        {
            throw runtime_error("Invalid input! Please enter a valid integer.");
        }
        return value;
    }
    catch (const runtime_error& e)
    {
        cout << e.what() << endl;
        clearInputBuffer();
        return getIntInput(prompt);
    }
    catch (...)
    {
        cout << "Unexpected error occurred. Please try again." << endl;
        clearInputBuffer();
        return getIntInput(prompt);
    }
}

//Get string Input
static string getStringInput(const string& prompt)
{
    try
    {
        string input;
        cout << prompt;
        getline(cin, input);
        if (input.empty())
        {
            cout << "Input cannot be empty! Please try again: ";
            return getStringInput("");
        }
        return input;
    }
    catch (...)
    {
        cout << "Error getting string input." << endl;
        system("pause");
        return getStringInput(prompt);
    }
}

//Create Player through choice of User
static Character* createPlayer()
{
    try
    {
        system("cls");
        string name = getStringInput("Enter your name: ");
        cout << "Choose class:" << endl;
        cout << "1.Warrior" << endl;
        cout << "2.Mage" << endl;
        cout << "3.Rogue" << endl;
        cout << "4.Archer" << endl;
        int choice = getIntInput("Choice: ");
        switch (choice)
        {
        case 1:
            return new Warrior(name, 1, 60, 8, 10, 3, 50, 30, 3);
        case 2:
            return new Mage(name, 1, 50, 10, 7, 2, 50, 40, 5);
        case 3:
            return new Rogue(name, 1, 55, 12, 8, 2, 50, 30, 8);
        case 4:
            return new Archer(name, 1, 50, 11, 9, 2, 50, 30, 10);
        default:
            cout << "Invalid choice, defaulting to Warrior." << endl;
            system("pause");
            return new Warrior(name, 1, 60, 8, 10, 3, 50, 30, 3);
        }
    }
    catch (...)
    {
        cout << "Error creating player. Defaulting to Warrior." << endl;
        system("pause");
        return new Warrior("Default", 1, 60, 8, 10, 3, 50, 30, 3);
    }
}

//Save game Data through file handling
static void saveGame(const Character* c)
{
    try
    {
        system("cls");
        ofstream out("savegame.txt");
        if (!out.is_open())
        {
            throw runtime_error("Unable to open save file.");
        }
        c->save(out);
        out.close();
        cout << "Game saved." << endl;
        system("pause");
    }
    catch (const runtime_error& e)
    {
        cout << "Save failed: " << e.what() << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error saving game." << endl;
        system("pause");
    }
}

//Load Game data from previously saved game through file
static void loadGame(Character* c)
{
    try
    {
        system("cls");
        ifstream in("savegame.txt");
        if (!in.is_open())
        {
            throw runtime_error("No save file found.");
        }
        c->load(in);
        string line;
        getline(in, line);
        if (line != "checksum=12345")
        {
            throw runtime_error("Save file corrupted!");
        }
        cout << "Game loaded." << endl;
        in.close();
        system("pause");
    }
    catch (const runtime_error& e)
    {
        cout << e.what() << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error loading game." << endl;
        system("pause");
    }
}

//Control Turn-based battle between player and enemy
static void engageBattle(Character* c, Enemy* e)
{
    try
    {
        system("cls");
        cout << endl;
        cout << "Battle: " << c->getName() << " vs " << e->getName() << endl;
        bool defending = false;
        while (c->getHealth() > 0 && e->getHealth() > 0)
        {
            system("cls");
            cout << endl;
            cout << "HP: " << c->getHealth() << " | Enemy HP: " << e->getHealth() << endl;
            int choice = getIntInput("1. Attack 2. Skill 3. Item 4. Defend\nChoice: ");
            c->updateBuffs();
            int originalDefense = c->getDefense();
            if (defending == true)
            {
                c->setDefense(-5);
                defending = false;
            }
            switch (choice)
            {
            case 1:
                c->attackEnemy(e);
                break;
            case 2:
                c->useSkill();
                break;
            case 3:
            {
                c->showInventory();
                int index = getIntInput("Item index (0 to cancel): ");
                if (index > 0)
                {
                    c->useItem(index - 1);
                }
                break;
            }
            case 4:
                c->setDefense(5);
                defending = true;
                cout << "Defending: +5 Defense" << endl;
                system("pause");
                break;
            default:
                cout << "Invalid choice." << endl;
                system("pause");
                continue;
            }
            if (e->getHealth() > 0)
            {
                e->attackCharacter(c);
            }
        }
        string outcome;
        if (c->getHealth() > 0)
        {
            outcome = "Victory";
        }
        else
        {
            outcome = "Defeat";
        }
        int exp;
        if (outcome == "Victory")
        {
            exp = 10;
        }
        else
        {
            exp = 0;
        }
        c->addBattleRecord(e->getName(), outcome, exp);
        cout << outcome << "!" << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error during battle." << endl;
        system("pause");
    }
}


int main()
{
    try
    {
        system("color 0A");
        srand(time(0));
        Character* c = createPlayer();
        if (!c)
        {
            throw runtime_error("Failed to create player.");
        }

        Area* areas[4] = { new Forest(), new Cave(), new Town(), new Dungeon() };
        int areaCount = 4;
        bool inCombat = false;

        c->addItem(new Potion("Health Potion", "Heals 15 HP", 15));
        c->addItem(new BuffItem("Strength", "Boosts attack by 5", 5, 0, 2));
        system("pause");


        bool running = true;
        while (running == true)
        {
            system("cls");
            cout << endl;
            cout << COLOR_GREEN << ".-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=." << endl;
            cout << "|" << BOLD_ON << COLOR_CYAN << "         LEGENDS OF VALOR          " << BOLD_OFF << COLOR_GREEN << "     |" << endl;
            cout << "|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|" << endl;
            cout << "|" << COLOR_YELLOW << "  1. " << COLOR_RESET << "Explore the Realm" << string(18, ' ') << COLOR_GREEN << "|" << endl;
            cout << "|" << COLOR_YELLOW << "  2. " << COLOR_RESET << "Character Statistics" << string(15, ' ') << COLOR_GREEN << "|" << endl;
            cout << "|" << COLOR_YELLOW << "  3. " << COLOR_RESET << "Inventory Management" << string(15, ' ') << COLOR_GREEN << "|" << endl;
            cout << "|" << COLOR_YELLOW << "  4. " << COLOR_RESET << "Battle History" << string(21, ' ') << COLOR_GREEN << "|" << endl;
            cout << "|" << COLOR_YELLOW << "  5. " << COLOR_RESET << "Save Progress" << string(22, ' ') << COLOR_GREEN << "|" << endl;
            cout << "|" << COLOR_YELLOW << "  6. " << COLOR_RESET << "Load Game" << string(25, ' ') << COLOR_GREEN << " |" << endl;
            cout << "|" << COLOR_YELLOW << "  7. " << COLOR_RED << "Quit Game" << string(25, ' ') << COLOR_GREEN << " |" << endl;
            cout << ":-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=:" << COLOR_RESET << endl;
            int choice = getIntInput("\nEnter your choice (1-7): ");
            if (c->getLevel() >= 3)
            {
                areas[3]->setIsLocked(false);
            }

            system("color 0A");
            switch (choice)
            {
            case 1:
            {
                system("cls");
                cout << "Areas:" << endl;
                for (int i = 0; i < areaCount; i++)
                {
                    cout << i + 1 << ". " << areas[i]->getName() << (areas[i]->getIsLocked() ? " (Locked)" : "") << endl;
                }
                int areaChoice = getIntInput("Choose area: ");
                if (areaChoice < 1 || areaChoice > areaCount)
                {
                    cout << "Invalid area!" << endl;
                    system("pause");
                    break;
                }
                Area* area = areas[areaChoice - 1];
                if (area->getIsLocked())
                {
                    cout << "Area locked! Reach level 3 to unlock the Dungeon." << endl;
                    system("pause");
                    break;
                }
                area->enterArea();
                area->triggerEvent(c);
                if (rand() % 100 < area->getEnemyEncounterRate() * 100)
                {
                    Enemy* enemy = area->getRandomEnemy(c->getLevel());
                    if (!enemy)
                    {
                        cout << "Failed to generate enemy, skipping battle." << endl;
                        system("pause");
                        break;
                    }
                    inCombat = true;
                    engageBattle(c, enemy);
                    inCombat = false;
                    delete enemy;
                }
                break;
            }
            case 2:
                c->showStats();
                break;
            case 3:
            {
                c->showInventory();
                int index = getIntInput("Use item? (0 for no): ");
                if (index > 0)
                {
                    c->useItem(index - 1);
                }
                break;
            }
            case 4:
                c->viewBattleHistory();
                break;
            case 5:
                saveGame(c);
                break;
            case 6:
                loadGame(c);
                break;
            case 7:
            {
                if (inCombat)
                {
                    cout << "Warning: Quitting in combat may result in loss!" << endl;
                }
                int saveChoice = getIntInput("Save? (1: Yes, 0: No): ");
                if (saveChoice == 1)
                {
                    saveGame(c);
                }
                c->showFinalReport();
                running = false;
                break;
            }
            default:
                cout << "Invalid choice." << endl;
                system("pause");
            }
        }

        delete c;
        for (int i = 0; i < areaCount; i++)
        {
            delete areas[i];
        }
    }
    catch (const runtime_error& e)
    {
        cout << "Fatal error: " << e.what() << endl;
        system("pause");
        return 1;
    }
    catch (...)
    {
        cout << "An unexpected error occurred. Exiting game." << endl;
        system("pause");
        return 1;
    }
    return 0;
}
