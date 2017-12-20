import poke

def disarmingVoice(h):
    h.dealDamage(30)
    h.applyCondition(CONFUSED,ACTIVE,ENEMY)

def sparklingAria(h):
    h.dealDamage(100)
    h.heal(30)