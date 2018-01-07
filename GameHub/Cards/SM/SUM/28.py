import poke as p

def confusionWave(h):
    h.applyCondition(p.PLAYER.SELF, p.CONDITION.CONFUSED)
    h.applyCondition(p.PLAYER.ENEMY, p.CONDITION.CONFUSED)
