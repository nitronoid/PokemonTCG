import poke as p

def confuseRay(h):
    h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.CONFUSED)

def aquaSpark(h):
    dmg = 60
    # if water energy is attached to pokemon
    if(p.TYPE.WATER in h.viewBench(p.PLAYERS.SELF)[0].energySet()):
        dmg += 60
    h.dealDamage(dmg)