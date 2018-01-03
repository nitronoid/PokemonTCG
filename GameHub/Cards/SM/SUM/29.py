import poke as p 

def filter(card):
    return card.cardType() == p.CARD.ENERGY and card.type() == p.TYPE.WATER

def scratch(h):
    h.dealDamage(20)

def doubleJet(h):
    cards = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF , 
        p.PILE.HAND, 
        p.ACTION.DISCARD,
        filter,
        2)
    h.moveCards(cards, p.PLAYER.SELF, p.PILE.HAND, p.PILE.DISCARD)
    dmg = len(cards)*60
    h.dealDamage(dmg)