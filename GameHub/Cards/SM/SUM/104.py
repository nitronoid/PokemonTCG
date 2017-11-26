import poke

def treasureHunt(h):
    # ABILITY: when you play this monster from your hand to evolve 1 of your
    # monster during your turn, you may put an item card from your discard pile into your hand

    #if played to evolve a pokemon then: 
    cards = h.playerChoise(SELF, DISCARD, ITEM,?,1)
    for card in cards:
        h.moveCard(card, DISCARD, HAND, False)

def bite(h):
    h.dealDamage(50)