import poke as p

def confuseRay(h):
    h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.CONFUSED)

def aquaSpark(h):
    dmg = 60
    # if water energy is attached to pokemon
    if(h.viewBoard(p.PLAYER.SELF)[0].energy() == WATER):
        dmg += 60
    h.dealDamage(dmg)