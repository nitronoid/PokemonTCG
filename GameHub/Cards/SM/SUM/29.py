import poke

def scratch(h):
    h.dealDamage(20)

def doubleJet(h):
    cards = h.playerChoice(SELF,HAND,WATER_ENERGY,?,2)
    dmg = len(cards)*60
    h.dealDamage(dmg)