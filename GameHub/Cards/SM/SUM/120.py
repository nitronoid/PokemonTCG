import poke as p 

def filter(card):
    return True

def canPlay(h):
    return h.numCards(p.PLAYER.SELF, p.PILE.DECK) > 0

def hau(h):
    for i in range(3):
        h.drawCard(p.PLAYER.SELF)
