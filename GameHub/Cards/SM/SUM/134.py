import poke as p 

def filter(card):
    return card.cardType() == p.CARD.POKEMON and card.stage()

def canPlay(h):
    return len(h.viewDeck(p.PLAYER.SELF)) > 0 

def timerBall(h):
    # flip coin twice
    headsAmount = h.flipCoin(2)
    if headsAmount:
        cards = h.playerCardChoice( 
            p.PLAYER.SELF,  
            p.PLAYER.SELF,  
            p.PILE.DECK,  
            p.ACTION.DRAW, 
            filter,  
            headsAmount)
        h.moveCards(cards, p.PLAYER.SELF, p.PILE.DECK, p.PILE.HAND)
        h.shuffleDeck(p.PLAYER.SELF)
