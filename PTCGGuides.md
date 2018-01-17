# PokeTCG User Guides
___

## **Content**
___
### 1. **[Introduction](#introduction)**
### 2. **[How do I make a card and a deck for PokeTCG? Or anything Technical?](#making-cards-and-decks)**
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

> **[Details of implementation](#details-of-implementations)**
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
___

### **Details of Implementations**

- **[Checking Board States](#checks-and-view-methods)**
- **[Activating Effects](#operations-affecting-game-state)**
- **[Interactive and Choice Prompt](#interactive-functions)**
- **[Delayed or Persistent Effects](#delayed-or-persistent-effects)**
- **[ASCII Printer](#ascii-printer)**

> These card implementations are not handled by the core, we simply call your functions when needed.

**In .py:**
- **bool canPlay(h)** returns true if card is playble at this point of the game. This is required for implementing Trainer cards.
- **void cardEffect(h)** method name is the card's name and you impllement the card's effects here.

(h is an instance of our core so it would change if you name it differently.)

> **There are view functions that you can access for checking if a Trainer card can be played:**
___

#### **Checks and View Methods**

- **These are the functions for viewing board states and accessing factors that affect you decisions and canPlay functions**

```cpp 
//------------------------------------------------------------------------------
  /// @brief a function that returns the number of cards in a pile.
  /// @param [in] _owner is the player who owns the pile
  /// @param [in] _pile is the pile to check
  /// @return the number of cards in the pile
  //----------------------------------------------------------------------------
size_t numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const; 

//------------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in a pile
  /// @param [in] _owner is the player who owns the pile
  /// @param [in] _pile is the pile that contains the cards
  /// @return a copy of all cards in that pile
  //----------------------------------------------------------------------------
std::vector<std::unique_ptr<Card>>  viewPile(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const;
  //---------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in the deck
  /// @param [in] _owner is the player who owns the deck
  /// @return a copy of all cards in that deck
  //--------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewDeck(const PTCG::PLAYER &_player)    const;
  //-------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in the discard pile
  /// @param [in] _owner is the player who owns the discard pile
  /// @return a copy of all cards in that discard pile
  //-------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewDiscard(const PTCG::PLAYER &_player) const;
  //-------------------------------------------------------------------------
  /// @brief function that copies and returns all cards in the hand
  /// @param [in] _owner is the player who owns the hand
  /// @return a copy of all cards in that hand
  //-------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>>  viewHand(const PTCG::PLAYER &_player)    const;
  //-------------------------------------------------------------------------
  /// @brief function that copies and returns all prize cards
  /// @param [in] _owner is the player who owns the prize cards
  /// @return a copy of all prize cards
  //------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card> > viewPrize(const PTCG::PLAYER &_player)   const;
  //------------------------------------------------------------------------
  /// @brief function that copies and returns all slots on the bench including the active
  /// @param [in] _owner is the player who owns the bench
  /// @return a copy of all slots in the bench
  //------------------------------------------------------------------------
  std::array<BoardSlot, 6>            viewBench(const PTCG::PLAYER &_player)   const;
  //-------------------------------------------------------------------------------------
  /// @brief gets a copy of the active status
  /// @param [in] _owner is the player who owns the status
  /// @return a copy of the _owners active status
  //-------------------------------------------------------------------------------------
  Status viewStatus(const PTCG::PLAYER _owner) const;
  //------------------------------------------------------------------------
  /// @brief gets the current tunr count
  /// @return the current turn count
  //------------------------------------------------------------------------
  unsigned turnCount() const;
```
**[Back To Implementation Section](#details-of-implementations)**
___

#### **Operations Affecting Game State**

- **These are the functions used for effect implementation which will affect the board:**

```cpp
//------------------------------------------------------------------------------------------
  /// @brief function called when a card wants to deal damage through an attack, which takes into account weakeness and
  /// resistance using the damage calculator.
  /// @param [in] _damage is the raw amount of damage to inflict before caclculation.
  /// @param [in] _id is the index in the opponents bench for the damage to be dealt to, 0 is the active pokemon.
  /// @param [in] _applyWeak is a switch that can be used to avoid weakness and resistance calculation.
  //----------------------------------------------------------------------------------------
  void dealDamage(const int _damage, const size_t _id = 0, const bool &_applyWeak = true);
  //----------------------------------------------------------------------------------------
  /// @brief function used to apply damage through an effect such as burn or poison. This can be done to self or opponent.
  /// @param [in] _damage is the raw amount of damage to inflict
  /// @param [in] _player a flag telling us who to inflict the damage on
  /// @param [in] _id is the index of the pokemon in the players board to deal damage to.
  //----------------------------------------------------------------------------------------
  void addDamageCounter(const int _damage, const PTCG::PLAYER _player = PTCG::PLAYER::ENEMY, const unsigned _id = 0);
  //----------------------------------------------------------------------------------------
  /// @brief this function is used to remove an amount of damage from a pokemon. This can only done to the self
  /// @param [in] _heal is the amount of damage to remove from the pokemon.
  /// @param [in] _id is the index in the current players bench for the damage to removed from, 0 is the active pokemon
  //----------------------------------------------------------------------------------------
  void healDamage(const int _heal, const unsigned _id = 0);
  //----------------------------------------------------------------------------------------
  /// @brief this function is used to add bonus damage to an attack that happens this turn. Is cleared upon end of turn.
  /// @param [in] _value is the amount of damage to add to the attack.
  /// @param [in] _order refers to whether or not the bonus should be applied before or after damage calculation
  /// @param [in] _player is the player who's attack is given the bonus
  //----------------------------------------------------------------------------------------
  void addBonusDamage(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  //----------------------------------------------------------------------------------------
  /// @brief this function is used to lower the damage done by an attack this turn. Is cleared upon end of turn.
  /// @param [in] _value is the amount of damage to lower the attack damage by.
  /// @param [in] _order refers to whether or not the bonus should be applied before or after damage calculation
  /// @param [in] _player is the player who's attack is lowered
  //----------------------------------------------------------------------------------------
  void addBonusDefense(const unsigned &_value, const PTCG::ORDER &_order, const PTCG::PLAYER &_player = PTCG::PLAYER::SELF);
  //----------------------------------------------------------------------------------------
  /// @brief applies a condition to the _target's active pokemon
  /// @param [in] _target is the player, who's active should be affected.
  /// @param [in] _condition is the condition to apply
  //----------------------------------------------------------------------------------------
  void applyCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  //----------------------------------------------------------------------------------------
  /// @brief removes a condition from the _target's active pokemon
  /// @param [in] _target is the player, who's active should be now be unaffected by _condition
  /// @param [in] _condition is the condition to remove
  //----------------------------------------------------------------------------------------
  void removeCondition(const PTCG::PLAYER &_target,const PTCG::CONDITION &_condition);
  //----------------------------------------------------------------------------------------
  /// @brief removes all conditions from _target's active pokemon
  /// @param [in] _target is the player, who's active should be now be unaffected by any conditions
  //----------------------------------------------------------------------------------------
  void removeAllConditions(const PTCG::PLAYER &_target);
  //----------------------------------------------------------------------------------------
  /// @brief sets the canRetreat value for _affected's active pokemon
  /// @param [in] _affected is the player who's active should be set
  /// @param [in] _val is the value to set
  //----------------------------------------------------------------------------------------
  void setCanRetreat(const PTCG::PLAYER &_affected, const bool _val = false);
  //----------------------------------------------------------------------------------------
  /// @brief sets the isProtected value for _affected's active pokemon
  /// @param [in] _affected is the player who's active should be set
  /// @param [in] _val is the value to set
  //----------------------------------------------------------------------------------------
  void setProtected(const PTCG::PLAYER &_affected, const bool _val = true);
  //----------------------------------------------------------------------------------------
  /// @brief function that removes energy card(s) from a slot and moves them to a card pile
  /// @param [in] _owner is the player who owns the slot and energy
  /// @param [in] _destination is the pile to move the cards to
  /// @param [in] _slotIndex is the index of the slot to remove energies from
  /// @param [in] _indices are the indices of the energy to move from the _origin pile
  //----------------------------------------------------------------------------------------
  void removeEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const size_t _slotIndex,
      std::vector<size_t> _indices
      );
  //----------------------------------------------------------------------------------------
  /// @brief function used to simulate the outcome of flipping one or more coins
  /// @param [in] _num is the amount of coin flips to be simulated
  /// @return the amount of heads
  //----------------------------------------------------------------------------------------
  unsigned flipCoin(const unsigned _num);
  //----------------------------------------------------------------------------------------
  /// @brief shuffles _owner's deck
  /// @param [in] _owner the player who's deck should be shuffled
  //----------------------------------------------------------------------------------------
  void shuffleDeck(const PTCG::PLAYER _owner);

  //----------------------------------------------------------------------------------------
  /// @brief function that moves the top card of the players deck to their hand
  /// @param [in] _player is the player who will draw a card
  /// @return whether or not the player could draw a card
  //----------------------------------------------------------------------------------------
  bool drawCard(const PTCG::PLAYER _player);

  //----------------------------------------------------------------------------------------
  /// @brief function that reveals a list of cards to the player
  /// @param [in] _learner is the player to whom the cards are revealed
  /// @param [in] _owner is the player who owns the cards
  /// @param [in] _origin is the pile that contains the cards
  /// @param [in] _indices tells the player the position of each card in _origin
  //----------------------------------------------------------------------------------------
  void revealCards(
      const PTCG::PLAYER _learner,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices
      );

  //----------------------------------------------------------------------------------------
  /// @brief function that moves cards from a pile to bench slots. There should be exactly one bench index for every card index.
  /// @param [in] _owner is the player who owns the slots
  /// @param [in] _origin is the pile to move the cards from
  /// @param [in] _pileIndex a list of indices, each refers to a card in the _origin pile to move
  /// @param [in] _benchIndex a list of indices, each refers to a slot to move a card into
  //----------------------------------------------------------------------------------------
  void pileToBench(
      const PTCG::PLAYER &_owner,
      const PTCG::PILE &_origin,
      std::vector<size_t> _pileIndex,
      std::vector<size_t> _benchIndex
      );
  //----------------------------------------------------------------------------------------
  /// @brief function that moves cards from one pile to another
  /// @param [in] _cardIndices are the positions of the cards to move from the _origin pile
  /// @param [in] _owner is the player who owns the cards
  /// @param [in] _origin is the pile that contains the cards prior to this call
  /// @param [in] _destination is the pile to move the cards to
  //----------------------------------------------------------------------------------------
  void moveCards(
      std::vector<size_t> _cardIndices,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination
      );
```
**[Back To Implementation Section](#details-of-implementations)**
___

#### **Interactive Functions**
- **There are functions that will prompt the player/Ai to choose between cards:**

```cpp
//------------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose card(s) from a set of options
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _origin is the pile that contains the cards
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _match is a function that will be used to filter the cards in the _origin down to the options for _thinker
  /// @param [in] _amount is the amount of cards that the _thinker should pick from the options
  /// @param [in] _known tells us whether the options should be revealed to the player, for example prize cards should not
  /// @param [in] _range allows the caller to limit the amount of cards that are possible options. e.g. we could say pick
  /// from the top 7 cards of the deck by setting range to 7.
  /// @return the indices of the picked cards, in _origin
  //----------------------------------------------------------------------------------------
  std::vector<size_t> playerCardChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      std::function<bool(Card*const)> _match,
      const unsigned _amount,
      const bool _known = true,
      const size_t _range = 0
      );
  //----------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose slot(s) from a set of options
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _amount is the amount of slots that the _thinker should pick from the options
  /// @param [in] _match is a function that will be used to filter the slots down to the options for _thinker
  /// @param [in] _skipActive tells us whether to consider the active pokemon/slot as an option
  /// @return the indices of the picked slots
  //----------------------------------------------------------------------------------------
  std::vector<size_t> playerSlotChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const unsigned _amount,
      std::function<bool(BoardSlot*const)> _match,
      const bool _skipActive = false
      );

  //----------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose energ(y/ies) from a slot
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _destination is where the energies will be moved to
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _slotIndex is the slot which the energies are attached to
  /// @param [in] _match is a function that will be used to filter the cards in the _origin down to the options for _thinker
  /// @param [in] _amount is the amount of cards that the _thinker should pick from the options
  /// @return the indices of the picked energy cards
  //----------------------------------------------------------------------------------------
  std::vector<size_t> playerEnergyChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const size_t _slotIndex,
      std::function<bool(Card*const)> _match,
      const unsigned _amount
      );
  //-------------------------------------------------------------------------------------
  /// @brief function that asks the player to choose condition(s) from their active pokemon
  /// @param [in] _thinker is the player who must make the choice
  /// @param [in] _owner is the player who owns the options
  /// @param [in] _action is what will be done with the resulting choice
  /// @param [in] _options are the conditions to choose from if they are on the active
  /// @param [in] _amount is the amount of conditions that the _thinker should pick from the options
  /// @return the indices of the picked conditons
  //-------------------------------------------------------------------------------------
  std::vector<size_t> playerConditionChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<PTCG::CONDITION> _options,
      const unsigned _amount
      );
```
**Example:**
```python
#123.py
import poke as p 

def filter(card):
    return card.cardType() == p.CARD.POKEMON and not card.stage()

def canPlay(h):
    # checks if deck is not empty && checks if the type of pokemon is in the deck
    # if both return TRUE
    return h.numCards(p.PLAYER.SELF,p.PILE.DECK)

def nestBall(h):
    cards = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF, 
        p.PILE.DECK, 
        p.ACTION.DRAW,
        filter,
        1)
    freeSlots = h.freeSlots(p.PLAYER.SELF)
    amount = min(len(freeSlots), len(cards))
    h.pileToBench(p.PLAYER.SELF, p.PILE.DECK, cards[:amount], freeSlots[:amount])
    h.shuffleDeck(p.PLAYER.SELF)
```
**[Back To Implementation Section](#details-of-implementations)**
___
#### **Delayed or Persistent Effects**

- **There are also cases for delayed/persistent effects:** 
```cpp
  //----------------------------------------------------------------------------------------
  /// @brief will add an effect to the effect queue so that it will be executed on a future turn.
  /// @param [in] _affected is the player who's turn the effect will be executed on
  /// @param [in] _wait is the ammount of _affected's turns to wait before execution
  /// @param [in] _effect is the effect to be executed
  //----------------------------------------------------------------------------------------
  void addEffect(const PTCG::PLAYER _affected, const unsigned _wait, const Ability &_effect);
```
> ***Ability* is an object you pass into the function, here's what you need to construct an *Abilty:***

```cpp

  //---------------------------------------------------------------------------------------
  /// @brief specific assignment ctor for constructing an Ability
  /// @param [in] _ability effect function to be executed/used
  /// @param [in] _name name of the attack, effect or ability
  /// @param [in] _trigger when the effect is triggered
  /// @param [in] _duration how does the effect wear off/number of use
  /// @param [in] _canUse function to check if effect can be used
  //---------------------------------------------------------------------------------------
  Ability(
      const EffectFunc _ability,
      const std::string &_name,
      const PTCG::TRIGGER _trigger,
      const PTCG::DURATION _duration,
      const std::function<bool(Game*const)> _canUse = [](auto){return true;}
  );
```
**Example:**
```python
#37.py
import poke as p

def effect(h):
    print "cant retreat next turn"
    h.setCanRetreat(p.PLAYER.SELF,False)

def roost(h):
    h.healDamage(30)
    # next turn no retreat
    ability = p.Ability(effect, '', p.TRIGGER.START, p.DURATION.SINGLE)
    h.addEffect(p.PLAYER.SELF, 1, ability)

```
**[Back To Implementation Section](#details-of-implementations)**

#### **ASCII Printer**

- **[General Usage](#general-usage)**
- **[Printer Structure](#printer-structure)**
- **[Type Name Conversion](#type-name-conversion)**

### **General Usage**

To draw the board, simply call **drawBoard();** and it will print out both players.

Re-printing is done automatically whenever changes in the board occur, so you don't have to worry about that.

The printer draws both boards at once, and it differentiates between how to draw each of them using a boolean switch that is passed to function.

**Example**
```c++
//this will mark the board as enemy and draw it in reverse order
drawSide(m_subject->getBoard(PTCG::PLAYER::ENEMY), false);

//while this will use standard order marking it as self
drawSide(m_subject->getBoard(PTCG::PLAYER::SELF), true);
```

To draw a pokemon card, for example, your template string should include tags such as **$TYPE** or **$NAME**. There is no list of tags because those are not strictly defined. You can freely use your own tags, but if you wish to use our tags, take a look at a card you want to draw in **asciicards.h**. As long as you use the same tag in the card template and in the replacement function the information will be replaced correctly.

For further information see **[Printer Structure](#printer-structure)**

The function that deals with information replacement is called **str_replace_sent** and you **must** provide valid tag and new information as a string. There is an option to pad the text to the front of the input field, or back. This is controlled by a boolean parameter at the end. By default it is set to true (front) and you **do** **not** have to **specify** it **unless** **necessary**.

**Example**
```c++
str_replace_sent(_str, "$HP", std::to_string(_card->hp()));

//this line will pad to back                       vvv
str_replace_sent(_str, "$NAME", _card->getName(), false);

str_replace_sent(_str, "$T", std::string{charify(_card->type())});
```

For function descriptions see **documentation**.

**[Back To ASCII Printer Section](#ascii-printer)**

### **Printer Structure**

The basic idea of the printer is that it takes a manually predefined default template string for an object, scans it for tags and substitutes those tags with appropriate information.

Used tags include: **$T**; **$TXT**; **$NAME**; **$HP**; **$E**; **$EVO**; **$A**; **$W**; **$R** and others.

You can use a custom tag, just make sure to include it in the card template. 

All predefined card string templates are stored in **asciicards.h** and there are 4 types of card templates:

- Big Card (used for card inspection, more information, larger size (64x28))
- Standard Slot aka Sentinel Slot (used as a standard draw type for bench, moderate amount of information, size: 25x11)
- Card aka Sentinel Card (used as a standard draw type for hand, minimal information, size: 17x10)
- Prize Card (no information, size: 5x3)

**Example** **(standard slot)**
```
*[$ID$/149][$L$/$HP$hp]*
| $NAME$$$$$$$$$$ [$T$]|
| Energy: $E$x         |
| Tool: $TOOL$$$$$$$   |
|----------------------|
| $A0$$$$$ $D0$ ($AR0$)|
| $A1$$$$$ $D1$ ($AR1$)|
|----------------------|
| [$W$]  [$R$$]  [$C$] |
| [$STATUS$$$$$$$$$$$] |
*----------------------*
```

You may notice that sometimes the input fields are much larger than the actual input information. This is not the problem because everything marked with **$** will be replaced with empty spaces by **str_replace** after the information has been filled in.

Based on the type of ownership, the boards are drawn differently. Board sections include:

- Active (slot with active pokemon)
- Bench (other slots)
- Hand (all cards in hand, **IGNORED** **if** **owner** **is** **ENEMY**)
- Prize (all prize cards)

**Example**
```
order for SELF:
 I     ACTIVE
 II    BENCH
 III   HAND
 IV    PRIZE

order for ENEMY:
 I     PRIZE
 II    BENCH
 III   ACTIVE
```

Printer is split into specialized methods to draw specific card types. All inspection functions have a word "big" in their names and every specific type function is named with that type.

So for inspection we have: **bigSlotStr** and **bigCardStr**. Where bigCardStr calls one of the following: **bigPCStr**, **bigECStr** or **bigTCStr**, based on the type of card.

And for standard we have: **slotStr** and **cardStr**. Where cardStr calls one of the following: **pokemonCardStr**, **energyCardStr** or **trainerCardStr**, based on the type of card.

**[Back To ASCII Printer Section](#ascii-printer)**

### **Type Name Conversion**

Whenever you need to put a pokemon type into your card, there are 2 ways of doing that:

- Using a single character (when there is little space)
- Using the whole type name

For example, we have a water pokemon with resistance to fire:

To get a character use **charify**

**Example**
```c++
//this will give 'W'
char pType = charify(pokemonCard->type());
//this will give 'F'
char pRes = charify(pokemonCard->resistance());
```

To get a full string use **stringifyChar**

**Example**
```c++
//this will give "WATER"
std::string strPType = stringifyChar(charify(pokemonCard->type());
//this will give "FIRE"
std::string strPRes = stringifyChar(charify(pokemonCard->resistance());
```

**charify** can be used for **Pokemon** **Type** and **Condition**

**stringify** can be used for **Card** **Type**

**stringifyChar** can be used for **Pokemon** **Type** and **Condition**


**[Back To Top](#poketcg-user-guides)**
___
#### **Battle Damage Handling**
**This class is internal to our core so cards cannot access these functionalities directly, Please go to the [Details of Implementations and call functions from the Game core.](#details-of-implementations)**
- Handles Weakness and Resistance calculation during damage calculation.
- Handles Bonus Damage/Damage Reduction before/after Weakness/Resistance calculation.
- Handles Global Status Condition damage and card effect damage (adding damage counters).
___

**Functions called by Game**

```cpp
 //--------------------------------------------------------------------------------------
  /// @brief removing damage taken by a healing a pokemon
  /// @param [in] _slot pokemon on a bench slot, to be healed
  /// @param [in] _value healing amount
  /// @return whether the healing failed
  //-------------------------------------------------------------------------------------
  bool heal(BoardSlot* _slot, const int &_value);
  //-------------------------------------------------------------------------------------
  /// @brief dealing damage to a pokemon, factor in weakness, bonus damages for active, factoring only base for benched
  /// @param [in] _attacker bench on the attacking pokemon's side
  /// @param [in] _defender bench on the defending pokemon's side
  /// @param [in] _defenderIndex index of the bench for the defending pokemon
  /// @param [in] _damage base damage of the attack
  /// @param [in] _applyWeak whether the damage needs to apply weakness and resistance
  //-------------------------------------------------------------------------------------
  void generalDamage(
      Bench *_attacker,
      Bench *_defender,
      const size_t &_defenderIndex,
      const int &_damage,
      const bool &_applyWeak = true
      );
  //-------------------------------------------------------------------------------------
  /// @brief dealing damage, factor only base damage, simulates "Put x Damage Counters onto xxxx Pokemon from special conditions, attacks effects."
  /// @param [in] _defender the slot for the defending pokemon
  /// @param [in] _damage base damage of the attack/effect
  //-------------------------------------------------------------------------------------
  void rawDamage(BoardSlot* _defender, const int &_damage);
  //-------------------------------------------------------------------------------------
  /// @brief increases poison damage
  /// @param [in] _damage how much to increase the Poison damage
  //-------------------------------------------------------------------------------------
  void increasePoison(const int _damage);
  //-------------------------------------------------------------------------------------
  /// @brief increases poison damage
  /// @param [in] _damage how much to increase the Burn damage
  //-------------------------------------------------------------------------------------
  void increaseBurn(const int _damage);
  //-------------------------------------------------------------------------------------
  /// @brief increases poison damage
  /// @param [in] _damage how much to increase the Confusion damage
  //-------------------------------------------------------------------------------------
  void increaseConfuse(const int _damage);
  //-------------------------------------------------------------------------------------
  /// @brief accessing game poison damage
  /// @return current poison damage per turn
  //-------------------------------------------------------------------------------------
  int getPoison() const;
  //-------------------------------------------------------------------------------------
  /// @brief accessing game burn damage
  /// @return current burn damage per turn
  //-------------------------------------------------------------------------------------
  int getBurn() const;
  //-------------------------------------------------------------------------------------
  /// @brief accessing game confusion damage
  /// @return current confusion damage per tail on coin flip when attacking
  //-------------------------------------------------------------------------------------
  int getConfuse() const;
```
___
**Internal Methods and Attributes:**
```cpp
 //--------------------------------------------------------------------------------------
  /// @brief applying and determining weakness or resisitance within damage calculation
  /// @param [in] _defender slot of the defending pokemon
  /// @param [in] _attacker slot of the attacking pokemon
  /// @return damage reduction when resistant, damage multiplies when weak against attack
  //-------------------------------------------------------------------------------------
  int applyWeakRes(BoardSlot* _defender, BoardSlot* _attacker);
  //-------------------------------------------------------------------------------------
  /// @brief adding the net bonus damage for damage calculation
  /// @param [in] _defender slot of the defending pokemon
  /// @param [in] _attacker slot of the attacking pokemon
  /// @param [in] _order whether you are calculating net bonus before/after weakness/resistance application
  /// @return net bonus damage before/after weakness/resistance calculation
  //-------------------------------------------------------------------------------------
  int applyBonusDamage(Status *_defender, Status *_attacker, const PTCG::ORDER &_order);
  //-------------------------------------------------------------------------------------
  /// @brief weakness multiplier
  //-------------------------------------------------------------------------------------
  int m_weaknessMult = 2;
  //-------------------------------------------------------------------------------------
  /// @brief resistance damage reduction
  //-------------------------------------------------------------------------------------
  int m_resistance = - 20;
  //-------------------------------------------------------------------------------------
  /// @brief base poison damage
  //-------------------------------------------------------------------------------------
  int m_poisonDamage = 10;
  //-------------------------------------------------------------------------------------
  /// @brief base burn damage
  //-------------------------------------------------------------------------------------
  int m_burnDamage = 20;
  //-------------------------------------------------------------------------------------
  /// @brief base confusion damage
  //-------------------------------------------------------------------------------------
  int m_confuseDamage = 30;
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

Clone usually is the same for Ai, make sure this is written like the one below if you wish to use turn simulation.

```cpp
Player* SomeAi::clone() const
{
  return new SomeAi(*this);
}
```
___

You can use these parameters passed from the Game Core to determine the selection of cards and slots in different situations.

It's usually preferred to define another logs function outside of the overriden methods to keep this function clean.

The choice functions require you to return a ```std::vector<size_t>``` which contains a list of indices. These indices are your AI's pick from the options provided.

For example a dumb AI might just choose the first options everytime:

```cpp
std::vector<size_t> SomeAi::chooseCards(
    const PTCG::PLAYER _player, 
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(_options.size(), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}
```

The turn function is what will be called when it is your AI's turn to play. You should do all of your card playing, retreating and evolving here.

The function returns a pair of a ```bool``` and an ```unsigned```.

The first is your decision to attack, true will tell the game that you do want to attack, and false will tell it that you don't. 

If you decide to attack, the second value will be examined, this is the index of the attack you wish to use (zero based).

Bellow is another example of a dumb AI, however this one gives you an example of how you can use the functions within player to achieve basic actions in your turn.

```cpp
std::pair<bool, unsigned> SomeAi::turn()
{
  // Have a look at your hand
  auto hand = viewHand();
  // If it's not empty and you can play the first card
  if (!hand.empty() && canPlay(0))
    // Play the first card in your hand
    playCard(0);

  // View my bench and keep a reference to the active
  auto bench = viewBench();
  auto& activeSlot = bench[0];

  // If my active has less than half it's hp left we'll try to retreat it
  if (activeSlot.getRemainingHP() < (activeSlot.active()->hp() / 2))
    retreat();

  // See how many attacks I have
  unsigned numAttacks = activeSlot.active()->attackNum();
  // Variables to hold attack decision
  unsigned attackToUse = 0;
  bool doAttack = false;
  // Loop over all attacks and find one that can be used
  for (unsigned i = 0; i < numAttacks; ++i)
  {
    if (canAttack(i))
    {
      doAttack = true;
      attackToUse = i;
    }
  }
  // Return the decision
  return std::pair<bool, unsigned> {doAttack, attackToUse};
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

// You can then query the current game state by calling the view functions on the dummy game
auto checkBench = dummySelf.viewBench();
```

If you're a fan of lambda expressions you can use them instead of writing free functions:
```cpp
// These are equivalent to the functions provided above
dummySelf.setTurn(
    [](Player*_dummyPlayer)
    {
      auto hand = _dummyPlayer->viewHand();
      if (hand.size() && _dummyPlayer->canPlay(0))
        _dummyPlayer->playCard(0);
      return std::pair<bool, unsigned> {false, 0};
    }
);
dummyEnemy.setTurn([](Player*){ return std::pair<bool, unsigned> {false, 0}; });
```
Lambdas with closure objects are also supported.
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
