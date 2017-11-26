import poke

def callForFamily(h):
    cards = h.playerChoice(SELF, DECK, BASIC_POKEMOM, ?, 2)
    for card in cards:
        h.moveCard(card, DECK, BENCH, False)
    h.shuffleDeck()

def surf(h):
    h.dealDamage(60)