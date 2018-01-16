# PokeTCG User Guides
___

## **Content**
___
### 1. **[Introduction](#introduction)**
### 2. **[How do I make a card and a deck for PokeTCG?](#making-cards-and-decks)**
### 3. **[How do I make an AI for PokeTCG?](#making-ais)**
### 4. **[How to play our game?](#how-to-play)**
___

## **Introduction**
___

- PokeTCG is a project for our assignment to create a platform for simulating Pokemon Trading Card Game. It is coded in C++ with [Qtcreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/), python script and bound with [pybind11](https://pybind11.readthedocs.io/en/stable/).

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

> **[Decklist](#decklist)**
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
___
### **Decklist**

- **A decklist contains all cards' set ID including duplicates:**

```json
{
    "Name" : "Bright Tide",
    "Deck" : [
       41,
       41,
       40,
       40,
       39,
       39,
       39,
       29,
       28,
       28,
       34,
       37,
       37,
       36,
       36,
       33,
       33,
       50,
       49,
       49,
       53,
       53,
       104,
       104,
       103,
       103,
       97,
       97,
       116,
       120,
       120,
       122,
       123,
       123,
       127,
       127,
       128,
       134,
       134,
       135,
       166,
       166,
       166,
       166,
       166,
       166,
       166,
       166,
       166,
       166,
       166,
       166,
       167,
       167,
       167,
       167,
       167,
       167,
       167,
       167
    ]
}

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
//----------------------------------------------------------------------------------------  
  /// @brief getter method for retrieving the name of the deck
//--------------------------------------------------------------------------------------
virtual std::string deckName() const = 0;
//----------------------------------------------------------------------------------------
  /// @brief card choice method
  /// @param [in] _player owner of the card pile
  /// @param [in] _origin the card pile where the options currently are
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
  /// @return the indices of the picked cards, in _options
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
  /// @param [in] _owner owner of the slots
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options slots to choose from
  /// @param [in] _amount amount of slots to choose (if possible)
  /// @return the indices of the picked slots, in _options
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
  /// @param [in] _owner owner of the pokemon
  /// @param [in] _destination  the card pile where the energy will be moved to
  /// @param [in] _action  the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
  /// @return the indices of the picked energy cards, in _options
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
  /// @param [in] _owner owner of the pokemon
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
  /// @return the decision, true for agree and false for disagree
//--------------------------------------------------------------------------------------
virtual bool agree(const PTCG::ACTION _action) = 0;
//----------------------------------------------------------------------------------------
  /// @brief method for the players turn; decision making, card playing, attacking, retreating, etc...
  /// @return a pair containing a bool for whether you want to attack, and the index of the attack if you do
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
 ___
### **Turn Simulation:**

It is useful for an AI to be able to simulate a turn, and evaluate the outcome of their actions.

We have a simple frame work in place to do this, however it is slightly more involved than writing a non-simulating AI.

Within the core we have a class called ```StrategyPlayer```, you will need to include this as it is a key part of simulation.

If you are familiar with the "Strategy Pattern" this may look familiar. We will also use the ```getDummyGame``` function provided by the player class,
which your AI should already inherit from.

The first thing you'll want to do is write the turn functions for self and enemy, which will be executed by the simulation.

```cpp

void selfTurnSim(Player* _dummySelf)
{
  // View our hand
  auto hand = _dummySelf->viewHand();
  // If we have any cards in the hand, and the first one is playable
  if (hand.size() && _dummySelf->canPlay(0))
    // Play the first card
    _dummySelf->playCard(0);
  // Don't attack
  return std::pair<bool, unsigned> {false, 0};
}

void enemyTurnSim(Player* _dummyEnemy)
{
  // Essentially saying do nothing.
  return std::pair<bool, unsigned> {false, 0};
}
```
Then in your AI's turn function, you need to get a dummy game to run the simulations on.
```cpp
Game dummy = getDummyGame();
```
The next step is to create two Strategy Players, these will replace you and your opponent in the simulation.

We need to pass the dummy Game to these players, to inform them that they are participants to that Game.

We also pass a pointer to your AI, which will be cloned and used to fill in the other parts of the Player interface, such as choose cards, slots etc.
```cpp
StrategyPlayer dummySelf(&dummy, this);
StrategyPlayer dummyEnemy(&dummy, this);
```
We then register the two players with the dummy game, and tell it which player is which.
```cpp
dummy.registerPlayer(&dummySelf, PTCG::PLAYER::SELF);
dummy.registerPlayer(&dummyEnemy, PTCG::PLAYER::ENEMY);
```
Finally we need to call ```setTurn``` for both players and pass the functions you wrote earlier.

This will set the turn function for those players to whatever you wish to simulate.
```cpp
dummySelf.setTurn(selfTurnSim);
dummyEnemy.setTurn(enemyTurnSim);
```
Now you can call nextTurn as many times as you want and view the outcome.
```cpp
// Finally we call next turn, this can be called as many times as you'd like
dummy.nextTurn();

// You can then queery the current game state by calling the view functions on the dummy game
auto checkBench = dummySelf.viewBench();
```
 ___

**[Back To Top](#poketcg-user-guides)**
___
## **How to play**
___
- **[Board](#board-and-prompt-interface)**
- **[Commands](#commands)**
- **[Rules](#rules)**
___
-This game's UI is WIP and currently we recommend playing in a maximised terminal. 

### **Board and Prompt Interface**
___
> **Example Board State:**
```
PRIZE:

*---**---**---**---**---**---*
| ? || ? || ? || ? || ? || ? |
*---**---**---**---**---**---*
Taking card from top of deck.
Lightning Energy has been put into the hand.
PRIZE:

*---**---**---**---**---**---*
| ? || ? || ? || ? || ? || ? |
*---**---**---**---**---**---*
BENCH:

*--------------**-------------**--------------**------------**--------------*
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
*--------------**-------------**--------------**------------**--------------*

ACTIVE:

*[  39/149][ 70/  70hp]*
| Popplio         [  W]|
| Energy:   0x         |
| Tool:          ---   |
|----------------------|
| Pound      10 (    W)|
| Water Gu   20 (   WC)|
|----------------------|
| [  G]  [   -]  [  1] |
| [                  ] |
*----------------------*
ACTIVE:

*[  53/149][ 70/  70hp]*
| Togedemaru      [  L]|
| Energy:   0x         |
| Tool:          ---   |
|----------------------|
| Defense       (    C)|
| Discharg  30x (    L)|
|----------------------|
| [  F]  [   M]  [  1] |
| [                  ] |
*----------------------*
BENCH:

*--------------**-------------**--------------**------------**--------------*
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
|              ||             ||              ||            ||              |
*--------------**-------------**--------------**-------------**-------------*

HAND:

*---[  ITEM]---**---[ENERG]----**---[ENERG]----**---[  POKE]---**--[  ITEM]--**--[ENERG]---*
|Nest Ball   ||       ____   ||      /=====/ ||Primar  [ 150]||Nest Ball    ||      /=====/ |
|            ||     **'`     ||     /====/   ||         [  W]||             ||     /====/   |
|            ||   *'  |      ||    /===/     ||Disarming     ||             ||    /===/     |
| ---------- ||  /     *_    ||      /====/  ||  30        WC||  ---------- ||      /====/  |
|  |TRAINERS||| |        '.  ||     /===/    ||Sparkling     ||  |TRAINERS| ||     /===/    |
|  ----------|| '  *``*   }  ||    /==/      || 100       WWC||  ---------- ||    /==/      |
|            ||  \{    }  /  ||   /=/        ||[  G]    [  -]||             ||   /=/        |
|            ||   '*__*_*'   ||  /           ||[  2]         ||             ||  /           |
*------------**--------------**--------------**--------------**-------------**--------------*
PRIZE:

*---**---**---**---**---**---*
| ? || ? || ? || ? || ? || ? |
*---**---**---**---**---**---*
What do you want to do?

```

___
### **Commands**
___

> ### **These are all/most of what you need to know to traverse the current UI**


> At the start of the game, a prompt:
```
Pick a card from 1 - n, to play from your hand

```
> This prompt asks you to play a basic Pokemon from your hand. 

> 1-n is the index of the Basic Pokemon in hand from left to right.

> **During:**

```
What do you want to do?
```
> **You have several commands available to type into the terminal:**
``` 
- play / play %cardIndexInHand% / play %cardIndexInHand% %optionIndex%

Plays a card from hand, you can attach an index of the card in hand after play to say which card to play from hand. 

If you type "play" with no extensions, the game will prompt you with the selections.

Sometimes if you attach cards onto the bench. 

You can also put an index for which bench to attach the card to 

(%optionIndex%) AFTER %cardIndexInHand%. Remember that it's not necessarily bench index, it is the index of the playable slots.

                                                  _________________

- retreat

Retreats a pokemon, the game prompts you to choose the substituting Pokemon, see below:

What do you want to do?
> retreat
Pick a card from 1 - 1, to move from your bench
> 1
Pick a card from 1 - 1, to discard from your active pokemon
> 1
Lightning Energy has been discarded.
 
                                                  _________________

- attack / attack %attackIndex%

You either end your turn with an attack or a "skip". 

If you type "attack", the game prompts you to use which attack on your Active Pokemon or you can call attack with a decided attackIndex. 

Index increases rom the top to the bottom.
                                                  _________________

- skip 

If you type skip, you end your turn without attacking.

```
___
### **Rules**
___

The rules are based on the current PTCG Ruling which you can find [here](https://www.pokemon.com/uk/pokemon-tcg/).

**[Back To Top](#poketcg-user-guides)**
___
