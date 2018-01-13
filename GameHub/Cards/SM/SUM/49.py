import poke as p 

def filter(card):
    return card is not None

def searchingLight(h):
    cards = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF, 
        p.PILE.PRIZE, 
        p.ACTION.VIEW, 
        filter, 
        1,
        False)
    h.revealCards(p.PLAYER.SELF, p.PLAYER.SELF, p.PILE.PRIZE, cards)

def electroBall(h):
    h.dealDamage(30)
