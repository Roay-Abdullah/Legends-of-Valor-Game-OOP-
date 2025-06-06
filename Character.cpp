#include <iostream>
#include <string>
#include "24F-0570_24F-0512_Character.h"
#include "24F-0570_24F-0512_Enemy.h"
#include "24F-0570_24F-0512_Item.h"

//Count number of players being created
int Character::playerCount = 0;
//Character constructor to initialize the variables
Character::Character(string Name, int Level, int Health, int Agility, int Attack, int Defense, int Gold, int Mana) : name(Name), level(Level), health(Health), agility(Agility), attack(Attack), defense(Defense), gold(Gold), mana(Mana), experience(0), enemies(0), skillCooldown(0), buffCount(0), recordCount(0)
{
    inventory = new Inventory();
    playerCount++;
}
//Copy Character constructor for deep copy
Character::Character(const Character& other) : name(other.name), level(other.level), health(other.health), agility(other.agility), attack(other.attack), defense(other.defense), gold(other.gold), mana(other.mana), experience(other.experience), enemies(other.enemies), skillCooldown(other.skillCooldown), buffCount(other.buffCount), recordCount(other.recordCount)
{
    inventory = new Inventory(*other.inventory);
    for (int i = 0; i < buffCount; i++)
    {
        activeBuffs[i] = other.activeBuffs[i];
    }
    for (int i = 0; i < recordCount; i++)
    {
        battleRecords[i] = other.battleRecords[i];
    }
    playerCount++;
}
//Character virtual destructor
Character::~Character()
{
    delete inventory;
}
//Character get Health
int Character::getHealth() const
{
    return health;
}
//Character get Name
string Character::getName() const
{
    return name;
}
//Character get Agility
int Character::getAgility() const
{
    return agility;
}
//Character get Defense
int Character::getDefense() const
{
    return defense;
}
//Character get Enemies Defeated
int Character::getEnemiesDefeated() const
{
    return enemies;
}
//Character get Mana
int Character::getMana() const
{
    return mana;
}
//Character get Level
int Character::getLevel() const
{
    return level;
}
//Character get PlayerCount
int Character::getPlayerCount()
{
    return playerCount;
}
//Character take Damage
void Character::takeDamage(int damage) 
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
        cout << "Error applying damage to character." << endl;
        system("pause");
    }
}
//Character Heal function
void Character::heal(int amount)
{
    try 
    {
        if (health > 0 && health <= 100)
        {
            health += amount;
        }
        else
        {
            health = 100;
        }
    }
    catch (...)
    {
        cout << "Error healing character." << endl;
        system("pause");
    }
}
//Character set Defense
void Character::setDefense(int boost) 
{
    try 
    {
        defense += boost;
    }
    catch (...)
    {
        cout << "Error setting defense." << endl;
        system("pause");
    }
}
//Character set Attack
void Character::setAttack(int boost) 
{
    try 
    {
        attack += boost;
    }
    catch (...)
    {
        cout << "Error setting attack." << endl;
        system("pause");
    }
}
//Character set Agility
void Character::setAgility(int boost) 
{
    try 
    {
        agility += boost;
    }
    catch (...)
    {
        cout << "Error setting agility." << endl;
        system("pause");
    }
}
//Character show Stats
void Character::showStats() const
{
    try 
    {
        system("cls");
        cout << endl;
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;
        cout << "Health: " << health << endl;
        cout << "Mana: " << mana << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
        cout << "Gold: " << gold << endl;
        cout << "Experience: " << experience << endl;
        cout << "Enemies Defeated: " << enemies << endl;

        if (buffCount > 0)
        {
            cout << "Active Buffs:" << endl;
            for (int i = 0; i < buffCount; i++)
            {
                cout << "- " << activeBuffs[i].name << " (Turns: " << activeBuffs[i].turnsLeft << ")" << endl;
            }
        }
        system("pause");

    }
    catch (...) 
    {
        cout << "Error displaying stats." << endl;
        system("pause");
    }
}
//Character add Item to Inventory
void Character::addItem(Item* item)
{
    try
    {
        inventory->addItem(item);
    }
    catch (...)
    {
        cout << "Error adding item to inventory." << endl;
        system("pause");
    }
}
//Character buy Item
bool Character::buyItem(Item* item, int price)
{
    try 
    {
        if (gold >= price) 
        {
            gold -= price;
            addItem(item);
            cout << "Purchased " << item->getName() << " for " << price << " gold." << endl;
            system("pause");
            return true;
        }
        cout << "Not enough gold!" << endl;
        system("pause");
        return false;
    }
    catch (...) 
    {
        cout << "Error buying item." << endl;
        system("pause");
        return false;
    }
}
//Character use Item from Inventory
void Character::useItem(int index) 
{
    try
    {
        inventory->useItem(index, this);
    }
    catch (...)
    {
        cout << "Error using item." << endl;
        system("pause");
    }
}
//Character remove Item from Inventory
void Character::removeItem(int index) 
{
    try 
    {
        inventory->removeItem(index);
    }
    catch (...)
    {
        cout << "Error removing item." << endl;
        system("pause");
    }
}
//Character show Inventory
void Character::showInventory() const 
{
    try 
    {
        inventory->showInventory();
    }
    catch (...) 
    {
        cout << "Error showing inventory." << endl;
        system("pause");
    }
}
//Character add Battle records
void Character::addBattleRecord(const string& Enemy, const string& Outcome, int Exp)
{
    try 
    {
        if (recordCount >= 100) 
        {
            throw runtime_error("Battle record limit reached!");
        }
        battleRecords[recordCount++] = { Enemy, Outcome, Exp };
        experience += Exp;
        if (Outcome == "Victory")
        {
            enemies++;
        }
        int expNeeded = level * 100;
        if (experience >= expNeeded)
        {
            levelUp();
            experience -= expNeeded;
        }

    }
    catch (const runtime_error& e) 
    {
        cout << e.what() << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error adding battle record." << endl;
        system("pause");
    }
}
//Character view Battle History
void Character::viewBattleHistory() const
{
    try 
    {
        system("cls");

        cout << endl;
        cout << "Battle History:" << endl;
        for (int i = 0; i < recordCount; i++)
        {
            cout << "Battle " << i + 1 << ": vs " << battleRecords[i].enemyName << ", Outcome: " << battleRecords[i].outcome << ", Exp: " << battleRecords[i].experienceGained << endl;
        }

        system("pause");
    }
    catch (...)
    {
        cout << "Error displaying battle history." << endl;
        system("pause");
    }
}
//Character update Buff items and restoring cooldown for them
void Character::updateBuffs() 
{
    try
    {
        for (int i = 0; i < buffCount; i++)
        {
            activeBuffs[i].turnsLeft--;
            if (activeBuffs[i].turnsLeft <= 0)
            {
                for (int j = i; j < buffCount - 1; j++)
                {
                    activeBuffs[j] = activeBuffs[j + 1];
                }
                buffCount--;
                i--;
            }
        }
        if (skillCooldown > 0)
        {
            skillCooldown--;
        }

    }
    catch (...)
    {
        cout << "Error updating buffs." << endl;
        system("pause");
    }
}
//Character apply Buff items
void Character::applyBuff(const string& Name, int AttBoost, int DefBoost, int AgiBoost, int Dur)
{
    try
    {
        if (buffCount >= 5) 
        {
            throw runtime_error("Buff limit reached!");
        }
        activeBuffs[buffCount++] = { Name, AttBoost, DefBoost, AgiBoost, Dur };
        attack += AttBoost;
        defense += DefBoost;
        agility += AgiBoost;
        cout << name << " applied " << Name << " for " << Dur << " turns." << endl;

    }
    catch (const runtime_error& e)
    {
        cout << e.what() << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error applying buff." << endl;
        system("pause");
    }
}
//Character save Data through file handling
void Character::save(ofstream& out) const 
{
    try
    {
        out << "[Character]" << endl;
        out << "name = " << name << endl;
        out << "level = " << level << endl;
        out << "health = " << health << endl;
        out << "agility=" << agility << endl;
        out << "attack=" << attack << endl;
        out << "defense=" << defense << endl;
        out << "gold=" << gold << endl;
        out << "mana=" << mana << endl;
        out << "experience=" << experience << endl;
        out << "enemies=" << enemies << endl;
        out << "buffCount=" << buffCount << endl;

        for (int i = 0; i < buffCount; i++)
        {
            out << "buff" << i << "=" << activeBuffs[i].name << "," << activeBuffs[i].attackBoost << "," << activeBuffs[i].defenseBoost << "," << activeBuffs[i].turnsLeft << endl;
        }
        inventory->save(out);

        out << "[BattleHistory]" << endl;
        out << "count = " << recordCount << endl;
        for (int i = 0; i < recordCount; i++)
        {
            out << "battle" << i << "=" << battleRecords[i].enemyName << "," << battleRecords[i].outcome << "," << battleRecords[i].experienceGained << endl;
        }

        out << "checksum=12345" << endl;

    }
    catch (const ios_base::failure& e)
    {
        cout << "Error saving character: " << e.what() << endl;
        throw;
    }
    catch (...)
    {
        cout << "Error saving character." << endl;
        throw;
    }
}
//Character load previous saved game Data from file
void Character::load(ifstream& in)
{
    try
    {
        string line;
        while (getline(in, line) && line != "[Inventory]")
        {
            if (line.empty() || line[0] == '[')
            {
                continue;
            }

            int pos = line.find('=');

            if (pos == string::npos)
            {
                throw runtime_error("Invalid save data format.");
            }

            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            if (key == "name")
            {
                name = value;
            }
            else if (key == "level") 
            {
                level = stoi(value);
            }
            else if (key == "health") 
            {
                health = stoi(value);
            }
            else if (key == "agility") 
            {
                agility = stoi(value);
            }
            else if (key == "attack") 
            {
                attack = stoi(value);
            }
            else if (key == "defense") 
            {
                defense = stoi(value);
            }
            else if (key == "gold") 
            {
                gold = stoi(value);
            }
            else if (key == "mana") 
            {
                mana = stoi(value);
            }
            else if (key == "experience") 
            {
                experience = stoi(value);
            }
            else if (key == "enemies") 
            {
                enemies = stoi(value);
            }
            else if (key == "buffCount") 
            {
                buffCount = stoi(value);
            }
            else if (key.find("buff") == 0) 
            {
                int index = stoi(key.substr(4));
                int p1 = value.find(',');
                int p2 = value.find(',', p1 + 1);
                int p3 = value.find(',', p2 + 1);

                if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
                {
                    throw runtime_error("Invalid buff data format.");
                }

                activeBuffs[index].name = value.substr(0, p1);
                activeBuffs[index].attackBoost = stoi(value.substr(p1 + 1, p2 - p1 - 1));
                activeBuffs[index].defenseBoost = stoi(value.substr(p2 + 1, p3 - p2 - 1));
                activeBuffs[index].turnsLeft = stoi(value.substr(p3 + 1));

            }
        }

        getline(in, line);
        int itemCount = stoi(line.substr(6));
        inventory->load(in, itemCount);
        getline(in, line);
        getline(in, line);
        recordCount = stoi(line.substr(6));

        for (int i = 0; i < recordCount && getline(in, line); i++)
        {
            int p1 = line.find('=');
            int p2 = line.find(',', p1 + 1);
            int p3 = line.find(',', p2 + 1);

            if (p1 == string::npos || p2 == string::npos || p3 == string::npos) 
            {
                throw runtime_error("Invalid battle record format.");
            }

            battleRecords[i].enemyName = line.substr(p1 + 1, p2 - p1 - 1);
            battleRecords[i].outcome = line.substr(p2 + 1, p3 - p2 - 1);
            battleRecords[i].experienceGained = stoi(line.substr(p3 + 1));
        }

    }
    catch (const ios_base::failure& e) 
    {
        cout << "Error reading character from file: " << e.what() << endl;
        throw;
    }
    catch (const runtime_error& e)
    {
        cout << "Error loading character: " << e.what() << endl;
        throw;
    }
    catch (...)
    {
        cout << "Error loading character." << endl;
        throw;
    }
}
//Character show Final report when player exiting the game
void Character::showFinalReport() const
{
    try 
    {
        system("cls");
        cout << endl;
        cout << "Final Score Report:" << endl;;
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;
        cout << "Total XP: " << experience << endl;
        cout << "Battles Won: " << enemies << endl;
        cout << "Gold: " << gold << endl;
        system("pause");

    }
    catch (...)
    {
        cout << "Error displaying final report." << endl;
        system("pause");
    }
}

