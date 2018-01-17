import poke as p



def wallofSand(h):
    h.addBonusDefense(20, p.ORDER.AFTER)

def absorbVitality(h):
    origHealth= h.viewBench(p.PLAYER.ENEMY)[0].getRemainingHP()
    h.dealDamage(50) #heal from this pokemon same amount of damage as done to opponent active pokemon
    newHealth=h.viewBench(p.PLAYER.ENEMY)[0].getRemainingHP()
    h.healDamage(origHealth-newHealth)
    
