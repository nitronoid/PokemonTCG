import poke as p

def bearHug(h):
    h.dealDamage(40)
    h.setCanRetreat(p.PLAYER.ENEMY)

def superpower(h):
    damage = 80
    if h.playerAgree(p.PLAYER.SELF, p.ACTION.ATTACK):
        damage += 40
        h.addDamageCounter(20, p.PLAYER.SELF)
    h.dealDamage(damage)
