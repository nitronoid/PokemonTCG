import poke as p

def singe(h):
    h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.BURNED )#needs to burn the opposing pokemon


def bodySlam(h): 
    h.dealDamage(50)
    if h.flipCoin(1):
        h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.PARALYZED )
