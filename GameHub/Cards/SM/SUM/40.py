import poke

def waveSplash(h):
    h.dealDamage(30)

def disarmingVoice(h):
    h.dealDamage(50)
    h.applyCondition(poke.PLAYER.ENEMY, poke.CONDITION.CONFUSED)