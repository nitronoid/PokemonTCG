import poke as p

def headlock(h):
    dmg = 30
    if(h.flipCoin(1)):
        dmg += 30
    else:
        h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.PARALYZED)
    h.dealDamage(dmg)


def guardPress(h):
    h.dealDamage(80)
    # next turn less damage (20)
    

