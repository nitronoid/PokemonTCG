import poke as p

def defenseCurl(h):
    if(h.flipCoin(1)):
        print "Need to heal"
        # prevent all damage done next turn (heal the amount that pokemon attacks)

def filter(card):
    card.cardType() == p.CARD.ENERGY and card.type() == p.TYPE.LIGHTNING

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
