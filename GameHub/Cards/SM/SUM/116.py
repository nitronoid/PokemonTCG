import poke as p 

def filter(card):
    return card.cardType() == p.CARD.ENERGY

def canPlay(h): 
#First check if there is more than two cards in discard pile, Second if there is more than two energy cards in a discard pile return true
#checks the length of the discard pile if more than two return TRUE &&
#checks if type of card > 2 in it too 
    cards = h.viewDiscard(p.PLAYER.SELF)
    amountOfTypeCards = 0
    for card in cards:
        if(card.type() == p.CARD.ENERGY):
            amountOfTypeCards += 1
    return len(h.viewDiscard(p.PLAYER.SELF)) > 1 and amountOfTypeCards > 1
            
def energyRetrieval(h):
    # std::vector<int> Game::playerChoice(PLAYER thinker, PLAYER owner, PILE origin, CARD cardType, ACTION action, int amount = 1, int range = origin.size);
    # thinker - Player who makes the choice (SELF/ENEMY)
    # owner - The player who owns the cards to choose from
    # origin - Search location (DECK/HAND/DISCARD/BENCH/PRIZE)
    # cardType - The cards to select (POKEMON/SUPPORTER/ENERGY.....ALL)
    # action - what to do with the selection
    # amount - Number of cards play should draw AT MOST! (>0)
    # range - Number of cards the player picks from (>1), defaults to the whole thing
    # return - The list of chosen cards

    # void Game::moveCards(std::vector<int> cardIndices, PLAYER owner, PILE origin, PILE destination, bool reveal);
    # cardIndices - Indices of card in Origin
    # owner - The player who owns the cards to move
    # origin - card's original location (DECK/HAND/DISCARD/BENCH/PRIZE)
    # destination - where the cards goes (DECK/HAND/DISCARD/BENCH/PRIZE)
    # reveal - whether the enemy sees the card (True/False)

    cards = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF, 
        p.PILE.DISCARD, 
        p.ACTION.DRAW, 
        filter,
        2)
    h.moveCards(cards, p.PLAYER.SELF, p.PILE.DISCARD, p.PILE.HAND)
