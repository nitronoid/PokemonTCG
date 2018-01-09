import poke

def shoreUp(h):
    discard=h.viewDiscard(p.PLAYER.SELF)
    for card in discard:
        if card.getName()== "Fighting Energy"
            h.pileToBench(p.PLAYER.SELF, p.PILE.DISCARD, ,0) #sort this bit out

def flare(h):
    count=0
    for slot in h.viewBench(p.PLAYER.SELF):
        if slot.active().getName() == "Passimian":
            count+=1
    h.dealDamage(10+30*count)#10 +30 for every pokemon on the bench