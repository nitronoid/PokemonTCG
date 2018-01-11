import poke as p 

def filter(card):
    return True

def canPlay(h):
    # if deck has more than two cards 
    return len(h.viewDeck(p.PLAYER.SELF)) >= 2

def professorKukui(h):
    for i in range(2):
        h.drawCard(p.PLAYER.SELF)
    # your Pokemon's attacks do 20 more damage to your opponent's 
    # active Pokemon (before applying Weakness and Resistance).	
    h.addBonusDamage(20, p.ORDER.BEFORE, p.PLAYER.SELF)
