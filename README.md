# PokemonTCG, shared Repo

This is where we edit and share our files to each other.\
There are four respositories:\

1. GameHub: Jack, Renat, Eric, and Ming. 
2. BrightTide: Stacy and Moira
3. RoaringHeat: Lucien and Tom
4. ForestShadow: Philip and Jamie 

Wherever your name is you will work in that respository.\
So your partner(s) can see what you do, and at the same time you can edit it.\
There is an empty file in all of the directories just delete it.

It would be useful to communicate what you have done by logging. \
You should edit the README, there will be a section for it. Under section **LOG** you should put the date of the day you done work, your name, the work you have done and an additional message to who you are communication. 

## LOG

To add in the table you put the | symbol under the last log and the seperate each column with it.


| Date | Name | What have you done? | To whom? : Additional message | 
| ---- | ---- | ------------------- | ------------------ |
| 14/11/17 | Bright Tide Team | Deciding which functions we need | To GameHub: Look in our docx file for the functions |
| 16/11/17 | Game Hub Team | Majority of UML structure finished | To other teams: please, give us a list of functions for the game hub |
| 20/11/2017 | Bright Tide Team | added cards 7 cards | Stacy add the rest of the cards (total 8) |
| 20/11/17 | Game Hub Team |  Added the start of core game code with a simple example of loading a card from json and python, needs work on error protection, and parsing the rest of the properties/card types |   Continue to write the cards and report any required functions. |
| 21/11/17 | Game Hub Team |  Added Trainer Card Example: Card 119 | Write Trainer Cards plz |
| 21/11/17 | Game Hub Team |  Advanced the UML, split the componets of player into seperate objects for card groups. Also started to define the Game API. |  |
| 21/11/17 | Game Hub Team |  Simplified card class heirarchy by condensing all trainer cards into one class with a type enum. Also added some useful functions. Started to provide a basic implementation for testing. Pokemon cards can now be fully loaded from json and python with the exception of abilities. | TODO: Add the card pool class to UML, finish the Game API. |
| 22/11/17 | Game Hub Team |  Fixed card 119 implementation. | Other teams: look at this card (119) and use it to help write your own. |
| 22/11/17 | Game Hub Team |  Pokemon cards and trainer cards can now be fully loaded through the card factory including abilities. Currently no error checking or energy cards. UML updated to reflect change in design regarding the player class. It is now abstract with two example descendants for AI and human player. Card 119 json was patched to reflect how abilities should be written. | Other teams: Look at the updated UML to start thinking about how your AI will integrate into the system. |
| 23/11/17 | Game Hub Team |  Started to implement the card pile classes and board slots. |  |
| 24/11/17 | Game Hub Team |  Fleshing out player API and corresponding game functions required by it. | Game Hub Team: Update UML to reflect recent changes. Need to implement a non-copying swap for Board slots to be used by the retreat function, a specialisation in the std namespace should also be present. |
| 26/11/17 | Bright Tide Team | added the item and supporter cards, edited python code | | 
| 29/11/17 | Game Hub Team | Wrote the headers for core game to match the new design, outlined by UML. | GameHub, TODO: Implement constructors for card pile classes and write implementations for all functions. Other Teams: Modify your python cards to implment a "canPlay" function, mostly for trainer cards, not neccessary for pokemon cards (probably). | 
| 30/11/17 | Game Hub Team | Implemented functions for BoardSlot and Bench, minor changes reflected in uml. |  | 
| 04/12/17 | Game Hub Team | TODO: Make view functions return copies rather than ref's. |  | 
| 08/12/2017 | Bright Tide Team | added canPlay function, added energy cards, edited cards | |
| 18/12/2017 | Game Hub Team | Testing and fixing bugs for game setup. Implementing Text output. | TODO: Implement importDeckList function in Card Factory with a testing deck list for game setup.|
| 18/12/2017 | Bright Tide | modified cards for canPlay function | | 
| 19/12/2017 | Game Hub Team | Added some text output for card movement, need to implement view board in game and player| | 
| 19/12/2017 | Bright Tide | modified cards again, based on template, still need modifying, did final deck list | GameHub: Check the functions queries under 18/19 of December in dockx file (Bright Tide)| 




 
