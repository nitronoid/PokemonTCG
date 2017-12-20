import poke

def peckBugs(h):
    dmg = 10
    for i in h.viewBench(ENEMY):
        if(i.type() == GRASS):
            dmg += 30
        h.dealDamage(dmg)
