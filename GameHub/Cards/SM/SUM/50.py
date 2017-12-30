import poke

def confuseRay(h):
    h.applyCondition(CONFUSED, ENEMY)

def aquaSpark(h):
    dmg = 60
    # if water energy is attached to pokemon
    if(h.viewBoard(SELF)[0].energy() == WATER):
        dmg += 60
    h.dealDamage(dmg)