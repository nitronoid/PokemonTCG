import poke as p

def effect(h):
    print "prevent all damage done"

def canUse(h):
    return True

def defenseCurl(h):
    if h.flipCoin(1):
        # prevent all damage done next turn
        ability = p.Ability(effect, '', p.TRIGGER.ATTACK, p.DURATION.SINGLE, canUse)
        h.addEffect(p.PLAYER.ENEMY, 0, ability)

def filter(card):
    return card.cardType() == p.CARD.ENERGY and card.type() == p.TYPE.LIGHTNING

def discharge(h):
    # discard all electricity energies on this monster
    # for each electricity card you DISCARD
    # on pokemon
    energy = h.viewBench(p.PLAYER.SELF)[0].viewEnergy()
    lightingEnergy = []
    for i in range(len(energy)):
        if filter(energy[i]):
            lightingEnergy.append(i)
    h.removeEnergy(p.PLAYER.SELF, p.PILE.DISCARD, 0, lightingEnergy)
    dmg = len(lightingEnergy) * 30
    h.dealDamage(dmg)
