import poke as p

def filter(card):
    return True;

def canPlay(h):
    # checks if it is your first turn; if first turn and less than 8 cards in your hand return true
    drawAmount = 6
    if h.turnCount() < 2:
        drawAmount += 2
    # Need -1 for handsize due to you discarding Lillie itself when playing it
    return (h.numCards(p.PLAYER.SELF, p.PILE.HAND) - 1  < drawAmount) and (h.numCards(p.PLAYER.SELF, p.PILE.DECK) > 0)

def lillie(h):
    # if first turn 
    amount = 6
    # Need -1 for handsize due to you discarding Lillie itself when playing it
    handSize = h.numCards(p.PLAYER.SELF, p.PILE.HAND) - 1
    if h.turnCount() < 2:
        amount += 2
    for i in range(max(0, amount - handSize)):
        h.drawCard(p.PLAYER.SELF)
