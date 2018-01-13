import poke as p 

'''
Some card effects such as: "Put 2 energy cards into your deck.", have constraints on when they,
can be played. You must implement a canPlay function to make sure these constraints are satisfied.
'''
def canPlay(h):
    # if deck has at least two cards 
    return h.numCards(p.PLAYER.SELF, p.PILE.DECK) >= 2

def professorKukui(h):
    # draw two cards
    for i in range(2):
        h.drawCard(p.PLAYER.SELF)
    # your Pokemon's attacks do 20 more damage to your opponent's,
    # active Pokemon (before applying Weakness and Resistance).	
    h.addBonusDamage(20, p.ORDER.BEFORE, p.PLAYER.SELF)
    