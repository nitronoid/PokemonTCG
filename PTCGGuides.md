# PokeTCG User Guides
___

## Content
___
### 1. **[Introduction](#introduction)**
### 2. **[How do I make a card and a deck for PokeTCG?](#making-cards-and-decks)**
### 3. **[How do I make an AI for PokeTCG?](#making-ais)**
### 4. **More to come in the future.**
___

## Introduction
___

    PokeTCG is a project for our assignment to create a platform for simulating Pokemon Trading Card Game. It is coded in C++, python script and bound with [pybind11](https://pybind11.readthedocs.io/en/stable/).

    The current version contains the SUM Starter Decks and is played in a terminal with ASCII-based GUI.

___

## Making cards and decks
___
**For each card:**

- Prepare a .json file to store static data fields of a card. 
- Prepare a .py file to implement function implementation as python scripts. 
- Both files should be in the same directory as of the current version.

 **See below**
___
> **[Pokemon Cards](#pokemon-cards)**

> **[Trainer Cards](#trainer-cards)**

> **[Energy Cards](#energy-cards)**
___
### **Pokemon Cards:**
> ### **Json File:**
```cpp
//9.json
{
    "ID" : 9,               // Set ID of a Card
    "Name" : "Rowlet",      // Name of a Card
    "HP" : 60,              // HP of a Pokemon
    "Type" : "G",           // Type of a Pokemon, 
    "Weakness" : "R",       // Weakness of a Pokemon, "" if none exists
"Resistance" : "",          // Resistance of a Pokemon, "" if none exists
    "Retreat" : 1,          // Retreat cost of a Pokemon
    "Stage" : 0,            // Evolution Satge: 0 - Basic, 1 - Stage 1...etc
    "Pre evolution" : "",   // Name of the pokemon's pre-evolution, empty for stage 0 
    "Attacks" : {           
        "Tackle" : {        // Name of attack
            "func" : "tackle",          // name of attack function in .py file
            "baseDamage" : "10",        // base damage text
            "energy" : "C"              // energy requrirement C, see function acronyms 
        },
        "Leafage" : {
            "func" : "leafage",
            "baseDamage" : "20",
            "energy" : "GC"
        }
    }
}
```
>### **Energy Acronyms:**

- [C]olorless (Normal, Flying, older cards also Dragon)
- [F]ighting (Fighting, Rock, Ground)
- [L]ightning (Electric)
- [G]rass (Grass, Bug, older cards also Poison)
- [P]sychic (Psychic, Ghost, Poison)
- [M]etal (Steel)
- [W]ater (Water, Ice)
- [D]arkness (Dark)
- Fi[R]e (Fire)
- Drago[N] (Dragon)
- Fair[Y] (Fairy)

> ### **Python script:**
```python
#9.py
import poke # this is the bound cpp module to be included 

def tackle(h): #h as an instance of the game state, function name matches json field
    h.dealDamage(10,0) #calling a deal damage function to do obvious things


def leafage(h): 
    h.dealDamage(20,0)
```
___
### **Trainer Cards:**
> ### **Json File:**
```cpp
//128.json
{
    "ID" : 128,
    "Name" : "Professor Kukui",
    "Trainer" : "S",                //Type of Trainer Cards, see Trainer Type Acronyms
    "Ability" : {
        "func" : "professorKukui",
        "duration" : "S",           //Effect Duration, see Effect Duration
        "phase" : "M"               //Activation phase............
    }
}
```
> ### **Python Script:**
```python
#128.py
import poke as p 

# if you need to have certain constraints on card effects such as: 
# > "Put 2 energy cards into your deck." 
# Check available functions in the game core for scripts and declare a function to filter cards in card piles. 
def filter(card): 
    return True
# All trainer cards need a canPlay(h) for checking if the card be played or not
# check for rulings on specific cards and implement this function
def canPlay(h):
    # if deck has more than two cards 
    return len(h.viewDeck(p.PLAYER.SELF)) >= 2

def professorKukui(h):
    for i in range(2):
        h.drawCard(p.PLAYER.SELF)
    # your Pokemon's attacks do 20 more damage to your opponent's 
    # active Pokemon (before applying Weakness and Resistance).	
    h.addBonusDamage(20, p.ORDER.BEFORE, p.PLAYER.SELF)
```
>### **Trainer Type Acronyms:**
- [I]tem
- [T]ool
- [S]upporter
- St[A]dium
>### **Effect Duration:**

- [S]INGLE,
- [M]ULTIPLE,
- [P]ERMANENT

___
### **Energy Cards:**
> ### **Json File:**
```cpp
//169.json
{
    "ID" : 169,
    "Name" : "Fighting Energy",
    "Type" : "F"  //See Energy Acronyms
}
```
> ### **Python Script:**
```cpp
//Due to time constraints, we are only allowing Basic Energy Cards in this set, therefore, function implementation for energy cards are not needed for Basic Energy Cards.
```

___

## Making AIs
___

- I'm lazy, break time.