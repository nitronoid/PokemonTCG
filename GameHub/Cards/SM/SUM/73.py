import poke as p

def filter(slot):
    return slot.active() is not None

def fling(h):
    chosenEnemy = h.playerSlotChoice(
        p.PLAYER.SELF,
        p.PLAYER.ENEMY,
        p.ACTION.ATTACK,
        1,
        filter,
        False
        )

    if chosenEnemy:
        h.dealDamage(30, chosenEnemy[0], False) #needs to do damage to a benched pokemon after selection


def teamPlay(h):
    count=0
    for slot in h.viewBench(p.PLAYER.SELF):
        if slot.active() and slot.active().getName() == "Passimian":
            count+=1
    h.dealDamage(10+30*count)#10 +30 for every pokemon on the bench