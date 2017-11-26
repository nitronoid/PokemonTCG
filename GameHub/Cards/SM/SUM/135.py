import poke

def ultraBall(h):
    # std::vector<int> Game::playerChoice(PLAYER player, PILE origin, CARD cardType, ACTION action, int amount = 1, int range = origin.size);
    # player - Player who makes the choice (SELF/ENEMY)
    # origin - Search location (DECK/HAND/DISCARD/BENCH/PRIZE)
    # cardType - The cards to select (POKEMON/SUPPORTER/ENERGY.....ALL)
    # action - what to do with the selection
    # amount - Number of cards play should draw AT MOST! (>0)
    # range - Number of cards the player picks from (>1), defaults to the whole thing
    # return - The list of chosen cards

    # void Game::moveCards(std::vector<int> cardIndices, PILE origin, PILE destination, bool reveal);
    # cardIndices - Indices of card in Origin
    # origin - card's original location (DECK/HAND/DISCARD/BENCH/PRIZE)
    # destination - where the cards goes (DECK/HAND/DISCARD/BENCH/PRIZE)
    # reveal - whether the enemy sees the card (True/False)

    discardChoice = h.playerChoice(SELF, HAND, ANY, DISCARD, 2)

    if len(discardChoice) == 2 :
        h.moveCards(discardChoice, HAND, DISCARD, False)
        pokeCard = h.playerChoice(SELF, DECK, POKEMON, DRAW)
        h.moveCards(pokeCard, DECK, HAND, True)
        h.shuffleDeck()


    

            