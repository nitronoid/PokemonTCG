import poke as p


def filter(card):
    return card.cardType() == p.CARD.POKEMON and not card.stage()
            

def callForFamily(h):
    cards = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF, 
        p.PILE.DECK,
        p.ACTION.DRAW,
        filter,
        2)
    
    freeSlots = h.freeSlots(p.PLAYER.SELF)
    amount = min(len(freeSlots), len(cards))
    h.pileToBench(p.PLAYER.SELF, p.PILE.DECK, cards[:amount], freeSlots[:amount])
    h.shuffleDeck(p.PLAYER.SELF)

def surf(h):
    h.dealDamage(60)