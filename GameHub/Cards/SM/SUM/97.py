import poke as p

def peckBugs(h):
    dmg = 10
    if(h.viewBench(p.PLAYER.ENEMY)[0].active().type() == p.TYPE.GRASS):
        dmg += 30
    h.dealDamage(dmg)
