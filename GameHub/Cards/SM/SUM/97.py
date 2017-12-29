import poke

def peckBugs(h):
    dmg = 10
    if(h.viewBoard(ENEMY)[0].type() == GRASS):
        dmg += 30
    h.dealDamage(dmg)
