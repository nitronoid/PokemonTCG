import poke as p 

def effect(h):
    # this is executed on this players next turn
    h.addBonusDamage(20, p.ORDER.BEFORE, p.PLAYER.SELF)

def canUse(h):
    return True

def workUp(h):
    ability = p.Ability(effect,'', p.TRIGGER.ATTACK, p.DURATION.SINGLE, canUse)
    h.addEffect(p.PLAYER.SELF, 1, ability)
    # during next turn this monster attacks 20+ (before applying weakness and resistance)

def bite(h):
    h.dealDamage(20)