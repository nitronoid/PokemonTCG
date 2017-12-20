import poke

def confuseRay(h):
    h.applyCondition(CONFUSED, ACTIVE, ENEMY)

def aquaSpark(h):
    dmg = 60
    # if water energy is attached to pokemon
    if True:
        dmg += 60
    h.dealDamage(dmg)