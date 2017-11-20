import poke

def disarmingVoice(h):
    h.dealDamage(30)
    h.applyCondition(CONFUSED,ACTIVE,ENEMY)

def waterGun(h):
    h.dealDamage(100)
    h.heal(30)