# PokeTCG User Guides
___

## **Content**
___
### 1. **[Introduction](#introduction)**
### 2. **[How do I make a card and a deck for PokeTCG?](#making-cards-and-decks)**
### 3. **[How do I make an AI for PokeTCG?](#making-ais)**
### 4. **More to come in the future.**
___

## **Introduction**
___

- PokeTCG is a project for our assignment to create a platform for simulating Pokemon Trading Card Game. It is coded in C++, python script and bound with [pybind11](https://pybind11.readthedocs.io/en/stable/).

- The current version contains the SUM Starter Decks and is played in a terminal with ASCII-based GUI.

___

## **Making cards and decks**
___
**For each card:**

- Prepare a .json file to store static data fields of a card. 
- Prepare a .py file to implement the card behaviour with named functions. 
- Both files should be in the same directory as of the current version, named after their set.

 **See below**
___
> **[Pokemon Cards](#pokemon-cards)**

> **[Trainer Cards](#trainer-cards)**

> **[Energy Cards](#energy-cards)**
___
### **Pokemon Cards:**
> ### **Json File:**
```json
##9.json
{
    "ID" : 9,               // Set ID of a Card
    "Name" : "Rowlet",      // Name of a Card
    "HP" : 60,              // HP of a Pokemon
    "Type" : "G",           // Type of a Pokemon, 
    "Weakness" : "R",       // Weakness of a Pokemon, "" if none exists
    "Resistance" : "",      // Resistance of a Pokemon, "" if none exists
    "Retreat" : 1,          // Retreat cost of a Pokemon
    "Stage" : 0,            // Evolution Satge: Basic is zero, then Stage 1...etc
    "Pre evolution" : "",   // Name of the pokemon's pre-evolution, empty for stage 0 
    "Attacks" : {           
        "Tackle" : {        // Name of attack for static analysis
            "Func" : "tackle",          // name of attack function in .py file
            "BaseDamage" : "10",        // base damage text
            "Energy" : "C"              // energy requrirement C, see energy codes
        },
        "Leafage" : {
            "Func" : "leafage",
            "BaseDamage" : "20",
            "Energy" : "GC"
        }
    }
}
```
>### **Energy Codes:**

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

'''
h is an instance of the game state/(h)ub, 
and the function name matches json field
'''
def tackle(h): 
    #calling dealDamage to do 10 damage to the opponent
    h.dealDamage(10) 


def leafage(h): 
    h.dealDamage(20)
```
___
### **Trainer Cards:**
> ### **Json File:**
```json
##128.json
{
    "ID" : 128,
    "Name" : "Professor Kukui",
    "Trainer" : "S",                //Type of Trainer Cards, see Trainer Type Codes
    "Ability" : {
        "Func" : "professorKukui",
        "Duration" : "S",           //Effect Duration, see Effect Duration
        "Trigger" : "N"             //Activation phase, see effect trigger codes
    }
}
```
> ### **Python Script:**
```python
#128.py
import poke as p 

'''
Some card effects such as: "Put 2 energy cards into your deck.", have constraints on when they,
can be played. You must implement a canPlay function to make sure these constraints are satisfied.
'''
def canPlay(h):
    # if deck has at least two cards 
    return h.numCards(p.PLAYER.SELF, p.PILE.DECK) >= 2

def professorKukui(h):
    # draw two cards
    for i in range(2):
        h.drawCard(p.PLAYER.SELF)
    # your Pokemon's attacks do 20 more damage to your opponent's,
    # active Pokemon (before applying Weakness and Resistance).	
    h.addBonusDamage(20, p.ORDER.BEFORE, p.PLAYER.SELF)
    
```
>### **Trainer Type Codes:**
- [I]tem
- [T]ool
- [S]upporter
- St[A]dium
>### **Effect Trigger Codes:**
- [N]OW,
- [S]TART
- [A]TTACK,
- [E]ND
>### **Effect Duration Codes:**
- [S]INGLE,
- [M]ULTIPLE,
- [P]ERMANENT

___
### **Energy Cards:**
> ### **Json File:**
```json
##169.json
{
    "ID" : 169,
    "Name" : "Fighting Energy",
    "Type" : "F"  //See Energy Codes
}
```
> ### **Python Script:**
```python
'''
Due to time constraints, we are only allowing Basic Energy Cards in this set. 
Function implementation for basic energy cards are not required.
'''
```
**[Back To Top](#poketcg-user-guides)**
___

## **Making AIs**
___

- **[Examples](#example)**
___

### **Ai Concepts**

- You might want to check out our Documentations on Game, Player Class and any of their children.

- The Game Core will call certain Player methods when actions are needed such as "selecting cards to act upon".

**See Below** 
- These are the functions you **have** to define inside your Ai for the Game to communicate:

 ```cpp
//----------------------------------------------------------------------------------------
  /// @brief object cloning method
//--------------------------------------------------------------------------------------
virtual Player* clone() const = 0;  
//----------------------------------------------------------------------------------------  /// @brief getter method for retrieving the name of the deck
//--------------------------------------------------------------------------------------
virtual std::string deckName() const = 0;
//----------------------------------------------------------------------------------------
  /// @brief card choice method
  /// @param [in] _player owner of the card pile
  /// @param [in] _origin the card pile where the options currently are
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
//--------------------------------------------------------------------------------------
virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;
//----------------------------------------------------------------------------------------
  /// @brief slot choice method
  /// @param [in] _owner owner of the card pile
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options slots to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
//--------------------------------------------------------------------------------------
virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) = 0;
//----------------------------------------------------------------------------------------
  /// @brief method to reveal cards to the player
  /// @param [in] _owner owner of the card pile
  /// @param [in] _origin the card pile where the cards currently are
  /// @param [in] _indices the locations of the revealed cards in _origin
  /// @param [in] _revealed the revealed cards
//--------------------------------------------------------------------------------------
virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) = 0;
//----------------------------------------------------------------------------------------
  /// @brief method for choosing energy cards attached to a pokemon
  /// @param [in] _owner owner of the card pile
  /// @param [in] _destination  the card pile where the energy will be moved to
  /// @param [in] _action  the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
//--------------------------------------------------------------------------------------
virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;
//----------------------------------------------------------------------------------------
  /// @brief method for choosing a condition that the active pokemon is suffering from
  /// @param [in] _owner owner of the card pile
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options conditions to choose from
  /// @param [in] _amount amount of conditions to choose
  /// @return the indices of the picked conditions, in _options
//--------------------------------------------------------------------------------------
 virtual std::vector<size_t> chooseConditions(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<PTCG::CONDITION> &_options,
      const unsigned _amount
      ) = 0;
//----------------------------------------------------------------------------------------
  /// @brief prompt player to agree to perform action or not
  /// @param [in] _action an action to evaluate
//--------------------------------------------------------------------------------------
virtual bool agree(const PTCG::ACTION _action) = 0;
//----------------------------------------------------------------------------------------
  /// @brief method for the players turn; decision making, card playing, attacking, retreating, etc...
  /// @return bool for whether you declare attack, unsigned for which attack of the active pokemon if you do declare attack
//--------------------------------------------------------------------------------------
virtual std::pair<bool, unsigned> turn() = 0;
 ```
 ___
### **Example:**
```
Clone usually is the same for Ai codes
```
```cpp
Player* SomeAi::clone() const
{
  return new SomeAi(*this);
}
```
___
```
You can use these parameters passed from the Game Core to determine the selection of cards and slots in different situations.

It's usually preferred to define another logs function outside of the overriden methods to keep this function clean.
```
```cpp
std::vector<size_t> SomeAi::chooseCards(
    const PTCG::PLAYER _player, 
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  return yourImplementedLogics(...);
}
```
```cpp
std::pair<bool, unsigned> SomeAi::turn()
{
  m_turnFinished = false;
  m_doAttack = false;
  while(!m_turnFinished)
  {  
    /*
    Do all the thinking and actions in here and finish when your Ai thinks it's enough.
    Remeber to implement the complex logics in other methods to keep this turn loop clean.
    */
    auto decision = think(...);
    m_parentGame.playCard(...);
    m_turnFinished = finished(...);
  }
  // Return the decision
  return std::pair<bool, unsigned> {m_doAttack, m_attackID-1};
}
```
**[Back To Top](#poketcg-user-guides)**
