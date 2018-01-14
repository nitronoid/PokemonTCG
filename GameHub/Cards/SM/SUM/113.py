import poke as p

def instruct(h):
    while len(h.viewHand()) < 3
        h.drawCard(p.PLAYER.SELF)

def psychic(h):
    enemyEnergy=h.viewBench(p.PLAYER.ENEMY)[0].numEnergy()
    h.dealDamage(60 + enemyEnergy * 20)
    