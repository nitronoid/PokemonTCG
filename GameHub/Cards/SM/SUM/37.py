import poke as p

def effect(h):
    print "cant retreat next turn"

def canUse(h):
    return True

def roost(h):
    h.healDamage(30)
    # next turn no retreat
    ability = p.Ability(effect, '', p.TRIGGER.START, p.DURATION.SINGLE, canUse)
    h.addEffect(p.PLAYER.SELF, 1, ability)
