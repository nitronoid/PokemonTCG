import poke

def disarmingVoice(h):
    h.dealDamage(30)
    h.applyCondition(poke.PLAYER.ENEMY, poke.CONDITION.CONFUSED)

def sparklingAria(h):
    h.dealDamage(100)
    h.healDamage(30)