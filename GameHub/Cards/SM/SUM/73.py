import poke

def filter(slot):
    return slot.active() is not None

def bite(h):
    chosenEnemy=playerSlotChoice(p.PLAYER.SELF, p.PLAYER.ENEMY, p.ACTION.ATTACK,1,filter)[0] #
    h.dealDamage(30, chosenEnemy, False) #needs to do damage to a benched pokemon after selection


def flare(h):
    count=0
    for slot in h.viewBench(p.PLAYER.SELF):
        if slot.active().getName() == "Passimian":
            count+=1
    h.dealDamage(10+30*count)#10 +30 for every pokemon on the bench