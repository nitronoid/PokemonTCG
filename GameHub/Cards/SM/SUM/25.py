import poke as p

def furySwipes(h):
    h.dealDamage(20 * h.flipCoin(3))
        
def filter(h):
    return True

def flamethrower(h): 
    h.dealDamage(90) #but also discard one energy on Torracat
    choice = h.playerEnergyChoice(p.PLAYER.SELF,p.PLAYER.SELF, p.PILE.DISCARD, p.ACTION.DISCARD,0,filter,1)
    h.removeEnergy(p.PLAYER.SELF, p.PILE.DISCARD, 0, choice)
