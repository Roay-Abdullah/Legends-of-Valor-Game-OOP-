## Legends of Valor - OOP Semester Project

## Overview
Legends of Valor is a text-based role-playing game (RPG) developed as a semester project for an Object-Oriented Programming (OOP) course. This project demonstrates the application of OOP principles such as inheritance, polymorphism, encapsulation, and abstraction through a fully functional game. The game allows players to create characters, explore different areas, engage in turn-based battles with enemies, manage inventory, and save/load game progress. It is developed entirely in C+.


## Features
Character Classes: Choose from four unique classes (Warrior, Mage, Rogue, Archer), each with distinct attributes and special skills.
Turn-Based Combat: Engage in strategic battles against variousNIEs like Wolves, Goblins, Zombies, Dragons, and a powerful Boss, with a dynamic combat system including critical hits, dodging, and defending.
Inventory System: Manage items like potions and buffs to enhance gameplay.
Exploration: Explore diverse areas (Forest, Cave, Town, Dungeon) with unique events and enemy encounter rates.
Save/Load System: Save and load game progress using file handling.
Battle History: Track your battles and view detailed statistics.
Dynamic Events: Random events in each area, such as finding healing herbs or triggering traps.


## Project Structure
The project is organized into multiple C++ files, each handling specific game components:

Character.h/cpp: Defines the base Character class and derived classes (Warrior, Mage, Rogue, Archer) with attributes like health, attack, and special skills.
Enemy.h/cpp: Implements enemy classes (Wolves, Goblin, Zombie, Dragon, Boss) with unique attack behaviors.
Area.h/cpp: Manages game areas with unique descriptions, enemy encounter rates, and events.
Item.h/cpp: Handles items like potions and buffs with consumable effects.
Inventory.h/cpp: Manages the player's inventory with a limit of 10 items.
main.cpp: Contains the game loop, user input handling, and core game logic.


## How to Play
Launch the game and enter your name.
Choose a character class (Warrior, Mage, Rogue, or Archer).
Use the menu to:
Explore areas and encounter enemies or events.
View character statistics.
Manage inventory (use or remove items).
Review battle history.
Save or load game progress.
Quit the game to view the final score report.


During battles, choose actions like attacking, using skills, items, or defending strategically.


## OOP Concepts Demonstrated
Inheritance: Character and Enemy classes use inheritance for shared functionality.
Polymorphism: Virtual functions like useSkill(), levelUp(), and attackEnemy() allow class-specific implementations.
Encapsulation: Private/protected attributes and public methods ensure controlled access.
Abstraction: Abstract base classes (Character, Enemy, Area, Item) hide implementation details.
Dynamic Memory Management: Proper use of pointers and destructors for inventory and enemies.
File I/O: Save and load game data using file streams.


## Known Issues
Error Handling: The game uses try-catch blocks extensively, but some errors may cause pauses due to system("pause").
Platform Dependency: The system("cls") and system("pause") commands are Windows-specific. For cross-platform compatibility, consider replacing them with platform-independent alternatives.
Balance: Some enemy encounters or item effects may need balancing for optimal gameplay.


## Future Improvements
Add a graphical user interface (GUI) using a library like SFML or SDL.
Implement cross-platform support for Linux and macOS.
Enhance the save/load system with encryption or compression.
Introduce more character classes and enemy types.
Add multiplayer support for cooperative gameplay.


Inspired by classic text-based RPGs and modern C++ programming practices.

