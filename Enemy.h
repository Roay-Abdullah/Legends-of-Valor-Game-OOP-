#pragma once
#include <string>
using namespace std;

class Character;

class Enemy
{
protected:
    string name;
    int health;
    int maxHealth;
    int agility;
    int attack;
    int defense;

public:
    Enemy(string, int, int, int, int);
    virtual ~Enemy();
    virtual void attackCharacter(Character*) = 0;
    int getHealth() const;
    int getMaxHealth() const;
    string getName() const;
    int getAgility() const;
    int getDefense() const;
    void takeDamage(int);
};


class Wolves : public Enemy 
{
public:
    Wolves(string, int, int, int, int);
    virtual void attackCharacter(Character*) override;
};


class Goblin : public Enemy
{
public:
    Goblin(string, int, int, int, int);
    virtual void attackCharacter(Character*) override;
};


class Zombie : public Enemy 
{
public:
    Zombie(string, int, int, int, int );
    virtual void attackCharacter(Character*) override;
};


class Dragon : public Enemy 
{
public:
    Dragon(string, int, int, int, int);
    virtual void attackCharacter(Character*) override;
};


class Boss : public Enemy
{
public:
    Boss(string, int, int, int, int);
    virtual void attackCharacter(Character*) override;

private:
    void normalAttack(Character*);
};


