import poke as p 

def filter(slot):
    return slot.active() and slot.active().getDamage()

def canPlay(h):
    # checks if there is pokemon on bench && active && needs healing
    for slot in h.viewBench(p.PLAYER.SELF):
        if slot.getDamage():
            return True
    return False

def potion(h):
    # select card 
    cards = h.playerSlotChoice(
        p.PLAYER.SELF,
        p.PLAYER.SELF,
        p.ACTION.HEAL,
        1,
        filter)

    for card in cards:
        h.healDamage(30)
