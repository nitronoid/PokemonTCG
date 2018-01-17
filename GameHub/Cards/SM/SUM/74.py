import poke as p

def match(card):
    return card.cardType() == p.CARD.ENERGY and card.type() == p.TYPE.FIGHTING

def shoreUp(h):
    choice = h.playerCardChoice(
        p.PLAYER.SELF,
        p.PLAYER.SELF,
        p.PILE.DISCARD,
        p.ACTION.PLAY,
        match,
        1)
    if choice:
        h.pileToBench(p.PLAYER.SELF, p.PILE.DISCARD, choice, [0]) #sort this bit out

def sandTomb(h):
    h.dealDamage(30)
