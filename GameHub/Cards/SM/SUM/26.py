import poke

def fireFang(h):
    h.dealDamage(30)


def darkestLariat(h):
    int heads=h.flipCoin(2) 
    h.dealDamage(100,heads)


