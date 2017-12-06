import poke

def hau(h):
    #int Game::playerChoice(Player, Location, CardType,int Range = Location.size,int Choice = 1);
    # Player - Player who makes the choice (SELF/ENEMY)
    # Location - Search location (DECK/HAND/DISCARD/BENCH/PRIZE)
    # Range - Number of cards the player picks from (>1)
    # Choice - Number of cards play should draw AT MOST! (>0)
    # return - The list of chosen cards

    cards = h.playerChoice(SELF, DECK, ANY, ?, 3)

    #void Game::moveCard(int card, Origin, Destination, bool reveal);
    # card - Index of card in Origin
    # Origin - card's original location (DECK/HAND/DISCARD/BENCH/PRIZE)
    # Destination - where the cards goes (DECK/HAND/DISCARD/BENCH/PRIZE)
    # reveal - whether the enemy sees the card (True/False)

    for card in cards:
        h.moveCard(card, DECK, HAND, False)