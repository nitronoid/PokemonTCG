import poke as p



def wallofSand(h):
    h.addBonusDefense(20, p.ORDER.AFTER)

def absorbVitality(h):
    healAmount=h.viewBench(p.PLAYER.ENEMY)[0].remainingHP()
    healAmount=clamp(0,50,healAmount)
    h.dealDamage(50) #heal from this pokemon same amount of damage as done to opponent active pokemon
    h.healDamage(healAmount)
    
