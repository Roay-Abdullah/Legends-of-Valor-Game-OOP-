#pragma once
#include <string>
using namespace std;

class Character;
class Enemy;

class Area
{
protected:
    string name;
    string description;
    float enemyEncounterRate;
    bool isLocked;

public:
    Area(string, string, float, bool);
    virtual ~Area();
    virtual void enterArea() = 0;
    virtual Enemy* getRandomEnemy(int) = 0;
    virtual void triggerEvent(Character*) = 0;
    float getEnemyEncounterRate() const;
    string getName() const;
    bool getIsLocked() const;
    void setIsLocked(bool);
};


class Forest : public Area 
{
public:
    Forest();
    virtual void enterArea() override;
    virtual Enemy* getRandomEnemy(int) override;
    virtual void triggerEvent(Character*) override;
};


class Cave : public Area 
{
public:
    Cave();
    virtual void enterArea() override;
    virtual Enemy* getRandomEnemy(int) override;
    virtual void triggerEvent(Character*) override;
};


class Town : public Area
{
public:
    Town();
    virtual void enterArea() override;
    virtual Enemy* getRandomEnemy(int) override;
    virtual void triggerEvent(Character*) override;
};


class Dungeon : public Area 
{
public:
    Dungeon();
    virtual void enterArea() override;
    virtual Enemy* getRandomEnemy(int) override;
    virtual void triggerEvent(Character*) override;
};

