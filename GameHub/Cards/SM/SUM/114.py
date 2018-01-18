import poke as p

def canPlay(h):
    # Check if active is damaged or in Special Conditions
    return len(h.viewStatus(p.PLAYER.SELF).conditions()) or h.viewBench(p.PLAYER.SELF)[0].getDamage()


def bigMalasada(h):
    h.healDamage(20)
    conditions = h.viewStatus(p.PLAYER.SELF).conditions()
    if len(conditions):
        conditionChoice = h.playerConditionChoice(p.PLAYER.SELF,p.PLAYER.SELF,p.ACTION.HEAL,conditions,1)
        h.removeCondition(p.PLAYER.SELF,conditions[conditionChoice[0]])
        print "remove a special condition from active pokemon"
    