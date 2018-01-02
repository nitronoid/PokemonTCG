import poke as p

def filter(card):
    return True;

def canPlay(h):
    # deck never empty ? 
    # checks if it is your first turn; if first turn and less than 8 cards in your hand return true
    result = False
    if(len(h.viewDeck(p.PLAYER.SELF) > 0)):
        if(h.turnCount() < 2 and len(h.viewHand(p.PLAYER.SELF))<8):
            result = True
    return result 

def lillie(h):
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

    # if first turn 
    amount = 6
    handSize = len(h.viewHand(p.PLAYER.SELF)) < 8
    if h.turnCount() < 2:
        amount += 2
    for i in range(max(0, amount - handSize)):
        h.drawCard(p.PLAYER.SELF)

