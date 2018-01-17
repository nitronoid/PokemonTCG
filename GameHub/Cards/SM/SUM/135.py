import poke as p 

def pokeFilter(card):
    return card.cardType() == p.CARD.POKEMON

def discardFilter(card):
    return True
# checks if the amount of cards in your hand is bigger than 2 and deck is not empty
# return true if yes else return false 
def canPlay(h):
    return h.numCards(p.PLAYER.SELF,p.PILE.HAND) > 2 and h.numCards(p.PLAYER.SELF,p.PILE,DECK)

def ultraBall(h):
    discardChoice = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF, 
        p.PILE.HAND, 
        p.ACTION.DISCARD,
        discardFilter,
        2)
    if len(discardChoice) == 2:
        h.moveCards(discardChoice, p.PLAYER.SELF, p.PILE.HAND, p.PILE.DISCARD)
        pokeCard = h.playerCardChoice(
            p.PLAYER.SELF, 
            p.PLAYER.SELF, 
            p.PILE.DECK,
            p.ACTION.DRAW,
            pokeFilter,
            1)
        h.moveCards(pokeCard, p.PLAYER.SELF, p.PILE.DECK, p.PILE.HAND)
        handSize = h.numCards(p.PLAYER.SELF,P.PILE.HAND)
        # So this generates a list of indices, from where the cards have just been moved
        # handSize - len(pokeCard) is the length before the move
        locations = range(handSize - len(pokeCard), handSize)
        # Flag is hand because that's where the cards are now
        h.revealCards(p.PLAYER.SELF, p.PLAYER.SELF, p.PILE.HAND, locations)
        h.shuffleDeck(p.PLAYER.SELF)


    

            