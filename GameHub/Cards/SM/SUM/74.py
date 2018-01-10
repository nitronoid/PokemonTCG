import poke

def shoreUp(h):
    discard=h.viewDiscard(p.PLAYER.SELF)
    indices = []
    for i in range(discard):
        if discard[i].cardType()== p.CARD.ENERGY and discard[i].type() == p.TYPE.FIGHTING:
            indices.append(i)
    h.pileToBench(p.PLAYER.SELF, p.PILE.DISCARD,indices[:1],[0]) #sort this bit out

def sandTomb(h):
    h.dealDamage(30)
    




