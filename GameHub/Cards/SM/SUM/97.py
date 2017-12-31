import poke as p

def peckBugs(h):
    dmg = 10
    print h.viewBench(p.PLAYER.ENEMY)[0].numPokemon()
    print type(h.viewBench(p.PLAYER.ENEMY)[0].active())
    if(h.viewBench(p.PLAYER.ENEMY)[0].active().type() == p.TYPE.GRASS):
        dmg += 30
    h.dealDamage(dmg)
