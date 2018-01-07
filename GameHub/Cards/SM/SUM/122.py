import poke as p

def filter(card):
    return True;

def canPlay(h):
    # checks if it is your first turn; if first turn and less than 8 cards in your hand return true
    drawAmount = 6
    if h.turnCount() < 2:
        drawAmount += 2
    return len(h.viewDeck(p.PLAYER.SELF)) > (drawAmount - len(h.viewHand(p.PLAYER.SELF)))   

def lillie(h):
    # if first turn 
    amount = 6
    handSize = len(h.viewHand(p.PLAYER.SELF))
    if h.turnCount() < 2:
        amount += 2
    for i in range(max(0, amount - handSize)):
        h.drawCard(p.PLAYER.SELF)