//Warrior constructor 
Warrior::Warrior(string Name, int Level, int Health, int Agility, int Attack, int Defense, int Gold, int Mana, int Amr) : Character(Name, Level, Health, Agility, Attack, Defense, Gold, Mana), armor(Amr) {}
//Use special skill for the player and setting its limit
void Warrior::useSkill() 
{
    try
    {
        if (mana < 10 || skillCooldown > 0)
        {
            if (mana < 10)
            {
                cout << "Not enough mana!" << endl;
            }
            else
            {
                cout << "Skill on cooldown!" << endl;
            }
            return;
        }
        mana -= 10;
        skillCooldown = 3;
        defense += armor / 2;
        cout << "Shield activated: Defense +" << armor / 2 << " for 2 turns." << endl;
        applyBuff("Shield", 0, armor / 2, 0, 2);
       
    }
    catch (...) 
    {
        cout << "Error using Warrior skill." << endl;
        system("pause");
    }
}
//Player level up
void Warrior::levelUp()
{
    try 
    {
        level++;
        health = 80;
        attack += 4;
        defense += 5;
        mana += 3;
        cout << name << " leveled up to " << level << "!" << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error leveling up Warrior." << endl;
        system("pause");
    }
}
//Player attacking the enemy
void Warrior::attackEnemy(Enemy* e) 
{
    try 
    {
        //if enemy Health greater than 0 then proceed to attack else Defeated 
        if (e->getHealth() > 0)
        {
            //if random num less than (player Agility - enemy Agility + 50) then attack proceed else dodged the Hit
            if (rand() % 100 < agility - e->getAgility() + 50)
            {
                //if player attack greater than enemy Defense then it take Damage of enemy otherwise it will be defended by enemy
                if (attack > e->getDefense())
                {
                    //if (player attack - enemy Defense) greater than 10 then it will be Crtical Hit otherwise normal Hit 
                    if (attack - e->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                }
                else
                {
                    cout << e->getName() << " defended the attack sucessfully" << endl;
                    e->takeDamage(1);
                }
            }
            else
            {
                cout << e->getName() << " dodged the hit" << endl;
            }

        }
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Warrior." << endl;
        system("pause");
        return;
    }
}


//Mage constructor 
Mage::Mage(string Name, int Level, int Health, int Agility, int Attack, int Defense, int Gold, int Mana, int Magic) : Character(Name, Level, Health, Agility, Attack, Defense, Gold, Mana), magic(Magic) {}
//Same as Warrior
void Mage::useSkill()
{
    try 
    {
        if (mana < 15 || skillCooldown > 0)
        {
            if (mana < 15)
            {
                cout << "Not enough mana!" << endl;
            }
            else
            {
                cout << "Skill on cooldown!" << endl;
            }
            return;
        }
        mana -= 15;
        skillCooldown = 3;
        attack += magic / 2;
        cout << "Fireball cast: Attack +" << magic / 2 << " for 2 turns." << endl;
        applyBuff("Fireball", magic / 2, 0, 0, 2);
    }
    catch (...) 
    {
        cout << "Error using Mage skill." << endl;
        system("pause");
    }
}
//Same as Warrior
void Mage::levelUp() 
{
    try
    {
        level++;
        health = 70;
        attack += 3;
        defense += 2;
        mana += 5;
        cout << name << " leveled up to " << level << "!" << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error leveling up Mage." << endl;
        system("pause");
    }
}
//Same as Warrior
void Mage::attackEnemy(Enemy* e) 
{
    try 
    {
        if (e->getHealth() > 0)
        {
            if ((rand() % 81 + 20) < agility - e->getAgility() + 50)
            {
                if (attack > e->getDefense())
                {
                    if (attack - e->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                }
                else
                {
                    cout << e->getName() << " defended the attack sucessfully" << endl;
                    e->takeDamage(1);
                }
            }
            else
            {
                cout << e->getName() << " dodged the hit" << endl;
            }

        }

    }
    catch (...) 
    {
        cout << "Error attacking enemy as Mage." << endl;
        system("pause");
    }
}


//Rogue Constructor
Rogue::Rogue(string Name, int Level, int Health, int Agility, int Attack, int Defense, int Gold, int Mana, int Stel) : Character(Name, Level, Health, Agility, Attack, Defense, Gold, Mana), stealth(Stel) {}
//Same as Warrior
void Rogue::useSkill() 
{
    try 
    {
        if (mana < 10 || skillCooldown > 0)
        {
            if (mana < 10)
            {
                cout << "Not enough mana!" << endl;
            }
            else
            {
                cout << "Skill on cooldown!" << endl;
            }
            return;
        }
        mana -= 10;
        skillCooldown = 2;
        agility += stealth / 2;
        cout << "Stealth activated: Agility +" << stealth / 2 << " for 2 turns." << endl;
        applyBuff("Stealth", 0, 0, stealth / 2, 2);
    }
    catch (...) 
    {
        cout << "Error using Rogue skill." << endl;
        system("pause");
    }
}
//Same as Warrior
void Rogue::levelUp()
{
    try 
    {
        level++;
        health = 75;
        attack += 3;
        defense += 3;
        mana += 3;
        cout << name << " leveled up to " << level << "!" << endl;
        system("pause");
    }
    catch (...) 
    {
        cout << "Error leveling up Rogue." << endl;
        system("pause");
    }
}
//Same as Warrior
void Rogue::attackEnemy(Enemy* e)
{
    try
    {
        if (e->getHealth() > 0)
        {
            if (rand() % 100 < agility - e->getAgility() + 50)
            {
                if (attack > e->getDefense())
                {
                    if (attack - e->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                }
                else
                {
                    cout << e->getName() << " defended the attack sucessfully" << endl;
                    e->takeDamage(1);
                }
            }
            else
            {
                cout << e->getName() << " dodged the hit" << endl;
            }

        }
        
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Rogue." << endl;
        system("pause");
    }
}


//Archer constructor
Archer::Archer(string Name, int Level, int Health, int Agility, int Attack, int Defense, int Gold, int Mana, int Rng) : Character(Name, Level, Health, Agility, Attack, Defense, Gold, Mana), range(Rng) {}
//Same as Warrior
void Archer::useSkill()
{
    try
    {
        if (mana < 12 || skillCooldown > 0)
        {
            if (mana < 12)
            {
                cout << "Not enough mana!" << endl;
            }
            else
            {
                cout << "Skill on cooldown!" << endl;
            }
            return;
        }
        mana -= 12;
        skillCooldown = 3;
        attack += range / 2;
        cout << "Precision Shot: Attack +" << range / 2 << " for 2 turns." << endl;
        applyBuff("Precision", range / 2, 0, 0, 2);
    }
    catch (...) 
    {
        cout << "Error using Archer skill." << endl;
        system("pause");
    }
}
//Same as Warrior
void Archer::levelUp() 
{
    try 
    {
        level++;
        health = 70;
        attack += 4;
        defense += 2;
        mana += 3;
        cout << name << " leveled up to " << level << "!" << endl;
        system("pause");
    }
    catch (...)
    {
        cout << "Error leveling up Archer." << endl;
        system("pause");
    }
}
//Same as Warrior
void Archer::attackEnemy(Enemy* e)
{
    try
    {
        if (e->getHealth() > 0)
        {
            if ((rand() % 61 + 40) < agility - e->getAgility() + 50)
            {
                if (attack > e->getDefense())
                {
                    if (attack - e->getDefense() > 10)
                    {
                        cout << "Critical Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                    else
                    {
                        cout << "Hit on the " << e->getName() << " for " << attack - e->getDefense() << " damage" << endl;
                        e->takeDamage(attack - e->getDefense());
                    }
                }
                else
                {
                    cout << e->getName() << " defended the attack sucessfully" << endl;
                    e->takeDamage(1);
                }
            }
            else
            {
                cout << e->getName() << " dodged the hit" << endl;
            }

        }
       
    }
    catch (...) 
    {
        cout << "Error attacking enemy as Archer." << endl;
        system("pause");
    }
}
