import poke

def workUp(h):
    h.addBonusDamage(20, poke.ORDER.BEFORE, poke.PLAYER.SELF)
    # during next turn this monster attacks 20+ (before applying weakness and resistance)

def bite(h):
    h.dealDamage(20)