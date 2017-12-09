import poke

def ultraBall(h):
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

    if(canPlay()):
        discardChoice = h.playerChoice(SELF, SELF, HAND, ALL, DISCARD, 2)
        
        if len(discardChoice) == 2 :
            h.moveCards(discardChoice, SELF, HAND, DISCARD, False)
            pokeCard = h.playerChoice(SELF, SELF, DECK, POKEMON, DRAW, 1)
            h.moveCards(pokeCard, SELF, DECK, HAND, True)
            h.shuffleDeck()


    

            