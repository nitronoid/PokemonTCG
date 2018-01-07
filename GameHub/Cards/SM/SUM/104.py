import poke as p

def filter(card):
    card.cardType() == p.CARD.ITEM

def treasureHunt(h):
    # ABILITY: when you play this monster from your hand to evolve 1 of your
    # monster during your turn, you may put an item card from your discard pile into your hand

    #if played to evolve a pokemon then: 
    cards = h.playerCardChoice(
        p.PLAYER.SELF, 
        p.PLAYER.SELF,
        p.PILE.DISCARD, 
        p.ACTION.DRAW,
        filter,
        1)
    h.moveCards(cards, p.PLAYER.SELF, p.PILE.DISCARD, p.PILE.HAND)

def bite(h):
    h.dealDamage(50)
