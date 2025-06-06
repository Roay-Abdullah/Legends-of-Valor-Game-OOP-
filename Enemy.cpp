#include <iostream>
#include <string>
#include "24F-0570_24F-0512_Enemy.h"
#include "24F-0570_24F-0512_Character.h"

//Enemy constructor to initialize the variables
Enemy::Enemy(string Name, int Health, int Agility, int Attack, int Defense) : name(Name), maxHealth(Health), health(Health), agility(Agility), attack(Attack), defense(Defense) {}
//Enemy virtual destructor
Enemy::~Enemy() {}
//Enemy get Health
int Enemy::getHealth() const
{
    return health;
}
//Enemy get MaxHealth
int Enemy::getMaxHealth() const
{
    return maxHealth;
}
//Enemy get Name
string Enemy::getName() const
{
    return name;
}
//Enemy get Agility
int Enemy::getAgility() const
{
    return agility;
}
//Enemy get Defense
int Enemy::getDefense() const
{
    return defense;
}
//Enemy take Damage
void Enemy::takeDamage(int damage) 
{
    try 
    {
        health -= damage;
        if (health < 0)
        {
            health = 0;
        }

    }
    catch (...)
    {
        cout << "Error applying damage to enemy." << endl;
        system("pause");
    }
}


//Wolves Constructor
Wolves::Wolves(string Name, int Health, int Agility, int Attack, int Defense) : Enemy(Name, Health, Agility, Attack, Defense) {}
//Enemy attacking the player
void Wolves::attackCharacter(Character* c) 
{
    try 
    {
        //if player Health greater than 0 then proceed to attack else Defeated 
        if (c->getHealth() > 0)
        {
            //if random num less than (enemy Agility - player Agility + 50) then attack proceed else dodged the Hit
            if (rand() % 100 < agility - c->getAgility() + 50)
            {
                //if enemy attack greater than player Defense then it take Damage of player otherwise it will be defended by player
                if (attack > c->getDefense())
                {
                    //if (enemy attack - player Defense) greater than 10 then it will be Crtical Hit otherwise normal Hit 
                    if (attack - c->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                }
                else
                {
                    cout << c->getName() << " defended the attack sucessfully" << endl;
                    c->takeDamage(1);
                }
            }
            else
            {
                cout << c->getName() << " dodged the hit" << endl;
            }

        }
        system("pause");
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Wolves." << endl;
        system("pause");
    }
}


//Goblin constructor
Goblin::Goblin(string Name, int Health, int Agility, int Attack, int Defense) : Enemy(Name, Health, Agility, Attack, Defense) {}
//Same as Wolves
void Goblin::attackCharacter(Character* c) 
{
    try 
    {
        if (c->getHealth() > 0)
        {
            if (rand() % 100 < agility - c->getAgility() + 50)
            {
                if (attack > c->getDefense())
                {
                    if (attack - c->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                }
                else
                {
                    cout << c->getName() << " defended the attack sucessfully" << endl;
                    c->takeDamage(1);
                }
            }
            else
            {
                cout << c->getName() << " dodged the hit" << endl;
            }

        }
        system("pause");
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Goblin." << endl;
        system("pause");
    }
}


//Zombie constructor
Zombie::Zombie(string Name, int Health, int Agility, int Attack, int Defense) : Enemy(Name, Health, Agility, Attack, Defense) {}
//Same as Wolves
void Zombie::attackCharacter(Character* c)
{
    try 
    {
        if (c->getHealth() > 0)
        {
            if (rand() % 100 < agility - c->getAgility() + 50)
            {
                if (attack > c->getDefense())
                {
                    if (attack - c->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                }
                else
                {
                    cout << c->getName() << " defended the attack sucessfully" << endl;
                    c->takeDamage(1);
                }
            }
            else
            {
                cout << c->getName() << " dodged the hit" << endl;
            }

        }
        system("pause");
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Zombie." << endl;
        system("pause");
    }
}


//Dragon constructor
Dragon::Dragon(string Name, int Health, int Agility, int Attack, int Defense) : Enemy(Name, Health, Agility, Attack, Defense) {}
//Same as Wolves
void Dragon::attackCharacter(Character* c)
{
    try 
    {
        if (c->getHealth() > 0)
        {
            if (rand() % 100 < agility - c->getAgility() + 50)
            {
                if (attack > c->getDefense())
                {
                    if (attack - c->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                }
                else
                {
                    cout << c->getName() << " defended the attack sucessfully" << endl;
                    c->takeDamage(1);
                }
            }
            else
            {
                cout << c->getName() << " dodged the hit" << endl;
            }

        }
        system("pause");
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Dragon." << endl;
        system("pause");
    }
}


//Boss constructor
Boss::Boss(string Name, int Health, int Agility, int Attack, int Defense) : Enemy(Name, Health, Agility, Attack, Defense) {}
//Boss attack to player in events/phases
void Boss::attackCharacter(Character* c)
{
    try
    {
        double healthRatio = static_cast<double>(health) / maxHealth;
        //if Health greater than 66% then normal attack like other enemies attack
        if (healthRatio > 0.66)              
        {
            cout << name << " (Phase 1): Normal Attack" << endl;
            normalAttack(c);
        }
        //if Health greater than 33%  and less than 66% then normal attack will be twice
        else if (healthRatio > 0.33) 
        {
            cout << name << " (Phase 2): Double Strike" << endl;
            normalAttack(c);
            if (c->getHealth() > 0)
            {
                normalAttack(c);
            }
        }
        //if Health less than 33% then there is 20% chance to Heal and 80% chance for massive Damage
        else
        {
            cout << name << " (Phase 3): Desperate Assault" << endl;
            if (rand() % 100 < 20) 
            {
                health += 10;
                if (health > maxHealth)
                {
                    health = maxHealth;
                }
                cout << name << " heals for 10 HP!" << endl;
            }
            else 
            {
                int massiveDamage = attack * 2;
                cout << name << " unleashes a massive attack!" << endl;
                if (rand() % 100 < agility - c->getAgility() + 50)
                {
                    cout << "Dealt " << massiveDamage << " damage!" << endl;
                    c->takeDamage(massiveDamage - c->getDefense());
                }
                else
                {
                    cout << c->getName() << " miraculously dodges the devastating attack" << endl;
                }

            }
        }
        system("pause");
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Boss." << endl;
        system("pause");
    }
}
//Same as Wolves
void Boss::normalAttack(Character* c)
{
    try
    {
        if (c->getHealth() > 0)
        {
            if ((rand() % 90 + 10) < agility - c->getAgility() + 50)
            {
                if (attack > c->getDefense())
                {
                    if (attack - c->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << c->getName() << " for " << attack - c->getDefense() << " damage" << endl;
                        c->takeDamage(attack - c->getDefense());
                    }
                }
                else
                {
                    cout << c->getName() << " defended the attack sucessfully" << endl;
                    c->takeDamage(1);
                }
            }
            else
            {
                cout << c->getName() << " dodged the hit" << endl;
            }

        }
        system("pause");
    }
    catch (...) 
    {
        cout << "Error performing normal attack as Boss." << endl;
        system("pause");
    }
}
