import poke as p

def fireFang(h):
    h.dealDamage(30)
    h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.BURNED)

def darkestLariat(h):
    heads=h.flipCoin(2) 
    h.dealDamage(100 * heads)


