import poke

def confusionWave(h):
    h.applyCondition(CONFUSED, ACTIVE, SELF)
    h.applyCondition(CONFUSED, ACTIVE, ENEMY)