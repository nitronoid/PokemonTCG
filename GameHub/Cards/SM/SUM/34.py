import poke

def headlock(h):
    dmg = 30
    if(h.flipCoin(1)):
        dmg += 30
        h.dealDamage(dmg)
    else:
        h.applyCondition(PARALYZED, ENEMY)


def guardPress(h):
    h.dealDamage(80)
    # next turn less damage (20)
    

