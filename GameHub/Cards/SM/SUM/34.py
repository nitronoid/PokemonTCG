import poke as p

def headlock(h):
    dmg = 30
    if(h.flipCoin(1)):
        dmg += 30
    else:
        h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.PARALYZED)
    h.dealDamage(dmg)

def effect(h):
    h.addBonusDefense(20, p.ORDER.AFTER, p.PLAYER.ENEMY)

def canUse(h):
    return True

def guardPress(h):
    h.dealDamage(80)
    ability = p.Abilty(effect, p.TRIGGER.ATTACK, p.DURATION.SINGLE, canUse)
    h.addEffect(p.PLAYER.ENEMY, 0, ability)
   
    

