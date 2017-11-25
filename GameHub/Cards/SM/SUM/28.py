import poke

def confusionWave(h):
    h.applyCondition(CONFUSED, SELF)
    h.applyCondition(CONFUSED, ENEMY)