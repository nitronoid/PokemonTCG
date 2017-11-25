# Function List For Hub Team

 This list reflects the functions needed for the cards to work with the hub~
 Mostly for hub team to see what the card teams are requesting tbh

## Edit History : 
- 24/11/2017 Eric: 
    "File Creation and first observation of cards created created by this date."
- Add new logs here if you can be bothered to... future self/teammate.


## Functions:
___________________________________________________________________________________________________________
``` c++
**void dealDamage() variant:**
```
1. void dealDamage(int _damageVal) - deals damage of value _damageVal.
2. void dealDamageX(int _damageVal, int _mult) - deals _mult x _damageVal damage.
3. void dealDamageBench(TARGET, std::array<int> _index, int _damageVal) - deals damage to seleccted benched pokemon

```
> We could only implement 2. and specify _mult = 1 by default for 1..
> 3. needs to be separate as bench damage doesn't apply weakness/resistance.
___________________________________________________________________________________________________________
``` c++
**int flipCoin(int _coinAmount): **
```
- flips _coinAmount number of coins, returns number of heads.

___________________________________________________________________________________________________________
``` c++
**void applyCondition(CONDITION, TARGET):** 
```
-    CONDITION [...] - Condition to apply to the target, see PokeEnums in GameHub directory
-    TARGET [SELF, ENEMY] - Opponent's active or Your own active.

___________________________________________________________________________________________________________

> I think returning a vector/array back into python might be iffy but we can work around it later
``` c++
**std::vector<std::unique_ptr<Card>> playerChoice(TARGET, LOCATION, CARDTYPE, int _range, int _choice ):**
```
    - TARGET [SELF, ENEMY] - Who is choosing?
    - LOCATION [DECK, HAND, DISCARD.....] - Where to choose from?
    - _range - How many cards to choose from?
-    _choice - Card(s) you can AT MOST choose.

- Returns a list of cards the player chose.

>When searching a Pokemon card, we need more requirements such as: BASIC, HP<90
>May want to seperate the functions when implementing them later.

>Something like this:
>e.g. 

``` c++
searchPokeEvo(EVOSTAGE, int _range=h.myDeck::getSize() ,int _choice)
```
___________________________________________________________________________________________________________

**Searching for quantity functions example:**
``` c++
int searchPokeName(std::string _name,TARGET,LOCATION):
```
> Do this for other json data fields would be useful

___________________________________________________________________________________________________________
``` c++
**void moveCard(std::unique_ptr<Card> _card, ORIGIN, DESTINATION, bool _reveal ):**
```
    - _card - the card you are moving.
    - ORIGIN (LOCATION but I want to make it less confusing) - Where is this card from?   
    - DESTINATION (See line above) - Where to move the card to?
    - _reveal - True for "Yes, show the card to my opponent" and vice versa.

___________________________________________________________________________________________________________
``` c++
**void shuffleDeck():**
```
- Shuffles deck. Technical explanation not needed here.

___________________________________________________________________________________________________________
``` c++
**int discardCard(CARDTYPE, int _amount):**
```
    - CARDTYPE - See PokeEnums for types of cards to discard.
    - _amount - Number of that type of card to discard
    - returns number of cards discarded

> discarding energy cards may need to specify addition enum TYPE, we may need to seperate the two functions into 
> functions for each card type.
> In the case of discarding all cards of one card type, we need access to boardslot container sizes

___________________________________________________________________________________________________________
``` c++
**void futureDamage(TARGET, ORDER, int _amount):**
```
    - TARGET - If ENEMY, current enemy active takes more/less damage until ENEMY's next turn.
        - If SELF, your active takes more/less damage until YOUR next turn.
    
    - ORDER[BEFORECALC, AFTERCALC] - Whether damage is added/reduced, BEFORE/AFTER applying weakness or resistance.  
    
    - _amount - (-) for damage reduction, (+) for bonus damage.

> Reduce/increase _amount of damage taken next turn

___________________________________________________________________________________________________________
``` c++
**void blockDamage():**
```
    > The call makes the current pokemon take 0 damage from any source until its owner's next turn.
    > It's weird to have a situational function just for this, we could think about
    > setting an additional status effect in CONDITION - PROTECT and have damage calc check for this flag
___________________________________________________________________________________________________________
``` c++
**void heal() variant(?):**

void heal(int _amount):
```
    - Rocover HP of _amount of the current Active Pokemon

> May need to have a targeted heal later 

___________________________________________________________________________________________________________
``` c++
**void noRetreat(TARGET):**
```
    - TARGET - prevents TARGET's active pokemon from retreating (the discarding energy way). 

___________________________________________________________________________________________________________
``` c++
**bool cardAttached() variant:**
```
1. energyAttached(TARGET,TYPE) - returns true if ENEMY/SELF has the specified energy attached.
2. toolAttached(TARGET) - turns true if ENEMY/SELF has the specified tool attached.
___________________________________________________________________________________________________________
``` c++
**bool matchPokeType(TARGET, LOCATION, TYPE):**
```
    - We need this for applying resistance/weakness and other attack bonus damage or effects
    - TARGET - Whose card are you checking?
    - LOCATION - Where are you
    - TYPE - Which element type are you matching? 

> returns true if the type of the pokemon in thr speciied place matches TYPE parameter.
> looks similar to cardAttached() variant but this only checj the type and doesn't dig into a slot's containers

___________________________________________________________________________________________________________
``` c++
**void view(LOCATION,TARGET):**
```
    - Allows user to view a card from a specified location of the board.
    - LOCATION - Where to view?
    - TARGET - Whose card(s) are you viewing? ENEMY or SELF?

>Parameter for indexing might be needed to reveal a chosen slot from "e.g. Prize"

>TO TEAMMATES - or we could implicitly call playerChoice() inside view()

___________________________________________________________________________________________________________
``` c++
**onPlayTrigger() variant:**
```
    - There are quite a lot of cases for abilities trigering when cards are played
> Need to work on this after we finish implementing turn sequence
___________________________________________________________________________________________________________


