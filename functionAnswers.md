Function answers
--
dealDamage
-
void dealDamage(const unsigned _damage, const unsigned _id = 0)
This function is in the Game class and can be called in python,
e.g. h.dealDamage(20) will deal 20 damage to the opponents active pokemon.
The _id parameter can be used to attack the opponents benched pokemon,
e.g. h.dealDamage(20, 2) will attack the opponents second benched pokemon.

healDamage
-
Eric is doing this, won't be difficult
Probably similar to deal damage,
e.g. void healDamage(const unsigned _damage, const unsigned _id = 0)
Where you're now applying it to your own pokemon.

applyCondition
-
You can use applyCondition for all status effects, such as confuse, burn, poision etc.
void applyCondition(const PTCG::PLAYER &_target, const PTCG::CONDITION &_condition)
Where the _target represents you (SELF) or your opponent (ENEMY). and _condition is what you want to apply, (CONFUSE, BURN, POISION, etc.).
This is again in the Game class and can be called from python 
e.g. h.applyCondition(ENEMY, POISON)
This will poison your opponents active pokemon.

flipCoin
-
This exists in game as 
unsigned flipCoin(const unsigned _num)
where the _num is the ammount of coins you want to flip. The function returns the number of heads.

shuffleDeck
-
We have the code for this, it's just not in the Game class yet, will probably be
void shuffleDeck(const PTCG::PLAYER _owner)
where _owner is the player whose deck you want to shuffle. In python this would be
e.g. h.shuffleDeck(SELF)
To shuffle your own deck.

moveCards
-
bool moveCards(const std::vector<unsigned> _cardIndices,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination,
      const bool _reveal= false,
      const std::vector<unsigned> _destIndex = {}
      )
This can be used to discard cards by moving from HAND to DISCARD,
e.g. h.moveCards([0,1], SELF, HAND, DISCARD)
Will move the first and second cards in your hand to your discard pile.