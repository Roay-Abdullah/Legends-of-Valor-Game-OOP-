#pragma once
#include <string>
#include <fstream>
#include "24F-0570_24F-0512_Inventory.h"
using namespace std;

class Enemy;

struct Buff
{
    string name;
    int attackBoost;
    int defenseBoost;
    int agilityBoost;
    int turnsLeft;
};

struct BattleRecord
{
    string enemyName;
    string outcome;
    int experienceGained;
};

class Character 
{
protected:
    string name;
    int level;
    int health;
    int agility;
    int attack;
    int defense;
    int gold;
    int experience;
    int enemies;
    int mana;
    int skillCooldown;
    static int playerCount;
    Inventory* inventory;
    BattleRecord battleRecords[100];
    int recordCount;
    Buff activeBuffs[5];
    int buffCount;

public:
    Character(string, int, int, int, int, int, int, int);
    Character(const Character&);
    virtual ~Character();
    virtual void useSkill() = 0;
    virtual void levelUp() = 0;
    virtual void attackEnemy(Enemy*) = 0;
    int getHealth() const;
    string getName() const;
    int getAgility() const;
    int getDefense() const;
    int getEnemiesDefeated() const;
    int getMana() const;
    static int getPlayerCount();
    int getLevel() const;
    void takeDamage(int);
    void heal(int);
    void setDefense(int);
    void setAttack(int);
    void setAgility(int);
    void showStats() const;
    void addItem(Item*);
    bool buyItem(Item*, int);
    void useItem(int);
    void removeItem(int);
    void showInventory() const;
    void addBattleRecord(const string&, const string&, int);
    void viewBattleHistory() const;
    void updateBuffs();
    void applyBuff(const string&, int, int, int, int);
    void save(ofstream&) const;
    void load(ifstream&);
    void showFinalReport() const;
};


class Warrior : public Character
{
protected:
    int armor;

public:
    Warrior(string, int, int, int, int, int, int, int, int);
    virtual void useSkill() override;
    virtual void levelUp() override;
    virtual void attackEnemy(Enemy*) override;
};


class Mage : public Character 
{
protected:
    int magic;

public:
    Mage(string, int, int, int, int , int, int, int, int);
    virtual void useSkill() override;
    virtual void levelUp() override;
    virtual void attackEnemy(Enemy* e) override;
};


class Rogue : public Character 
{
protected:
    int stealth;

public:
    Rogue(string, int, int, int, int, int, int, int, int);
    virtual void useSkill() override;
    virtual void levelUp() override;
    virtual void attackEnemy(Enemy*) override;
};


class Archer : public Character 
{
protected:
    int range;

public:
    Archer(string, int, int, int, int, int, int, int, int);
    virtual void useSkill() override;
    virtual void levelUp() override;
    virtual void attackEnemy(Enemy*) override;
};

