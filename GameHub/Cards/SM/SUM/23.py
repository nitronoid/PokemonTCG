import poke

def singe(h):
    h.applyCondition(h.PLAYER.ENEMY, h.CONDITION.BURNED )#needs to burn the opposing pokemon


def bodySlam(h): 
    h.dealDamage(50)
    if h.flipCoin(1):
        h.applyCondition(h.PLAYER.ENEMY, h.CONDITION.PARALYZED )
